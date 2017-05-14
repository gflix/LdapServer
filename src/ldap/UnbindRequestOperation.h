/*
 * UnbindRequestOperation.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_UNBINDREQUESTOPERATION_H_
#define SRC_LDAP_UNBINDREQUESTOPERATION_H_

#include <asn-one-objects/LdapUnbindRequestAsnOneObject.h>
#include <ldap/GenericOperation.h>

namespace Flix {

class UnbindRequestOperation: public GenericOperation {
public:
    UnbindRequestOperation();
    virtual ~UnbindRequestOperation();

    virtual GenericOperation* execute(void) const;

    virtual GenericAsnOneObject* getAsnOneObject(void) const;
    virtual std::string dump(void) const;

    static UnbindRequestOperation* fromAsnOneObject(LdapUnbindRequestAsnOneObject* asnOneObject);
};

} /* namespace Flix */

#endif /* SRC_LDAP_UNBINDREQUESTOPERATION_H_ */
