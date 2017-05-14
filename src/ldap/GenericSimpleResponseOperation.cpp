/*
 * GenericSimpleResponseOperation.cpp
 *
 *  Created on: 14.05.2017
 *      Author: felix
 */

#include <cassert>
#include <sstream>
#include <asn-one-objects/EnumeratedAsnOneObject.h>
#include <asn-one-objects/OctetStringAsnOneObject.h>
#include <ldap/GenericSimpleResponseOperation.h>

namespace Flix {

GenericSimpleResponseOperation::GenericSimpleResponseOperation(OperationType operationType):
    GenericOperation(operationType),
    result(OperationResult::OTHER)
{
}

GenericSimpleResponseOperation::~GenericSimpleResponseOperation()
{
}

OperationResult GenericSimpleResponseOperation::getResult(void) const
{
    return result;
}

const std::string& GenericSimpleResponseOperation::getMatchedDn(void) const
{
    return matchedDn;
}

const std::string& GenericSimpleResponseOperation::getDiagnosticMessage(void) const
{
    return diagnosticMessage;
}

void GenericSimpleResponseOperation::setResult(OperationResult result)
{
    this->result = result;
}

void GenericSimpleResponseOperation::setMatchedDn(const std::string& matchedDn)
{
    this->matchedDn = matchedDn;
}

void GenericSimpleResponseOperation::setDiagnosticMessage(const std::string& diagnosticMessage)
{
    this->diagnosticMessage = diagnosticMessage;
}

GenericOperation* GenericSimpleResponseOperation::execute(void) const
{
    // Not supported
    assert(false);
    return nullptr;
}

GenericAsnOneObject* GenericSimpleResponseOperation::getAsnOneObject(GenericAsnOneObject* asnObject) const
{
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

std::string GenericSimpleResponseOperation::dump(const std::string& operationType) const
{
    std::stringstream dumpedOperation;

    dumpedOperation << operationType << "(result=" << result <<
        ", matchedDn=" << matchedDn <<
        ", diagnosticMessage=" << diagnosticMessage << ")";

    return dumpedOperation.str();
}

} /* namespace Flix */
