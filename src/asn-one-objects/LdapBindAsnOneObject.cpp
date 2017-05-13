/*
 * LdapBindAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

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
    LOG_DEBUG("subObject.size()=" << subObjects.size());

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
        LOG_ERROR("LdapBindAsnOneObject::decode(invalid)");
        decodeStatus = AsnOneDecodeStatus::INVALID_COMPOUND;
        delete asnOneObject;
        return nullptr;
    }

    return asnOneObject;
}

} /* namespace Flix */
