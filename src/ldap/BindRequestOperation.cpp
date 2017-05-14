/*
 * BindRequestOperation.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <cassert>
#include <sstream>
#include <asn-one-objects/IntegerAsnOneObject.h>
#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <ldap/BindRequestOperation.h>
#include <ldap/BindResponseOperation.h>

namespace Flix {

BindRequestOperation::BindRequestOperation():
    GenericOperation(OperationType::BIND_REQUEST),
    protocolVersion(0)
{
}

BindRequestOperation::~BindRequestOperation()
{
}

int BindRequestOperation::getProtocolVersion(void) const
{
    return protocolVersion;
}

const std::string& BindRequestOperation::getAuthenticationDn(void) const
{
    return authenticationDn;
}

const std::string& BindRequestOperation::getPassword(void) const
{
    return password;
}

GenericOperation* BindRequestOperation::execute(void) const
{
    BindResponseOperation* operation = new BindResponseOperation();

    return operation;
}

GenericAsnOneObject* BindRequestOperation::getAsnOneObject(void) const
{
    // Not supported
    assert(false);
    return nullptr;
}

std::string BindRequestOperation::dump(void) const
{
    std::stringstream dumpedOperation;

    dumpedOperation << "BindRequestOperation(protocolVersion=" <<
        protocolVersion << ", authenticationDn=" << authenticationDn <<
        ", password=***)";

    return dumpedOperation.str();
}

void BindRequestOperation::setProtocolVersion(int protocolVersion)
{
    this->protocolVersion = protocolVersion;
}

void BindRequestOperation::setAuthenticationDn(const std::string& authenticationDn)
{
    this->authenticationDn = authenticationDn;
}

void BindRequestOperation::setPassword(const std::string& password)
{
    this->password = password;
}

BindRequestOperation* BindRequestOperation::fromAsnOneObject(LdapBindRequestAsnOneObject* asnOneObject)
{
    if (!asnOneObject || !asnOneObject->isValid()) {
        return nullptr;
    }

    BindRequestOperation* operation = new BindRequestOperation();
    operation->setProtocolVersion(IntegerAsnOneObject::castObject(asnOneObject->getSubObject(0))->getValue());
    operation->setAuthenticationDn(OctetStringAsnOneObject::castObject(asnOneObject->getSubObject(1))->getValue());
    operation->setPassword(OctetStringAsnOneObject::castObject(asnOneObject->getSubObject(2))->getValue());

    return operation;
}

} /* namespace Flix */
