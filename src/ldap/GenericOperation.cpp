/*
 * GenericOperation.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <common/Log.h>
#include <ldap/BindRequestOperation.h>
#include <ldap/GenericOperation.h>

namespace Flix {

GenericOperation::GenericOperation(OperationType type):
    type(type)
{
}

GenericOperation::~GenericOperation()
{
}

OperationType GenericOperation::getType(void) const
{
    return type;
}

bool GenericOperation::isType(OperationType requestedType) const
{
    return type == requestedType;
}

GenericOperation* GenericOperation::fromAsnOneObject(GenericAsnOneObject* asnOneObject)
{
    if (!asnOneObject) {
        return nullptr;
    }

    GenericOperation* operation = nullptr;
    switch (asnOneObject->getType()) {
    case AsnOneObjectType::LDAP_BIND_REQUEST:
        operation = BindRequestOperation::fromAsnOneObject(LdapBindRequestAsnOneObject::castObject(asnOneObject));
        break;
    default:
        break;
    }

    return operation;
}

std::ostream& operator<<(std::ostream& stream, const GenericOperation& operation)
{
    stream << operation.dump();
    return stream;
}

} /* namespace Flix */
