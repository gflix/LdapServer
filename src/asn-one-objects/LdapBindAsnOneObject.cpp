/*
 * LdapBindAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <cassert>
#include <asn-one-objects/LdapBindAsnOneObject.h>
#include <common/Log.h>

namespace Flix {

LdapBindAsnOneObject::LdapBindAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_BIND)
{
}

LdapBindAsnOneObject::~LdapBindAsnOneObject()
{
}

bool LdapBindAsnOneObject::isValid(void) const
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

LdapBindAsnOneObject* LdapBindAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    LdapBindAsnOneObject* asnOneObject = new LdapBindAsnOneObject();

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

LdapBindAsnOneObject* LdapBindAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapBindAsnOneObject*>(object);
}

StreamBuffer LdapBindAsnOneObject::serialize(void) const
{
    // not supported
    assert(false);
    return {};
}

std::string LdapBindAsnOneObject::dump(void) const
{
    std::string dumpedObject;

    dumpedObject = "LdapBind{";

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