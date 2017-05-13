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


std::string SequenceAsnOneObject::dump(void) const
{
    std::string dumpedObject;

    dumpedObject = "Sequence[";

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

    dumpedObject += ']';

    return dumpedObject;
}

} /* namespace Flix */
