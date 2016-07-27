// Socket
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// Memset
#include <string.h>
#include <iostream>

constexpr int DOMAIN = AF_INET; // IPv4s
constexpr int TYPE = SOCK_DGRAM; // UDP 
constexpr int PROTO = IPPROTO_UDP;
constexpr int BUFFER_LEN = 512; // bits

struct CPacket
{
    std::string address;
    int port;
    char data[BUFFER_LEN];
};

class CSocket
{
public:
    CSocket( uint16_t port, const std::string& ip = std::string() )
        : m_port( port )
        , m_ip( ip )
    {
        if( !Initialize() )
        {
            throw std::logic_error( "Failed creating socket" );
        }

        if( !BindSocket() )
        {
            throw std::logic_error( "Failed binding socket" );
        }
    }

    ~CSocket()
    {
        // close( m_socket );
    }
private:
    std::string m_ip;
    uint16_t m_port;

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
        m_server_sock.sin_port = htons( m_port );
        if( m_ip.empty() )
        {
            m_server_sock.sin_addr .s_addr = htonl( INADDR_ANY );
        }
        else
        {
            inet_aton( m_ip.c_str(), &m_server_sock.sin_addr );
        }
        
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
        socklen_t socket_length = sizeof( m_client_sock );
        int len = recvfrom( m_socket, buffer, BUFFER_LEN, 0,
                            ( struct sockaddr * ) &m_client_sock,
                            &socket_length );
        CPacket packet;
        packet.address = std::string( inet_ntoa( m_client_sock.sin_addr ) );
        packet.port = ntohs( m_client_sock.sin_port );
        for (int i = 0; i < BUFFER_LEN; ++i)
        {
            packet.data[i] = buffer[i];
        }
        return std::move( packet );
    }
};