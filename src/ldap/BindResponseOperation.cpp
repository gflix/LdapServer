/*
 * BindResponseOperation.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <cassert>
#include <sstream>
#include <asn-one-objects/EnumeratedAsnOneObject.h>
#include <asn-one-objects/LdapBindResponseAsnOneObject.h>
#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <ldap/BindResponseOperation.h>

namespace Flix {

BindResponseOperation::BindResponseOperation():
    GenericOperation(OperationType::BIND_RESPONSE)
{
}

BindResponseOperation::~BindResponseOperation()
{
}

GenericOperation* BindResponseOperation::execute(void) const
{
    // Not supported
    assert(false);
    return nullptr;
}

GenericAsnOneObject* BindResponseOperation::getAsnOneObject(void) const
{
    LdapBindResponseAsnOneObject* asnObject = new LdapBindResponseAsnOneObject();
    EnumeratedAsnOneObject* ldapResult = new EnumeratedAsnOneObject();
    ldapResult->setValue(2);
    OctetStringAsnOneObject* matchedDn = new OctetStringAsnOneObject();
    matchedDn->setValue("None");
    OctetStringAsnOneObject* diagnosticMessage = new OctetStringAsnOneObject();
    diagnosticMessage->setValue("Success");
    asnObject->appendSubObject(ldapResult);
    asnObject->appendSubObject(matchedDn);
    asnObject->appendSubObject(diagnosticMessage);

    return asnObject;
}

std::string BindResponseOperation::dump(void) const
{
    std::stringstream dumpedOperation;

    dumpedOperation << "BindResponse()";

    return dumpedOperation.str();
}

} /* namespace Flix */
