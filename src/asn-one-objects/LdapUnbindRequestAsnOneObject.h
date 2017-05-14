/*
 * LdapUnbindRequestAsnOneObject.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_ASN_ONE_OBJECTS_LDAPUNBINDREQUESTASNONEOBJECT_H_
#define SRC_ASN_ONE_OBJECTS_LDAPUNBINDREQUESTASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class LdapUnbindRequestAsnOneObject: public GenericAsnOneObject {
public:
    LdapUnbindRequestAsnOneObject();
    virtual ~LdapUnbindRequestAsnOneObject();

    static LdapUnbindRequestAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static LdapUnbindRequestAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_ASN_ONE_OBJECTS_LDAPUNBINDREQUESTASNONEOBJECT_H_ */
