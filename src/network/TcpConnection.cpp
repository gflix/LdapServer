/*
 * TcpConnection.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <sys/socket.h>
#include <unistd.h>
#include <asn-one-objects/GenericAsnOneObject.h>
#include <common/Log.h>
#include <ldap/BindResponseOperation.h>
#include <ldap/LdapMessage.h>
#include <network/TcpConnection.h>

namespace Flix {

TcpConnection::TcpConnection(int connectionSocket, const std::string& peer, int port):
    connectionSocket(connectionSocket),
    peer(peer),
    port(port)
{
    opened = connectionSocket >= 0 ? true : false;
    LOG_INFO("Accepted connection from " << peer << ":" << port);
}

TcpConnection::~TcpConnection()
{
}

int TcpConnection::getConnectionSocket(void) const
{
    return connectionSocket;
}

const std::string& TcpConnection::getPeer(void) const
{
    return peer;
}

int TcpConnection::getPort(void) const
{
    return port;
}

bool TcpConnection::close(void)
{
    if (!isOpened()) {
        return false;
    }

    ::close(connectionSocket);
    opened = false;

    return true;
}

bool TcpConnection::isOpened(void) const
{
    return opened;
}

void TcpConnection::handleIncomingData(const StreamBuffer& stream)
{
    if (!isOpened()) {
        return;
    }

    inputStream.push_back(stream);

    AsnOneDecodeStatus decodeStatus = AsnOneDecodeStatus::UNKNOWN;
    bool quitImmediately = false;
    while (inputStream.size() > 0 && decodeStatus != AsnOneDecodeStatus::INCOMPLETE && !quitImmediately) {
        ssize_t consumedBytes = 0;
        GenericAsnOneObject* asnOneObject = GenericAsnOneObject::decode(inputStream, consumedBytes, decodeStatus);

        if (!asnOneObject) {
            switch (decodeStatus) {
            case AsnOneDecodeStatus::OK:
            case AsnOneDecodeStatus::INCOMPLETE:
                break;
            default:
                LOG_NOTICE("Protocol error detected (" << decodeStatus << ")! Closing connection.");
                close();
                quitImmediately = true;
                break;
            }
        } else {
            LOG_DEBUG(*asnOneObject);

            LdapMessage* ldapMessage = LdapMessage::fromAsnOneObject(asnOneObject);
            LOG_INFO("Cleaning up ASN.1 object...");
            delete asnOneObject;

            if (ldapMessage) {
                LOG_DEBUG(*ldapMessage);

                if (ldapMessage->isOperationType(OperationType::BIND_REQUEST)) {
                    LdapMessage* responseLdapMessage = new LdapMessage();
                    BindResponseOperation* operation = new BindResponseOperation();

                    responseLdapMessage->setMessageId(ldapMessage->getMessageId());
                    responseLdapMessage->setOperation(operation);

                    StreamBuffer responseBuffer = responseLdapMessage->getBuffer();
                    unsigned char buffer[128];
                    while (responseBuffer.size() > 0) {
                        ssize_t bytesRead = responseBuffer.get(buffer, sizeof(buffer));
                        if (bytesRead <= 0) {
                            close();
                            quitImmediately = true;
                            break;
                        }
                        send(connectionSocket, buffer, bytesRead, 0);
                    }
                    delete responseLdapMessage;
                }

                LOG_INFO("Cleaning up LDAP message...");
                delete ldapMessage;
            } else {
                LOG_ERROR("Could not decode LDAP message! Closing connection.");
                close();
                quitImmediately = true;
            }
        }
        inputStream.erase(inputStream.begin(), inputStream.begin() + consumedBytes);
    }
}

} /* namespace Flix */
