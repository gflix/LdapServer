/*
 * TcpConnection.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <unistd.h>
#include <Log.h>
#include <TcpConnection.h>

namespace Flix {

TcpConnection::TcpConnection(int connectionSocket, const std::string& peer, int port):
    connectionSocket(connectionSocket),
    peer(peer),
    port(port)
{
    opened = connectionSocket >= 0 ? true : false;
    LOG_DEBUG("TcpConnection::TcpConnection(" << connectionSocket << ", " << peer << ":" << port << ")");
}

TcpConnection::~TcpConnection()
{
    LOG_DEBUG("TcpConnection::~TcpConnection(" << connectionSocket << ")");
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

    LOG_DEBUG("TcpConnection::close(" << connectionSocket << ")");

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
    LOG_DEBUG("stream.size()=" << stream.size() << ", inputStream.size()=" << inputStream.size());
}

} /* namespace Flix */
