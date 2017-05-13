/*
 * TcpServer.h
 *
 *  Created on: 13.05.2017
 *      Author: felix
 */

#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

namespace Flix {

class TcpServer {
public:
    TcpServer();
    virtual ~TcpServer();

    bool start(int port);
    bool stop(void);

    bool isRunning(void) const;
    int getServerSocket(void) const;
    void updateFileDescriptors(fd_set* fds, int* maxFileDescriptor);
    void handleIncomingData(fd_set* fds);

private:
    int serverSocket;

    int max(int a, int b);
};

} /* namespace Flix */

#endif /* SRC_TCPSERVER_H_ */
