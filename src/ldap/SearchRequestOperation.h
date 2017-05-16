/*
 * SearchRequestOperation.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_SEARCHREQUESTOPERATION_H_
#define SRC_LDAP_SEARCHREQUESTOPERATION_H_

#include <asn-one-objects/LdapSearchRequestAsnOneObject.h>
#include <ldap/GenericOperation.h>

namespace Flix {

class SearchRequestOperation: public GenericOperation {
public:
    SearchRequestOperation();
    virtual ~SearchRequestOperation();

    const std::string& getBaseDn(void) const;
    SearchScope getSearchScope(void) const;
    DereferenceAliases getDereferenceAliases(void) const;
    int getSizeLimit(void) const;
    int getTimeLimit(void) const;
    bool getOnlyTypesFlag(void) const;

    void setBaseDn(const std::string& baseDn);
    void setSearchScope(SearchScope searchScope);
    void setDereferenceAliases(DereferenceAliases dereferenceAliases);
    void setSizeLimit(int sizeLimit);
    void setTimeLimit(int timeLimit);
    void setOnlyTypesFlag(bool onlyTypesFlag);

    virtual Operations execute(void) const;

    virtual GenericAsnOneObject* getAsnOneObject(void) const;
    virtual std::string dump(void) const;

    static SearchRequestOperation* fromAsnOneObject(LdapSearchRequestAsnOneObject* asnOneObject);

private:
    std::string baseDn;
    SearchScope searchScope;
    DereferenceAliases dereferenceAliases;
    int sizeLimit;
    int timeLimit;
    bool onlyTypesFlag;
};

} /* namespace Flix */

#endif /* SRC_LDAP_SEARCHREQUESTOPERATION_H_ */
