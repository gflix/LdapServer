/*
 * EnumeratedAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_ENUMERATEDASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_ENUMERATEDASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class EnumeratedAsnOneObject: public GenericAsnOneObject {
public:
    EnumeratedAsnOneObject();
    virtual ~EnumeratedAsnOneObject();

    int getValue(void) const;

    void setValue(int value);

    static EnumeratedAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static EnumeratedAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;

private:
    int value;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_ENUMERATEDASNONEOBJECT_H_ */
