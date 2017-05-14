/*
 * GenericAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <asn-one-objects/BooleanAsnOneObject.h>
#include <asn-one-objects/EnumeratedAsnOneObject.h>
#include <asn-one-objects/GenericAsnOneObject.h>
#include <asn-one-objects/IntegerAsnOneObject.h>
#include <asn-one-objects/LdapBindRequestAsnOneObject.h>
#include <asn-one-objects/LdapFilterPresenceAsnOneObject.h>
#include <asn-one-objects/LdapSearchRequestAsnOneObject.h>
#include <asn-one-objects/LdapUnbindRequestAsnOneObject.h>
#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <asn-one-objects/SequenceAsnOneObject.h>
#include <common/Log.h>

#define LENGTH_LONG_FLAG (0x80)
#define LENGTH_LONG_MASK (0x7f)
#define PDU_CLASS_SHIFT (6)
#define PDU_CLASS_MASK (0x03)
#define PDU_COMBINED_SHIFT (5)
#define PDU_COMBINED_MASK (0x01)
#define PDU_TYPE_MASK (0x1f)

namespace Flix {

GenericAsnOneObject::GenericAsnOneObject(AsnOneObjectType type):
    type(type)
{
}

GenericAsnOneObject::~GenericAsnOneObject()
{
    for (auto& subObject: subObjects) {
        if (!subObject) {
            continue;
        }
        delete subObject;
    }
    subObjects.clear();
}

AsnOneObjectType GenericAsnOneObject::getType(void) const
{
    return type;
}

bool GenericAsnOneObject::isType(AsnOneObjectType requestedType) const
{
    return type == requestedType;
}

int GenericAsnOneObject::getSubObjectCount(void) const
{
    return subObjects.size();
}

GenericAsnOneObject* GenericAsnOneObject::getSubObject(int subObject) const
{
    if (subObject >= subObjects.size()) {
        return nullptr;
    }

    return subObjects[subObject];
}

bool GenericAsnOneObject::decodeSequence(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    if (buffer.size() == 0) {
        return true;
    }

    while (buffer.size() > 0 && decodeStatus == AsnOneDecodeStatus::OK) {
        ssize_t consumedBytes = 0;
        GenericAsnOneObject* subObject = GenericAsnOneObject::decode(buffer, consumedBytes, decodeStatus);

        if (decodeStatus != AsnOneDecodeStatus::OK || !subObject) {
            return false;
        }

        appendSubObject(subObject);
        buffer.erase(buffer.begin(), buffer.begin() + consumedBytes);
    }
    return true;
}

void GenericAsnOneObject::appendSubObject(GenericAsnOneObject* subObject)
{
    if (subObject) {
        subObjects.push_back(subObject);
    }
}

StreamBuffer GenericAsnOneObject::addAsnOneHeader(int pduClass, bool pduCombinedFlag, int pduType, const StreamBuffer& payload) const
{
    StreamBuffer pdu;
    int rawPduTag =
        (pduClass & PDU_CLASS_MASK) << PDU_CLASS_SHIFT |
        (pduCombinedFlag ? (1 << PDU_COMBINED_SHIFT) : 0) |
        (pduType & PDU_TYPE_MASK);

    pdu.push_back((unsigned char) rawPduTag);

    int length = payload.size();
    if (length <= 127) {
        pdu.push_back((unsigned char) length);
    } else {
        pdu.push_back(0x84);
        pdu.push_back((length >> 24) & 0xff);
        pdu.push_back((length >> 16) & 0xff);
        pdu.push_back((length >> 8) & 0xff);
        pdu.push_back(length & 0xff);
    }

    pdu.push_back(payload);

    return pdu;
}

StreamBuffer GenericAsnOneObject::serializeSequence(int pduClass, int pduType) const
{
    StreamBuffer payload;
    for (auto& subObject: subObjects) {
        if (!subObject) {
            continue;
        }
        payload.push_back(subObject->serialize());
    }

    return addAsnOneHeader(pduClass, true, pduType, payload);
}

GenericAsnOneObject* GenericAsnOneObject::decode(const StreamBuffer& buffer, ssize_t& consumedBytes, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::UNKNOWN;

    // A valid ASN.1 object consists at least of the tag byte and one or more length bytes
    int alreadyConsumedBytes = 2;
    if (buffer.size() < alreadyConsumedBytes) {
        decodeStatus = AsnOneDecodeStatus::INCOMPLETE;
        return nullptr;
    }

    int rawPduTag = buffer[0];
    int rawLength = buffer[1];
    int length = 0;

    if (rawLength & LENGTH_LONG_FLAG) {
        int lengthBytes = rawLength & LENGTH_LONG_MASK;
        if (buffer.size() < (alreadyConsumedBytes + lengthBytes)) {
            decodeStatus = AsnOneDecodeStatus::INCOMPLETE;
            return nullptr;
        }

        while (lengthBytes > 0) {
            length = (length << 8) + buffer[alreadyConsumedBytes];
            --lengthBytes;
            ++alreadyConsumedBytes;
        }
    } else {
        length = rawLength;
    }

    if (buffer.size() < alreadyConsumedBytes + length) {
        decodeStatus = AsnOneDecodeStatus::INCOMPLETE;
        return nullptr;
    }

    int pduClass = (rawPduTag >> PDU_CLASS_SHIFT) & PDU_CLASS_MASK;
    bool pduCombinedFlag = (rawPduTag >> PDU_COMBINED_SHIFT) & PDU_COMBINED_MASK ? true : false;
    int pduType = rawPduTag & PDU_TYPE_MASK;

    LOG_DEBUG("pduClass=" << pduClass << ", pduCombinedFlag=" << pduCombinedFlag << ", pduType=" << pduType);

    StreamBuffer subsetBuffer(buffer.cbegin() + alreadyConsumedBytes, buffer.cbegin() + alreadyConsumedBytes + length);
    GenericAsnOneObject* asnOneObject = nullptr;
    decodeStatus = AsnOneDecodeStatus::INVALID_TAG;

    if (pduClass == PDU_CLASS_UNIVERSAL) {
        if (!pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_BOOLEAN) {
            asnOneObject = BooleanAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_SEQUENCE) {
            asnOneObject = SequenceAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (!pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_INTEGER) {
            asnOneObject = IntegerAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (!pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_OCTET_STRING) {
            asnOneObject = OctetStringAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (!pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_ENUMERATED) {
            asnOneObject = EnumeratedAsnOneObject::decode(subsetBuffer, decodeStatus);
        }
    } else if (pduClass == PDU_CLASS_APPLICATION) {
        if (pduCombinedFlag && pduType == PDU_TYPE_APPLICATION_LDAP_BIND_REQUEST) {
            asnOneObject = LdapBindRequestAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (!pduCombinedFlag && pduType == PDU_TYPE_APPLICATION_LDAP_UNBIND_REQUEST) {
            asnOneObject = LdapUnbindRequestAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (pduCombinedFlag && pduType == PDU_TYPE_APPLICATION_LDAP_SEARCH_REQUEST) {
            asnOneObject = LdapSearchRequestAsnOneObject::decode(subsetBuffer, decodeStatus);
        }
    } else if (pduClass == PDU_CLASS_CONTEXT) {
        if (!pduCombinedFlag && pduType == PDU_TYPE_CONTEXT_LDAP_BIND_CREDENTIAL) {
            asnOneObject = OctetStringAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (!pduCombinedFlag && pduType == PDU_TYPE_CONTEXT_LDAP_FILTER_PRESENCE) {
            asnOneObject = LdapFilterPresenceAsnOneObject::decode(subsetBuffer, decodeStatus);
        }
    }

    if (decodeStatus == AsnOneDecodeStatus::OK) {
        consumedBytes = alreadyConsumedBytes + length;
    }

    return asnOneObject;
}

std::ostream& operator<<(std::ostream& stream, AsnOneDecodeStatus decodeStatus)
{
    switch (decodeStatus) {
    // a requested ASN.1 function is not yet supported
    case AsnOneDecodeStatus::NOT_SUPPORTED:
        stream << "NOT SUPPORTED";
        break;
    // the PDU contained in the buffer was not yet received completely
    case AsnOneDecodeStatus::INCOMPLETE:
        stream << "INCOMPLETE";
        break;
    // a ASN.1 tag could not be decoded
    case AsnOneDecodeStatus::INVALID_TAG:
        stream << "INVALID TAG";
        break;
    // a structure does not meet the expectations
    case AsnOneDecodeStatus::INVALID_COMPOUND:
        stream << "INVALID COMPOUND";
        break;
    // the ASN.1 was successfully decoded
    case AsnOneDecodeStatus::OK:
        stream << "OK";
        break;
    default:
        stream << "UNKNOWN";
        break;
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const GenericAsnOneObject& asnOneObject)
{
    stream << asnOneObject.dump();
    return stream;
}

} /* namespace Flix */
