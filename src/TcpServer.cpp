/*
 * TcpServer.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <Log.h>
#include <StreamBuffer.h>
#include <TcpServer.h>

#define SERVER_SOCKET_INVALID (-1)
#define READ_BUFFER_SIZE (8)
#define TCP_PORT_MIN (1)
#define TCP_PORT_MAX (65535)

namespace Flix {

TcpServer::TcpServer():
    serverSocket(SERVER_SOCKET_INVALID)
{
    LOG_DEBUG("TcpServer::TcpServer()");
}

TcpServer::~TcpServer()
{
    stop();
    LOG_DEBUG("TcpServer::~TcpServer()");
}

bool TcpServer::start(int port)
{
    if (isRunning()) {
        return false;
    }
    if (port < TCP_PORT_MIN || port > TCP_PORT_MAX) {
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        serverSocket = SERVER_SOCKET_INVALID;
        return false;
    }

    int reuseAddressFlag = 1;

    sockaddr_in serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuseAddressFlag, sizeof(reuseAddressFlag)) != 0 ||
        bind(serverSocket, (sockaddr*) &serverAddress, sizeof(serverAddress)) != 0 ||
        listen(serverSocket, 5) != 0) {
        close(serverSocket);
        serverSocket = SERVER_SOCKET_INVALID;
        return false;
    }

    return true;
}

bool TcpServer::stop(void)
{
    if (!isRunning()) {
        return false;
    }

    for (auto& connection: connections) {
        if (!connection.get()) {
            continue;
        }
        connection->close();
    }
    connections.clear();

    close(serverSocket);
    serverSocket = SERVER_SOCKET_INVALID;
    return true;
}

bool TcpServer::isRunning(void) const
{
    return serverSocket > SERVER_SOCKET_INVALID;
}

int TcpServer::getServerSocket(void) const
{
    return serverSocket;
}

void TcpServer::updateFileDescriptors(fd_set* fds, int* maxFileDescriptor)
{
    if (!fds || !isRunning()) {
        return;
    }

    int tempMaxFileDescriptor = 0;
    if (!maxFileDescriptor) {
        maxFileDescriptor = &tempMaxFileDescriptor;
    }

    FD_SET(serverSocket, fds);
    *maxFileDescriptor = max(*maxFileDescriptor, serverSocket);

    for (auto& connection: connections) {
        if (!connection.get() || !connection->isOpened()) {
            continue;
        }

        FD_SET(connection->getConnectionSocket(), fds);
        *maxFileDescriptor = max(*maxFileDescriptor, connection->getConnectionSocket());
    }
}

void TcpServer::handleIncomingData(fd_set* fds)
{
    if (!fds || !isRunning()) {
        return;
    }

    if (FD_ISSET(serverSocket, fds)) {
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = 0;
        char clientAddressBuffer[INET_ADDRSTRLEN];

        bzero(&clientAddress, sizeof(clientAddress));
        bzero(&clientAddressBuffer, sizeof(clientAddressBuffer));
        int clientSocket = accept(serverSocket, (sockaddr*) &clientAddress, &clientAddressSize);
        assert(clientAddressSize == sizeof(clientAddress));
        inet_ntop(AF_INET, &clientAddress.sin_addr, clientAddressBuffer, sizeof(clientAddressBuffer));

        TcpConnection* connection = new TcpConnection(clientSocket, std::string(clientAddressBuffer), ntohs(clientAddress.sin_port));
        connections.push_back(TcpConnectionPointer(connection));
    }
    for (auto& connection: connections) {
        if (!connection.get() || !connection->isOpened()) {
            continue;
        }

        int connectionSocket = connection->getConnectionSocket();
        if (FD_ISSET(connectionSocket, fds)) {
            unsigned char rawBuffer[READ_BUFFER_SIZE];
            ssize_t bytesRead = recv(connectionSocket, rawBuffer, sizeof(rawBuffer), 0);
            LOG_DEBUG("bytesRead=" << bytesRead);

            if (bytesRead <= 0) {
                LOG_DEBUG("Client closed connection");
                connection->close();
            } else {
                StreamBuffer buffer;
                buffer.put(rawBuffer, bytesRead);
                connection->handleIncomingData(buffer);
            }
        }
    }

    // Clean up closed or invalid connections
    auto connection = connections.begin();
    while (connection != connections.end()) {
        if (!connection->get() || !connection->get()->isOpened()) {
            connection = connections.erase(connection);
        } else {
            ++connection;
        }
    }
}

int TcpServer::max(int a, int b)
{
    return a > b ? a : b;
}

} /* namespace Flix */
