/*
 * EnumeratedAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <asn-one-objects/EnumeratedAsnOneObject.h>

namespace Flix {

EnumeratedAsnOneObject::EnumeratedAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::ENUMERATED),
    value(0)
{
}

EnumeratedAsnOneObject::~EnumeratedAsnOneObject()
{
}

int EnumeratedAsnOneObject::getValue(void) const
{
    return value;
}

void EnumeratedAsnOneObject::setValue(int value)
{
    this->value = value;
}

EnumeratedAsnOneObject* EnumeratedAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    EnumeratedAsnOneObject* asnOneObject = new EnumeratedAsnOneObject();

    int value = 0;
    auto currentValue = buffer.cbegin();
    while (currentValue != buffer.cend()) {
        value = (value << 8) + *currentValue;
        ++currentValue;
    }

    asnOneObject->setValue(value);

    return asnOneObject;
}

EnumeratedAsnOneObject* EnumeratedAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<EnumeratedAsnOneObject*>(object);
}

StreamBuffer EnumeratedAsnOneObject::serialize(void) const
{
    StreamBuffer payload;

    int tempValue = value;
    do {
        payload.insert(payload.begin(), tempValue & 0xff);
        tempValue = tempValue >> 8;
    } while (tempValue != 0);

    return addAsnOneHeader(PDU_CLASS_UNIVERSAL, false, PDU_TYPE_UNIVERSAL_ENUMERATED, payload);
}

std::string EnumeratedAsnOneObject::dump(void) const
{
    return "Enumerated(" + std::to_string(value) + ")";
}

} /* namespace Flix */
