/*
 * BooleanAsnOneObject.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <asn-one-objects/BooleanAsnOneObject.h>

namespace Flix {

BooleanAsnOneObject::BooleanAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::BOOLEAN),
    value(false)
{
}

BooleanAsnOneObject::~BooleanAsnOneObject()
{
}

bool BooleanAsnOneObject::getValue(void) const
{
    return value;
}

void BooleanAsnOneObject::setValue(bool value)
{
    this->value = value;
}

BooleanAsnOneObject* BooleanAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    BooleanAsnOneObject* asnOneObject = new BooleanAsnOneObject();

    bool value = false;
    auto currentValue = buffer.cbegin();
    while (currentValue != buffer.cend()) {
        if (*currentValue > 0) {
            value = true;
            break;
        }
        ++currentValue;
    }

    asnOneObject->setValue(value);

    return asnOneObject;
}

BooleanAsnOneObject* BooleanAsnOneObject::castObject(GenericAsnOneObject* object)
{
    return static_cast<BooleanAsnOneObject*>(object);
}

StreamBuffer BooleanAsnOneObject::serialize(void) const
{
    StreamBuffer payload;
    payload.push_back(value ? 1 : 0);

    return addAsnOneHeader(PDU_CLASS_UNIVERSAL, false, PDU_TYPE_UNIVERSAL_BOOLEAN, payload);
}

std::string BooleanAsnOneObject::dump(void) const
{
    return "Bool(" + std::string(value ? "true" : "false") + ")";
}

} /* namespace Flix */
