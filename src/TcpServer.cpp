/*
 * TcpServer.cpp
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <iostream>
#include "TcpServer.h"

#define SERVER_SOCKET_INVALID (-1)
#define TCP_PORT_MIN (1)
#define TCP_PORT_MAX (65535)

namespace Flix {

TcpServer::TcpServer():
    serverSocket(SERVER_SOCKET_INVALID)
{
}

TcpServer::~TcpServer()
{
    stop();
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

    sockaddr_in serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*) &serverAddress, sizeof(serverAddress)) != 0 ||
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
}

void TcpServer::handleIncomingData(fd_set* fds)
{
    if (!fds || !isRunning()) {
        return;
    }

    if (FD_ISSET(serverSocket, fds)) {
        sockaddr_in clientAddress;
        socklen_t clientAddressSize;
        bzero(&clientAddress, sizeof(clientAddress));
        int clientSocket = accept(serverSocket, (sockaddr*) &clientAddress, &clientAddressSize);
        assert(clientAddressSize == sizeof(clientAddress));
        std::cout << "INFO: Accepted client" << std::endl;
        close(clientSocket);
    }
}

int TcpServer::max(int a, int b)
{
    return a > b ? a : b;
}

} /* namespace Flix */
