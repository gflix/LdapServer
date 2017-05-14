/*
 * IntegerAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <asn-one-objects/IntegerAsnOneObject.h>
#include <common/Log.h>

namespace Flix {

IntegerAsnOneObject::IntegerAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::INTEGER),
    value(0)
{
}

IntegerAsnOneObject::~IntegerAsnOneObject()
{
}

int IntegerAsnOneObject::getValue(void) const
{
    return value;
}

void IntegerAsnOneObject::setValue(int value)
{
//    LOG_DEBUG("IntegerAsnOneObject::setValue(" << value << ")");
    this->value = value;
}

IntegerAsnOneObject* IntegerAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    IntegerAsnOneObject* asnOneObject = new IntegerAsnOneObject();

    int value = 0;
    auto currentValue = buffer.cbegin();
    while (currentValue != buffer.cend()) {
        value = (value << 8) + *currentValue;
        ++currentValue;
    }

    asnOneObject->setValue(value);

    return asnOneObject;
}

IntegerAsnOneObject* IntegerAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<IntegerAsnOneObject*>(object);
}

StreamBuffer IntegerAsnOneObject::serialize(void) const
{
    StreamBuffer payload;

    int tempValue = value;
    do {
        payload.insert(payload.begin(), tempValue & 0xff);
        tempValue = tempValue >> 8;
    } while (tempValue != 0);

    return addAsnOneHeader(PDU_CLASS_UNIVERSAL, false, PDU_TYPE_UNIVERSAL_INTEGER, payload);
}

std::string IntegerAsnOneObject::dump(void) const
{
    return "Integer(" + std::to_string(value) + ")";
}

} /* namespace Flix */
