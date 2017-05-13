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

StreamBuffer BindResponseOperation::getBuffer(void) const
{
    StreamBuffer buffer;
    buffer.push_back(0x61);
    buffer.push_back(0x07);
    buffer.push_back(0x0a);
    buffer.push_back(0x01);
    buffer.push_back(0x00);
    buffer.push_back(0x04);
    buffer.push_back(0x00);
    buffer.push_back(0x04);
    buffer.push_back(0x00);

    return buffer;
}

} /* namespace Flix */
