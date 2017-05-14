/*
 * GenericOperation.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <common/Log.h>
#include <ldap/BindRequestOperation.h>
#include <ldap/GenericOperation.h>
#include <ldap/SearchRequestOperation.h>
#include <ldap/UnbindRequestOperation.h>

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
    case AsnOneObjectType::LDAP_UNBIND_REQUEST:
        operation = UnbindRequestOperation::fromAsnOneObject(LdapUnbindRequestAsnOneObject::castObject(asnOneObject));
        break;
    case AsnOneObjectType::LDAP_SEARCH_REQUEST:
        operation = SearchRequestOperation::fromAsnOneObject(LdapSearchRequestAsnOneObject::castObject(asnOneObject));
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

std::ostream& operator<<(std::ostream& stream, OperationResult result)
{
    switch (result) {
    case OperationResult::SUCCESS:
        stream << "SUCCESS";
        break;
    case OperationResult::INVALID_CREDENTIALS:
        stream << "INVALID CREDENTIALS";
        break;
    case OperationResult::OTHER:
        stream << "OTHER RESULT";
        break;
    default:
        stream << "UNKNOWN RESULT";
        break;
    }
    return stream;
}

} /* namespace Flix */
