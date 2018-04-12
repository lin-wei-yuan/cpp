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


void MainClientLoop()
{
    try
    {
        std::cout << cprefix << "Connecting to " << SERVER_IP << ":" << SERVER_PORT << std::endl;
        network::TCPActiveSocket client(SERVER_IP, SERVER_PORT);
        std::cout << cprefix << "Connected to " << SERVER_IP << ":" << SERVER_PORT << std::endl;
        network::Peer<network::TCPActiveSocket> peer(client);
        auto data = network::ToArray("Hello, world");
        while(true)
        {
            peer.Send(data);
            sleep(5);
        }
    }
    catch(std::exception& ex)
    {
        std::cout << cprefix << "Failed with error: " << ex.what() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    std::thread client(&MainClientLoop);

    if(client.joinable())
    {
        client.join();
    }

    return 0;
}
