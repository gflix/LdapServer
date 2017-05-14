/*
 * LdapBindAsnOneObject.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAPBINDREQUESTASNONEOBJECT_H_
#define SRC_LDAPBINDREQUESTASNONEOBJECT_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

class LdapBindRequestAsnOneObject: public GenericAsnOneObject {
public:
    LdapBindRequestAsnOneObject();
    virtual ~LdapBindRequestAsnOneObject();

    bool isValid(void) const;

    static LdapBindRequestAsnOneObject* decode(StreamBuffer buffer, AsnOneDecodeStatus& decodeStatus);
    static LdapBindRequestAsnOneObject* castObject(GenericAsnOneObject* object);

    virtual StreamBuffer serialize(void) const;
    virtual std::string dump(void) const;
};

} /* namespace Flix */

#endif /* SRC_LDAPBINDASNONEOBJECT_H_ */
