/*
 * LdapSearchRequestAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_LDAPSEARCHREQUESTASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_LDAPSEARCHREQUESTASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class LdapSearchRequestAsnOneObject: public GenericAsnOneObject {
public:
    LdapSearchRequestAsnOneObject();
    virtual ~LdapSearchRequestAsnOneObject();

    bool isValid(void) const;

    static LdapSearchRequestAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static LdapSearchRequestAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_LDAPSEARCHREQUESTASNONEOBJECT_H_ */
