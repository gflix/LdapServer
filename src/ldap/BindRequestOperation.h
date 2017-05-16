/*
 * BindRequestOperation.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_BINDREQUESTOPERATION_H_
#define SRC_LDAP_BINDREQUESTOPERATION_H_

#include <asn-one-objects/LdapBindRequestAsnOneObject.h>
#include <ldap/GenericOperation.h>

namespace Flix {

class BindRequestOperation: public GenericOperation {
public:
    BindRequestOperation();
    virtual ~BindRequestOperation();

    int getProtocolVersion(void) const;
    const std::string& getAuthenticationDn(void) const;
    const std::string& getPassword(void) const;

    virtual Operations execute(void) const;

    virtual GenericAsnOneObject* getAsnOneObject(void) const;
    virtual std::string dump(void) const;

    void setProtocolVersion(int protocolVersion);
    void setAuthenticationDn(const std::string& authenticationDn);
    void setPassword(const std::string& password);

    static BindRequestOperation* fromAsnOneObject(LdapBindRequestAsnOneObject* asnOneObject);

private:
    int protocolVersion;
    std::string authenticationDn;
    std::string password;
};

} /* namespace Flix */

#endif /* SRC_LDAP_BINDREQUESTOPERATION_H_ */
