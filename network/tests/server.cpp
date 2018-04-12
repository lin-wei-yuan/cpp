#define TCP
#include <iostream>
#include <thread>
#include <signal.h>

#ifdef TCP
#include <tcp_sock.h>
#else
#include <udp_sock.h>
#endif

#include <peer_sock.h>

constexpr int BUFFER_SIZE = 255;
constexpr const char * SERVER_IP = "192.168.1.36";
constexpr int SERVER_PORT = 33333;
constexpr const char * sprefix = "[MainServerLoop] ";
constexpr const char * cprefix = "[MainClientLoop] ";

void MainServerLoop()
{
    while(true)
    {
        try
        {
            network::TCPPassiveSocket server("0", SERVER_PORT);

            while(true)
            {
                std::cout << sprefix << "Waiting connection..." << std::endl;
                auto client = server.WaitConnection();
                std::cout << sprefix << "Client [" << client.first << ":"
                          << client.second << "] connected." << std::endl;
                network::Peer<network::TCPPassiveSocket> peer(server);
                while(true)
                {
                    auto data = peer.Receive();
                    std::cout << sprefix << "Received data: " << network::ToString(data) << std::endl;
                }
            }
        }
        catch(std::exception& ex)
        {
            std::cout << sprefix << "Failed with error: " << ex.what() << std::endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    std::thread server(&MainServerLoop);

    if(server.joinable())
    {
        server.join();
    }

    return 0;
}
