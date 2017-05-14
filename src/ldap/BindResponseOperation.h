/*
 * BindResponseOperation.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_BINDRESPONSEOPERATION_H_
#define SRC_LDAP_BINDRESPONSEOPERATION_H_

#include <ldap/GenericOperation.h>

namespace Flix {

class BindResponseOperation: public GenericOperation {
public:
    BindResponseOperation();
    virtual ~BindResponseOperation();

    void setResult(OperationResult result);
    void setMatchedDn(const std::string& matchedDn);
    void setDiagnosticMessage(const std::string& diagnosticMessage);

    virtual GenericOperation* execute(void) const;

    virtual GenericAsnOneObject* getAsnOneObject(void) const;
    virtual std::string dump(void) const;

private:
    OperationResult result;
    std::string matchedDn;
    std::string diagnosticMessage;
};

} /* namespace Flix */

#endif /* SRC_LDAP_BINDRESPONSEOPERATION_H_ */
