/*
 * LdapSearchResultDoneAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_LDAPSEARCHRESULTDONEASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_LDAPSEARCHRESULTDONEASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class LdapSearchResultDoneAsnOneObject: public GenericAsnOneObject {
public:
    LdapSearchResultDoneAsnOneObject();
    virtual ~LdapSearchResultDoneAsnOneObject();

    static LdapSearchResultDoneAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static LdapSearchResultDoneAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_LDAPSEARCHRESULTDONEASNONEOBJECT_H_ */
