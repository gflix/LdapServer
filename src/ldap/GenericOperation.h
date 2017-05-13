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

class GenericOperation {
public:
    GenericOperation(OperationType type);
    virtual ~GenericOperation();

    OperationType getType(void) const;
    bool isType(OperationType requestedType) const;

    virtual std::string dump(void) const = 0;
    virtual StreamBuffer getBuffer(void) const = 0;

    static GenericOperation* fromAsnOneObject(GenericAsnOneObject* asnOneObject);
    friend std::ostream& operator<<(std::ostream& stream, const GenericOperation& operation);

private:
    OperationType type;
};

} /* namespace Flix */

#endif /* SRC_LDAP_GENERICOPERATION_H_ */
