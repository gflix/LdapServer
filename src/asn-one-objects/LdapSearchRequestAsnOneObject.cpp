/*
 * LdapSearchRequestAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <cassert>
#include <asn-one-objects/LdapSearchRequestAsnOneObject.h>
#include <common/Log.h>

namespace Flix {

LdapSearchRequestAsnOneObject::LdapSearchRequestAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_SEARCH_REQUEST)
{
}

LdapSearchRequestAsnOneObject::~LdapSearchRequestAsnOneObject()
{
}

bool LdapSearchRequestAsnOneObject::isValid(void) const
{
    LOG_DEBUG("LdapSearchRequestAsnOneObject::isValid(subObjects.size()=" << subObjects.size());
    if (subObjects.size() < 8) {
        return false;
    }

    if (subObjects[0]->getType() != AsnOneObjectType::OCTET_STRING ||
        subObjects[1]->getType() != AsnOneObjectType::ENUMERATED ||
        subObjects[2]->getType() != AsnOneObjectType::ENUMERATED) {
        return false;
    }

    return true;
}

LdapSearchRequestAsnOneObject* LdapSearchRequestAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    LdapSearchRequestAsnOneObject* asnOneObject = new LdapSearchRequestAsnOneObject();

    if (!asnOneObject->decodeSequence(buffer, decodeStatus)) {
        delete asnOneObject;
        return nullptr;
    }

    if (!asnOneObject->isValid()) {
        decodeStatus = AsnOneDecodeStatus::INVALID_COMPOUND;
        delete asnOneObject;
        return nullptr;
    }

    return asnOneObject;
}

LdapSearchRequestAsnOneObject* LdapSearchRequestAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapSearchRequestAsnOneObject*>(object);
}

StreamBuffer LdapSearchRequestAsnOneObject::serialize(void) const
{
    // not supported
    assert(false);
    return {};
}

std::string LdapSearchRequestAsnOneObject::dump(void) const
{
    std::string dumpedObject;

    dumpedObject = "LdapSearchRequest{";

    bool firstObject = true;
    for (auto& subObject: subObjects) {
        if (!subObject) {
            continue;
        }
        if (firstObject) {
            firstObject = false;
        } else {
            dumpedObject += ", ";
        }
        dumpedObject += subObject->dump();
    }

    dumpedObject += '}';

    return dumpedObject;
}

} /* namespace Flix */
