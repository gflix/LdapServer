/*
 * IntegerAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_INTEGERASNONEOBJECT_H_
#define SRC_INTEGERASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class IntegerAsnOneObject: public GenericAsnOneObject {
public:
    IntegerAsnOneObject();
    virtual ~IntegerAsnOneObject();

    int getValue(void) const;

    static IntegerAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static IntegerAsnOneObject* castObject(GenericAsnOneObject* object);

protected:
    std::string dump(void) const;

private:
    int value;

    void setValue(int value);
};

} /* namespace Flix */

#endif /* SRC_INTEGERASNONEOBJECT_H_ */
