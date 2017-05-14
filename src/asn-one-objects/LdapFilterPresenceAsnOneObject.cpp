/*
 * LdapFilterPresenceAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <asn-one-objects/LdapFilterPresenceAsnOneObject.h>

namespace Flix {

LdapFilterPresenceAsnOneObject::LdapFilterPresenceAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::LDAP_FILTER_PRESENCE)
{
}

LdapFilterPresenceAsnOneObject::~LdapFilterPresenceAsnOneObject()
{
}

const std::string& LdapFilterPresenceAsnOneObject::getValue(void) const
{
    return value;
}

void LdapFilterPresenceAsnOneObject::setValue(const std::string& value)
{
    this->value = value;
}

LdapFilterPresenceAsnOneObject* LdapFilterPresenceAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    LdapFilterPresenceAsnOneObject* asnOneObject = new LdapFilterPresenceAsnOneObject();

    std::string value;
    auto currentValue = buffer.cbegin();
    while (currentValue != buffer.cend()) {
        value += *currentValue;
        ++currentValue;
    }

    asnOneObject->setValue(value);

    return asnOneObject;
}

LdapFilterPresenceAsnOneObject* LdapFilterPresenceAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<LdapFilterPresenceAsnOneObject*>(object);
}

StreamBuffer LdapFilterPresenceAsnOneObject::serialize(void) const
{
    StreamBuffer payload;

    for (auto& character: value) {
        payload.push_back(character);
    }

    return addAsnOneHeader(PDU_CLASS_UNIVERSAL, false, PDU_TYPE_UNIVERSAL_OCTET_STRING, payload);
}

std::string LdapFilterPresenceAsnOneObject::dump(void) const
{
    return "LdapFilterPresence(" + value + ")";
}

} /* namespace Flix */
