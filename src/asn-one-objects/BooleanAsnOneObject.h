/*
 * BooleanAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_BOOLEANASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_BOOLEANASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class BooleanAsnOneObject: public GenericAsnOneObject {
public:
    BooleanAsnOneObject();
    virtual ~BooleanAsnOneObject();

    bool getValue(void) const;

    void setValue(bool value);

    static BooleanAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static BooleanAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;

private:
    bool value;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_BOOLEANASNONEOBJECT_H_ */
