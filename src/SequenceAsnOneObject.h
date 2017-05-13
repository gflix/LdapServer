/*
 * SequenceAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_SEQUENCEASNONEOBJECT_H_
#define SRC_SEQUENCEASNONEOBJECT_H_

#include <GenericAsnOneObject.h>

namespace Flix {

class SequenceAsnOneObject: public GenericAsnOneObject {
public:
    SequenceAsnOneObject();
    virtual ~SequenceAsnOneObject();

    static SequenceAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
};

} /* namespace Flix */

#endif /* SRC_SEQUENCEASNONEOBJECT_H_ */
