// Socket
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// bzero
#include <strings.h>
// close
#include <unistd.h>

namespace network {

constexpr int ERROR_STATE = -1;
constexpr int AUTO_PROTO = 0;
constexpr int BUFFER_LEN = 512; // bits

template<int DOMAIN, int TYPE, int PROTO>
class SocketHolder
{
public:
    SocketHolder()
    : m_fd(socket(DOMAIN, TYPE, PROTO))
    {
        if (m_fd == ERROR_STATE)
        {
            throw std::runtime_error("Socket creation failed");
        }
    }

    int GetFD() const { return m_fd; }
    int GetErrno() const { return errno; }

    ~SocketHolder()
    {
        close(m_fd);
    }
private:
    int m_fd;
};

typedef SocketHolder<AF_INET, SOCK_DGRAM, AUTO_PROTO> UDP;

template<typename TSocketHolder>
class Socket
{
public:
    Socket(const std::string& ip = std::string(), uint16_t port = 0)
    : m_sock_ip(ip)
    , m_sock_port(port)
    {
        struct sockaddr_in sock_addr;
        bzero((char *) &sock_addr, sizeof(sock_addr));
        if (m_sock_ip.empty() || m_sock_ip == "0")
        {
            sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else
        {
            sock_addr.sin_addr.s_addr = inet_addr(m_sock_ip.c_str());
        }

        sock_addr.sin_port = htons(m_sock_port);
        sock_addr.sin_family = AF_INET;

        if (ERROR_STATE == bind(m_socket.GetFD(), (struct sockaddr *)&sock_addr, sizeof(sock_addr)))
        {
            throw std::runtime_error("Socket binding failed");
        }
    }

    int Receive(void* buffer, size_t buffer_size)
    {
        struct sockaddr_in sock_addr;
        int slen = sizeof(sock_addr);
        return recvfrom(m_socket.GetFD(), buffer, buffer_size, 0, (struct sockaddr*)&sock_addr, (socklen_t*)&slen);
    }

    int Send(const void* buffer, size_t buffer_size, const std::string& dest_ip, uint16_t dest_port)
    {
        struct sockaddr_in sock_addr;
        int slen = sizeof(sock_addr);
        bzero((char *) &sock_addr, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(dest_port);
        sock_addr.sin_addr.s_addr = inet_addr(dest_ip.c_str());
        return sendto(m_socket.GetFD(), buffer, buffer_size, 0, (struct sockaddr *) &sock_addr, slen);
    }

private:
    TSocketHolder   m_socket;
    std::string     m_sock_ip;
    uint16_t        m_sock_port;

};

typedef Socket<UDP> UDPSocket;

} // end of namespace network