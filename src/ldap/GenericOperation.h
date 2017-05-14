/*
 * GenericOperation.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_LDAP_GENERICOPERATION_H_
#define SRC_LDAP_GENERICOPERATION_H_

#include <asn-one-objects/GenericAsnOneObject.h>

namespace Flix {

enum class OperationType {
    UNKNOWN,
    BIND_REQUEST,
    BIND_RESPONSE,
};

enum class OperationResult {
    SUCCESS = 0,
    INVALID_CREDENTIALS = 49,
    OTHER = 80,
};

class GenericOperation {
public:
    GenericOperation(OperationType type);
    virtual ~GenericOperation();

    OperationType getType(void) const;
    bool isType(OperationType requestedType) const;

    virtual GenericOperation* execute(void) const = 0;

    virtual GenericAsnOneObject* getAsnOneObject(void) const = 0;
    virtual std::string dump(void) const = 0;

    static GenericOperation* fromAsnOneObject(GenericAsnOneObject* asnOneObject);
    friend std::ostream& operator<<(std::ostream& stream, const GenericOperation& operation);

private:
    OperationType type;
};

} /* namespace Flix */

#endif /* SRC_LDAP_GENERICOPERATION_H_ */
