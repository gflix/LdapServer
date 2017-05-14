/*
 * BindResponseOperation.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <asn-one-objects/LdapBindResponseAsnOneObject.h>
#include <ldap/BindResponseOperation.h>

namespace Flix {

BindResponseOperation::BindResponseOperation():
    GenericSimpleResponseOperation(OperationType::BIND_RESPONSE)
{
}

BindResponseOperation::~BindResponseOperation()
{
}

GenericAsnOneObject* BindResponseOperation::getAsnOneObject(void) const
{
    return GenericSimpleResponseOperation::getAsnOneObject(new LdapBindResponseAsnOneObject());
}

std::string BindResponseOperation::dump(void) const
{
    return GenericSimpleResponseOperation::dump("BindResponse");
}

} /* namespace Flix */
