/*
 * TcpConnection.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <sys/socket.h>
#include <unistd.h>
#include <cassert>
#include <asn-one-objects/GenericAsnOneObject.h>
#include <common/Log.h>
#include <ldap/BindResponseOperation.h>
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
            LOG_DEBUG("Cleaning up ASN.1 object...");
            delete asnOneObject;

            if (ldapMessage) {
                LOG_INFO("Request: " << *ldapMessage);
                LdapMessage* ldapResponseMessage = ldapMessage->execute();
                if (!ldapResponseMessage) {
                    if (ldapMessage->isOperationType(OperationType::UNBIND_REQUEST)) {
                        LOG_NOTICE("Received LDAP unbind request. Closing connection...");
                    } else {
                        LOG_WARNING("Could not execute LDAP request! Closing connection...");
                    }
                    close();
                    quitImmediately = true;
                } else {
                    LOG_INFO("Response: " << *ldapResponseMessage);

                    GenericAsnOneObject* responseObject = ldapResponseMessage->getAsnOneObject();
                    assert(responseObject);
                    StreamBuffer responseBuffer = responseObject->serialize();

                    if (!sendData(responseBuffer)) {
                        close();
                        quitImmediately = true;
                    }

                    delete responseObject;
                    delete ldapResponseMessage;
                }

                LOG_DEBUG("Cleaning up LDAP message...");
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

bool TcpConnection::sendData(StreamBuffer stream)
{
    if (!isOpened()) {
        return false;
    }

    unsigned char buffer[128];
    while (stream.size() > 0) {
        ssize_t bytesRead = stream.get(buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            return false;
        }
        send(connectionSocket, buffer, bytesRead, 0);
    }
    return true;
}

} /* namespace Flix */
