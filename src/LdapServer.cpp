#include <signal.h>
#include <unistd.h>
#include <common/Log.h>
#include <network/TcpServer.h>

using namespace std;

#define TCP_SERVER_PORT (3389)

volatile bool terminationFlag = false;

void handleTerminationRequest(int signal)
{
    LOG_NOTICE("Caught signal " << signal << ". Stopping threads...");
    terminationFlag = true;
}

int main(int argc, char* argv[])
{
    Flix::TcpServer tcpServer;

    signal(SIGINT, &handleTerminationRequest);
    signal(SIGTERM, &handleTerminationRequest);
    signal(SIGHUP, &handleTerminationRequest);

    if (!tcpServer.start(TCP_SERVER_PORT)) {
        LOG_ERROR("Could not initialize TCP server! Aborting.");
        return 1;
    }

    LOG_INFO("TCP server is running on port " << TCP_SERVER_PORT);

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
            LOG_DEBUG("select() timed out.");
        }
    }

    if (!tcpServer.stop()) {
        LOG_ERROR("Could not stop TCP server! Aborting.");
        return 1;
    }

    return 0;
}
