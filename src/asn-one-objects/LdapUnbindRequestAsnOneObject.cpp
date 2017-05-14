/*
 * LdapUnbindRequestAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <cassert>
#include <asn-one-objects/LdapUnbindRequestAsnOneObject.h>

namespace Flix {

LdapUnbindRequestAsnOneObject::LdapUnbindRequestAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_UNBIND_REQUEST)
{
}

LdapUnbindRequestAsnOneObject::~LdapUnbindRequestAsnOneObject()
{
}

LdapUnbindRequestAsnOneObject* LdapUnbindRequestAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    LdapUnbindRequestAsnOneObject* asnOneObject = new LdapUnbindRequestAsnOneObject();

    return asnOneObject;
}

LdapUnbindRequestAsnOneObject* LdapUnbindRequestAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapUnbindRequestAsnOneObject*>(object);
}

StreamBuffer LdapUnbindRequestAsnOneObject::serialize(void) const
{
    // not supported
    assert(false);
    return {};
}

std::string LdapUnbindRequestAsnOneObject::dump(void) const
{
    return "LdapUnbindRequest{}";
}

} /* namespace Flix */
