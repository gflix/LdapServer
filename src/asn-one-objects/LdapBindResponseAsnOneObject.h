/*
 * LdapBindResponseAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_LDAPBINDRESPONSEASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_LDAPBINDRESPONSEASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class LdapBindResponseAsnOneObject: public GenericAsnOneObject {
public:
    LdapBindResponseAsnOneObject();
    virtual ~LdapBindResponseAsnOneObject();

    static LdapBindResponseAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static LdapBindResponseAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_LDAPBINDRESPONSEASNONEOBJECT_H_ */
