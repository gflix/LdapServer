/*
 * SequenceAsnOneObject.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <SequenceAsnOneObject.h>

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

    if (buffer.size() == 0) {
        return asnOneObject;
    }

    while (buffer.size() > 0 && decodeStatus == AsnOneDecodeStatus::OK) {
        ssize_t consumedBytes = 0;
        GenericAsnOneObject* subObject = GenericAsnOneObject::decode(buffer, consumedBytes, decodeStatus);

        if (decodeStatus != AsnOneDecodeStatus::OK || !subObject) {
            delete asnOneObject;
            return nullptr;
        }

        asnOneObject->appendSubObject(subObject);
        buffer.erase(buffer.begin(), buffer.begin() + consumedBytes);
    }
    return asnOneObject;
}

} /* namespace Flix */
