/*
 * OctetStringAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_OCTETSTRINGASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_OCTETSTRINGASNONEOBJECT_H_

#include <string>
#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class OctetStringAsnOneObject: public GenericAsnOneObject {
public:
    OctetStringAsnOneObject();
    virtual ~OctetStringAsnOneObject();

    const std::string& getValue(void) const;

    void setValue(const std::string& value);

    static OctetStringAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static OctetStringAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;

private:
    std::string value;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_OCTETSTRINGASNONEOBJECT_H_ */
