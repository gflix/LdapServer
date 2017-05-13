/*
 * TcpConnection.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <unistd.h>
#include <asn-one-objects/GenericAsnOneObject.h>
#include <common/Log.h>
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

    inputStream.insert(inputStream.end(), stream.cbegin(), stream.cend());

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
            LOG_INFO("Cleaning up ASN.1 object...");
            delete asnOneObject;
        }
        inputStream.erase(inputStream.begin(), inputStream.begin() + consumedBytes);
    }
}

} /* namespace Flix */
