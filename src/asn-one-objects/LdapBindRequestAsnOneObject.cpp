/*
 * LdapBindAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <cassert>
#include <asn-one-objects/LdapBindRequestAsnOneObject.h>
#include <common/Log.h>

namespace Flix {

LdapBindRequestAsnOneObject::LdapBindRequestAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_BIND_REQUEST)
{
}

LdapBindRequestAsnOneObject::~LdapBindRequestAsnOneObject()
{
}

bool LdapBindRequestAsnOneObject::isValid(void) const
{
    if (subObjects.size() < 3) {
        return false;
    }

    if (subObjects[0]->getType() != AsnOneObjectType::INTEGER ||
        subObjects[1]->getType() != AsnOneObjectType::OCTET_STRING ||
        subObjects[2]->getType() != AsnOneObjectType::OCTET_STRING) {
        return false;
    }

    return true;
}

LdapBindRequestAsnOneObject* LdapBindRequestAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    LdapBindRequestAsnOneObject* asnOneObject = new LdapBindRequestAsnOneObject();

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

LdapBindRequestAsnOneObject* LdapBindRequestAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapBindRequestAsnOneObject*>(object);
}

StreamBuffer LdapBindRequestAsnOneObject::serialize(void) const
{
    // not supported
    assert(false);
    return {};
}

std::string LdapBindRequestAsnOneObject::dump(void) const
{
    std::string dumpedObject;

    dumpedObject = "LdapBindRequest{";

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
