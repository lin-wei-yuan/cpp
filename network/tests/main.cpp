#define TCP
#include <iostream>
#include <thread>

#ifdef TCP
#include <tcp_sock.h>
#else
#include <udp_sock.h>
#endif

#include <peer_sock.h>

constexpr int BUFFER_SIZE = 1500;
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
    std::thread server(&MainServerLoop);
    std::thread client(&MainClientLoop);

    if(server.joinable())
    {
        server.join();
    }

    if(client.joinable())
    {
        client.join();
    }

    return 0;
}
