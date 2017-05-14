/*
 * LdapSearchResultDoneAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <asn-one-objects/LdapSearchResultDoneAsnOneObject.h>

namespace Flix {

LdapSearchResultDoneAsnOneObject::LdapSearchResultDoneAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_SEARCH_RESULT_DONE)
{
}

LdapSearchResultDoneAsnOneObject::~LdapSearchResultDoneAsnOneObject()
{
}

LdapSearchResultDoneAsnOneObject* LdapSearchResultDoneAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::NOT_SUPPORTED;
    return nullptr;
}

LdapSearchResultDoneAsnOneObject* LdapSearchResultDoneAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapSearchResultDoneAsnOneObject*>(object);
}

StreamBuffer LdapSearchResultDoneAsnOneObject::serialize(void) const
{
    return serializeSequence(PDU_CLASS_APPLICATION, PDU_TYPE_APPLICATION_LDAP_SEARCH_RESULT_DONE);
}

std::string LdapSearchResultDoneAsnOneObject::dump(void) const
{
    std::string dumpedObject;

    dumpedObject = "LdapSearchResultDone{";

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
