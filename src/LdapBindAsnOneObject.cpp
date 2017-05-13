/*
 * LdapBindAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <LdapBindAsnOneObject.h>

namespace Flix {

LdapBindAsnOneObject::LdapBindAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_BIND)
{
}

LdapBindAsnOneObject::~LdapBindAsnOneObject()
{
}

LdapBindAsnOneObject* LdapBindAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    LdapBindAsnOneObject* asnOneObject = new LdapBindAsnOneObject();

    return asnOneObject;
}

} /* namespace Flix */
