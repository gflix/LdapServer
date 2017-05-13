/*
 * IntegerAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <IntegerAsnOneObject.h>

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

} /* namespace Flix */
