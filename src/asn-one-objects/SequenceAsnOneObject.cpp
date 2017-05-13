/*
 * SequenceAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <asn-one-objects/SequenceAsnOneObject.h>

namespace Flix {

SequenceAsnOneObject::SequenceAsnOneObject():
    GenericAsnOneObject(AsnOneObjectType::SEQUENCE)
{
}

SequenceAsnOneObject::~SequenceAsnOneObject()
{
}

SequenceAsnOneObject* SequenceAsnOneObject::decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus)
{
    decodeStatus = AsnOneDecodeStatus::OK;
    SequenceAsnOneObject* asnOneObject = new SequenceAsnOneObject();

    if (!asnOneObject->decodeSequence(buffer, decodeStatus)) {
        delete asnOneObject;
        return nullptr;
    }

    return asnOneObject;
}

} /* namespace Flix */
