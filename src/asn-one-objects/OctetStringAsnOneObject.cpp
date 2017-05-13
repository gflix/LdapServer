/*
 * OctetStringAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <common/Log.h>

namespace Flix {

OctetStringAsnOneObject::OctetStringAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::OCTET_STRING)
{
}

OctetStringAsnOneObject::~OctetStringAsnOneObject()
{
}

const std::string& OctetStringAsnOneObject::getValue(void) const
{
    return value;
}

void OctetStringAsnOneObject::setValue(const std::string& value)
{
    LOG_DEBUG("OctetStringAsnOneObject::setValue(" << value << ")");
    this->value = value;
}

OctetStringAsnOneObject* OctetStringAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    OctetStringAsnOneObject* asnOneObject = new OctetStringAsnOneObject();

    std::string value;
    auto currentValue = buffer.cbegin();
    while (currentValue != buffer.cend()) {
        value += *currentValue;
        ++currentValue;
    }

    asnOneObject->setValue(value);

    return asnOneObject;
}

} /* namespace Flix */
