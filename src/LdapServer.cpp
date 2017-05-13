#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <TcpServer.h>

using namespace std;

#define TCP_SERVER_PORT (3389)

volatile bool terminationFlag = false;

void handleTerminationRequest(int signal)
{
    cerr << "INFO: Caught signal " << signal << ". Stopping threads..." << endl;
    terminationFlag = true;
}

int main(int argc, char* argv[])
{
    Flix::TcpServer tcpServer;

    signal(SIGINT, &handleTerminationRequest);
    signal(SIGTERM, &handleTerminationRequest);
    signal(SIGHUP, &handleTerminationRequest);

    if (!tcpServer.start(TCP_SERVER_PORT)) {
        cerr << "ERROR: Could not initialize TCP server! Aborting." << endl;
        return 1;
    }

    cout << "INFO: TCP server is running on port " << TCP_SERVER_PORT << endl;

    while (!terminationFlag) {
        fd_set fds;
        int maxFileDescriptor = 0;
        FD_ZERO(&fds);
        tcpServer.updateFileDescriptors(&fds, &maxFileDescriptor);

        timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        if (select(maxFileDescriptor + 1, &fds, nullptr, nullptr, &timeout) > 0) {
            tcpServer.handleIncomingData(&fds);
        } else {
            cout << "INFO: select() timed out." << endl;
        }
    }

    if (!tcpServer.stop()) {
        cerr << "ERROR: Could not stop TCP server! Aborting." << endl;
        return 1;
    }

    return 0;
}
