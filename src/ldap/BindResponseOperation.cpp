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
    GenericOperation(OperationType::BIND_RESPONSE),
    result(OperationResult::OTHER)
{
}

BindResponseOperation::~BindResponseOperation()
{
}

void BindResponseOperation::setResult(OperationResult result)
{
    this->result = result;
}

void BindResponseOperation::setMatchedDn(const std::string& matchedDn)
{
    this->matchedDn = matchedDn;
}

void BindResponseOperation::setDiagnosticMessage(const std::string& diagnosticMessage)
{
    this->diagnosticMessage = diagnosticMessage;
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

    EnumeratedAsnOneObject* resultObject = new EnumeratedAsnOneObject();
    resultObject->setValue(static_cast<unsigned char>(result));

    OctetStringAsnOneObject* matchedDnObject = new OctetStringAsnOneObject();
    matchedDnObject->setValue(matchedDn);

    OctetStringAsnOneObject* diagnosticMessageObject = new OctetStringAsnOneObject();
    diagnosticMessageObject->setValue(diagnosticMessage);

    asnObject->appendSubObject(resultObject);
    asnObject->appendSubObject(matchedDnObject);
    asnObject->appendSubObject(diagnosticMessageObject);

    return asnObject;
}

std::string BindResponseOperation::dump(void) const
{
    std::stringstream dumpedOperation;

    dumpedOperation << "BindResponse()";

    return dumpedOperation.str();
}

} /* namespace Flix */
