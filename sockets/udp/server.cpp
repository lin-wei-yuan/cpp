// Socket
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// Memset
#include <string.h>

constexpr int DOMAIN = AF_INET; // IPv4s
constexpr int TYPE = SOCK_DGRAM; // UDP 
constexpr int PROTO = IPPROTO_UDP;

constexpr int BUFFER_LEN = 512; // bits
constexpr int PORT = 3333; // Server port

struct CPacket
{
    std::string address;
    int port;
    std::string data;
};

class CSocket
{
public:
    CSocket()
    {
        if( Initialize() )
        {
            throw std::logic_error( "Failed creating socket" );
        }

        if( BindSocket() )
        {
            throw std::logic_error( "Failed binding socket" );
        }
    }
    ~CSocket() {}
private:
    int m_socket;
    struct sockaddr_in m_server_sock;
    struct sockaddr_in m_client_sock;

    bool Initialize()
    {
        m_socket = socket( DOMAIN, TYPE, PROTO );
        return m_socket != -1;
    }

    bool BindSocket()
    {
        // Zero out
        memset( (char *) &m_server_sock, 0, sizeof(m_server_sock) );
        // Init
        m_server_sock.sin_family = DOMAIN;
        m_server_sock.sin_port = htons( PORT );
        m_server_sock.sin_addr .s_addr = htonl( INADDR_ANY );
        // Bind
        int bind_result = bind( m_socket, 
                                ( struct sockaddr * ) &m_server_sock, 
                                sizeof(m_server_sock )
                            );
        return bind_result != -1;
    }

public:
    CPacket ReceiveData()
    {
        char buffer[BUFFER_LEN];
        int socket_length = sizeof( m_client_sock );
        int len = recvfrom( m_socket, buffer, BUFFER_LEN, 0,
                            ( struct sockaddr * ) &m_client_sock,
                            &socket_length );
        CPacket packet;
        packet.address = std::string( inet_ntoa( m_client_sock.sin_addr ) );
        packet.port = ntohs( m_client_sock.sin_port );
        packet.data = std::string( buffer );
        return std::move( packet );
    }

};


int main(int argc, char const *argv[])
{
    try
    {
        CSocket s;
        while( true )
        {
            auto packet = s.ReceiveData();
            std::cout << "Incoming data: " << packet.data << std::endl;
        }
    }
    catch( const std::exception& ex )
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    return 0;
}
}