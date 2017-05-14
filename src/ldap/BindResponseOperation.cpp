/*
 * BindResponseOperation.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <sstream>
#include <ldap/BindResponseOperation.h>

namespace Flix {

BindResponseOperation::BindResponseOperation():
    GenericOperation(OperationType::BIND_RESPONSE)
{
}

BindResponseOperation::~BindResponseOperation()
{
}

std::string BindResponseOperation::dump(void) const
{
    std::stringstream dumpedOperation;

    dumpedOperation << "BindResponse()";

    return dumpedOperation.str();
}

} /* namespace Flix */
