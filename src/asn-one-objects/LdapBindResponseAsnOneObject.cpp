/*
 * LdapBindResponseAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <asn-one-objects/LdapBindResponseAsnOneObject.h>

namespace Flix {

LdapBindResponseAsnOneObject::LdapBindResponseAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_BIND_RESPONSE)
{
}

LdapBindResponseAsnOneObject::~LdapBindResponseAsnOneObject()
{
}

LdapBindResponseAsnOneObject* LdapBindResponseAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::NOT_SUPPORTED;
    return nullptr;
}

LdapBindResponseAsnOneObject* LdapBindResponseAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapBindResponseAsnOneObject*>(object);
}

StreamBuffer LdapBindResponseAsnOneObject::serialize(void) const
{
    return serializeSequence(PDU_CLASS_APPLICATION, PDU_TYPE_APPLICATION_LDAP_BIND_RESPONSE);
}

std::string LdapBindResponseAsnOneObject::dump(void) const
{
    std::string dumpedObject;

    dumpedObject = "LdapBindResponse{";

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
