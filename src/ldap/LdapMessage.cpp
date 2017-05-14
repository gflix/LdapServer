/*
 * LdapMessage.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <sstream>
#include <asn-one-objects/IntegerAsnOneObject.h>
#include <asn-one-objects/SequenceAsnOneObject.h>
#include <ldap/LdapMessage.h>

namespace Flix {

LdapMessage::LdapMessage():
    messageId(0),
    operation(nullptr)
{
}

LdapMessage::~LdapMessage()
{
    if (operation) {
        delete operation;
    }
}

int LdapMessage::getMessageId(void) const
{
    return messageId;
}

GenericOperation* LdapMessage::getOperation(void) const
{
    return operation;
}

bool LdapMessage::isOperationType(OperationType requestedType) const
{
    if (!operation) {
        return false;
    }
    return operation->isType(requestedType);
}

LdapMessage* LdapMessage::execute(void) const
{
    if (!operation) {
        return nullptr;
    }

    LdapMessage* ldapResponseMessage = new LdapMessage();
    ldapResponseMessage->setMessageId(messageId);

    GenericOperation* responseOperation = operation->execute();
    if (!responseOperation) {
        delete ldapResponseMessage;
        return nullptr;
    }
    ldapResponseMessage->setOperation(responseOperation);

    return ldapResponseMessage;
}

GenericAsnOneObject* LdapMessage::getAsnOneObject(void) const
{
    SequenceAsnOneObject* asnObject = new SequenceAsnOneObject();
    IntegerAsnOneObject* messageIdObject = new IntegerAsnOneObject();
    messageIdObject->setValue(messageId);
    asnObject->appendSubObject(messageIdObject);
    if (operation) {
        asnObject->appendSubObject(operation->getAsnOneObject());
    }

    return asnObject;
}

std::string LdapMessage::dump(void) const
{
    std::stringstream dumpedMessage;

    dumpedMessage << "LdapMessage(id=" << messageId << ", ";

    if (operation) {
        dumpedMessage << *operation;
    } else {
        dumpedMessage << "INVALID OPERATION";
    }
    dumpedMessage << ")";

    return dumpedMessage.str();
}

void LdapMessage::setMessageId(int messageId)
{
    this->messageId = messageId;
}

void LdapMessage::setOperation(GenericOperation* operation)
{
    this->operation = operation;
}

LdapMessage* LdapMessage::fromAsnOneObject(const GenericAsnOneObject* asnOneObject)
{
    if (!asnOneObject || !asnOneObject->isType(AsnOneObjectType::SEQUENCE)) {
        return nullptr;
    }

    LdapMessage* ldapMessage = new LdapMessage();

    IntegerAsnOneObject* messageIdObject = IntegerAsnOneObject::castObject(asnOneObject->getSubObject(0));
    if (!messageIdObject->isType(AsnOneObjectType::INTEGER)) {
        delete ldapMessage;
        return nullptr;
    }

    ldapMessage->setMessageId(messageIdObject->getValue());
    ldapMessage->setOperation(GenericOperation::fromAsnOneObject(asnOneObject->getSubObject(1)));

    return ldapMessage;
}

std::ostream& operator<<(std::ostream& stream, const LdapMessage& ldapMessage)
{
    stream << ldapMessage.dump();
    return stream;
}

} /* namespace Flix */
