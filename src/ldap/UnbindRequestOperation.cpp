/*
 * UnbindRequestOperation.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <cassert>
#include <ldap/UnbindRequestOperation.h>

namespace Flix {

UnbindRequestOperation::UnbindRequestOperation():
    GenericOperation(OperationType::UNBIND_REQUEST)
{
}

UnbindRequestOperation::~UnbindRequestOperation()
{
}

GenericOperation* UnbindRequestOperation::execute(void) const
{
    return nullptr;
}

GenericAsnOneObject* UnbindRequestOperation::getAsnOneObject(void) const
{
    // Not supported
    assert(false);
    return nullptr;
}

std::string UnbindRequestOperation::dump(void) const
{
    return "UnbindRequestOperation()";
}

UnbindRequestOperation* UnbindRequestOperation::fromAsnOneObject(LdapUnbindRequestAsnOneObject* asnOneObject)
{
    if (!asnOneObject) {
        return nullptr;
    }

    UnbindRequestOperation* operation = new UnbindRequestOperation();
    return operation;
}


} /* namespace Flix */
