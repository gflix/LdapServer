/*
 * GenericAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <GenericAsnOneObject.h>
#include <IntegerAsnOneObject.h>
#include <LdapBindAsnOneObject.h>
#include <Log.h>
#include <SequenceAsnOneObject.h>

#define LENGTH_LONG_FLAG (0x80)
#define LENGTH_LONG_MASK (0x7f)
#define PDU_CLASS_SHIFT (6)
#define PDU_CLASS_MASK (0x03)
#define PDU_COMBINED_SHIFT (5)
#define PDU_COMBINED_MASK (0x01)
#define PDU_TYPE_MASK (0x1f)

#define PDU_CLASS_UNIVERSAL (0)
#define PDU_CLASS_APPLICATION (1)

#define PDU_TYPE_UNIVERSAL_INTEGER (2)
#define PDU_TYPE_UNIVERSAL_SEQUENCE (16)

#define PDU_TYPE_APPLICATION_BIND (0)

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

void GenericAsnOneObject::appendSubObject(GenericAsnOneObject* subObject)
{
    if (subObject) {
        subObjects.push_back(subObject);
    }
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
    LOG_DEBUG("subsetBuffer.size()=" << subsetBuffer.size());
    GenericAsnOneObject* asnOneObject = nullptr;
    decodeStatus = AsnOneDecodeStatus::INVALID_TAG;
    if (pduClass == PDU_CLASS_UNIVERSAL) {
        if (pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_SEQUENCE) {
            asnOneObject = SequenceAsnOneObject::decode(subsetBuffer, decodeStatus);
        } else if (!pduCombinedFlag && pduType == PDU_TYPE_UNIVERSAL_INTEGER) {
            asnOneObject = IntegerAsnOneObject::decode(subsetBuffer, decodeStatus);
        }
    } else if (pduClass == PDU_CLASS_APPLICATION) {
        if (pduCombinedFlag && pduType == PDU_TYPE_APPLICATION_BIND) {
            asnOneObject = LdapBindAsnOneObject::decode(subsetBuffer, decodeStatus);
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
    case AsnOneDecodeStatus::NOT_SUPPORTED:
        stream << "NOT SUPPORTED";
        break;
    case AsnOneDecodeStatus::INCOMPLETE:
        stream << "INCOMPLETE";
        break;
    case AsnOneDecodeStatus::INVALID_TAG:
        stream << "INVALID TAG";
        break;
    case AsnOneDecodeStatus::OK:
        stream << "OK";
        break;
    default:
        stream << "UNKNOWN";
        break;
    }

    return stream;
}

} /* namespace Flix */
