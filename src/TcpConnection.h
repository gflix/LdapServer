/*
 * TcpConnection.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_TCPCONNECTION_H_
#define SRC_TCPCONNECTION_H_

#include <list>
#include <memory>
#include <string>

namespace Flix {

class TcpConnection {
public:
    TcpConnection(int connectionSocket, const std::string& peer, int port);
    virtual ~TcpConnection();

    int getConnectionSocket(void) const;
    const std::string& getPeer(void) const;
    int getPort(void) const;

    bool close(void);
    bool isOpened(void) const;

private:
    int connectionSocket;
    std::string peer;
    int port;

    bool opened;
};

typedef std::shared_ptr<TcpConnection> TcpConnectionPointer;
typedef std::list<TcpConnectionPointer> TcpConnections;

} /* namespace Flix */

#endif /* SRC_TCPCONNECTION_H_ */
