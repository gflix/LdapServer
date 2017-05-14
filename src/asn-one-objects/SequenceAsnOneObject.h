/*
 * SequenceAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_SEQUENCEASNONEOBJECT_H_
#define SRC_SEQUENCEASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class SequenceAsnOneObject: public GenericAsnOneObject {
public:
    SequenceAsnOneObject();
    virtual ~SequenceAsnOneObject();

    static SequenceAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_SEQUENCEASNONEOBJECT_H_ */
