/*
 * GenericSimpleResponseOperation.h
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_GENERICSIMPLERESPONSEOPERATION_H_
#define SRC_LDAP_GENERICSIMPLERESPONSEOPERATION_H_

#include <ldap/GenericOperation.h>

namespace Flix {

class GenericSimpleResponseOperation: public GenericOperation {
public:
    GenericSimpleResponseOperation(OperationType operationType);
    virtual ~GenericSimpleResponseOperation();

    OperationResult getResult(void) const;
    const std::string& getMatchedDn(void) const;
    const std::string& getDiagnosticMessage(void) const;

    void setResult(OperationResult result);
    void setMatchedDn(const std::string& matchedDn);
    void setDiagnosticMessage(const std::string& diagnosticMessage);

    virtual Operations execute(void) const;

    virtual GenericAsnOneObject* getAsnOneObject(void) const = 0;
    virtual std::string dump(void) const = 0;

protected:
    GenericAsnOneObject* getAsnOneObject(GenericAsnOneObject* asnOneObject) const;
    std::string dump(const std::string& operationType) const;

private:
    OperationResult result;
    std::string matchedDn;
    std::string diagnosticMessage;
};

} /* namespace Flix */

#endif /* SRC_LDAP_GENERICSIMPLERESPONSEOPERATION_H_ */
