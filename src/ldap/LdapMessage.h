/*
 * LdapMessage.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_LDAPMESSAGE_H_
#define SRC_LDAP_LDAPMESSAGE_H_

#include <ostream>
#include <string>
#include <asn-one-objects/GenericAsnOneObject.h>
#include <ldap/GenericOperation.h>

namespace Flix {

class LdapMessage {
public:
    LdapMessage();
    virtual ~LdapMessage();

    int getMessageId(void) const;
    GenericOperation* getOperation(void) const;
    bool isOperationType(OperationType requestedType) const;
    std::string dump(void) const;

    void setMessageId(int messageId);
    void setOperation(GenericOperation* operation);

    static LdapMessage* fromAsnOneObject(const GenericAsnOneObject* asnOneObject);
    friend std::ostream& operator<<(std::ostream& stream, const LdapMessage& ldapMessage);

private:
    int messageId;
    GenericOperation* operation;
};

} /* namespace Flix */

#endif /* SRC_LDAP_LDAPMESSAGE_H_ */
