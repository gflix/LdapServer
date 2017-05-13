/*
 * IntegerAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_INTEGERASNONEOBJECT_H_
#define SRC_INTEGERASNONEOBJECT_H_

#include <GenericAsnOneObject.h>

namespace Flix {

class IntegerAsnOneObject: public GenericAsnOneObject {
public:
    IntegerAsnOneObject();
    virtual ~IntegerAsnOneObject();

    int getValue(void) const;

    static IntegerAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);

private:
    int value;

    void setValue(int value);
};

} /* namespace Flix */

#endif /* SRC_INTEGERASNONEOBJECT_H_ */
