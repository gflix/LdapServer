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
    UNBIND_REQUEST,
    SEARCH_REQUEST,
    SEARCH_RESULT_DONE,
};

enum class OperationResult {
    SUCCESS = 0,
    INVALID_CREDENTIALS = 49,
    OTHER = 80,
};

enum class SearchScope {
    BASE = 0,
    ONE = 1,
    SUBTREE = 2,
};

enum class DereferenceAliases {
    NEVER = 0,
    IN_SEARCHING = 1,
    FINDING_BASE_OBJECT = 2,
    ALWAYS = 3,
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

std::ostream& operator<<(std::ostream& stream, OperationResult result);

} /* namespace Flix */

#endif /* SRC_LDAP_GENERICOPERATION_H_ */
