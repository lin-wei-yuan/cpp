#ifndef __UDP_SOCK_H__
#define __UDP_SOCK_H__

#include "fd_sock.h"

#include <iostream>
#include <strings.h> // bzero
#include <unistd.h> // close

namespace network {
/*
    PassiveSocket class usually represents server side socket aka master socket.
*/
template<typename TSocketHolder> class PassiveSocket;
/*
    ActiveSocket class usually represents client side socket aka slave socket.
*/
template<typename TSocketHolder> class ActiveSocket;

typedef SocketHolder<AF_INET, SOCK_DGRAM, IPPROTO_UDP> UDPProto;
typedef ActiveSocket<UDPProto> UDPActiveSocket;
typedef PassiveSocket<UDPProto> UDPPassiveSocket;

template<typename TSocketHolder>
class PassiveSocket
{
public:
    PassiveSocket(const std::string& local_ip = std::string(), uint16_t local_port = 0)
    : m_sock_ip(local_ip)
    , m_sock_port(local_port)
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

    int Receive(void* buffer, size_t buffer_size, std::string& remote_ip, uint16_t& remote_port)
    {
        struct sockaddr_storage storage;
        unsigned int size = sizeof(storage);
        int status = recvfrom(m_socket.GetFD(), buffer, buffer_size, 0, (struct sockaddr *)&storage, &size);
        struct sockaddr_in *sin = (struct sockaddr_in *)&storage;
        unsigned char *ip = (unsigned char *)&sin->sin_addr.s_addr;

        remote_ip = std::to_string(ip[0])
                    .append(".")
                    .append(std::to_string(ip[1]))
                    .append(".")
                    .append(std::to_string(ip[2]))
                    .append(".")
                    .append(std::to_string(ip[3]));
        remote_port = ntohs(sin->sin_port);
        return status;
    }

    int Send(const void* buffer, size_t buffer_size, const std::string& remote_ip, uint16_t remote_port)
    {
        struct sockaddr_in sock_addr;
        int slen = sizeof(sock_addr);
        bzero((char *) &sock_addr, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(remote_port);
        sock_addr.sin_addr.s_addr = inet_addr(remote_ip.c_str());
        return sendto(m_socket.GetFD(), buffer, buffer_size, 0, (struct sockaddr *) &sock_addr, slen);
    }

private:
    TSocketHolder   m_socket;
    std::string     m_sock_ip;
    uint16_t        m_sock_port;
};

template<typename TSocketHolder>
class ActiveSocket
{
public:
    ActiveSocket(const std::string& ip = std::string(), uint16_t port = 0)
    : m_sock_ip(ip)
    , m_sock_port(port)
    {}

    int Receive(void* buffer, size_t buffer_size, std::string& remote_ip, uint16_t& remote_port)
    {
        remote_ip = "0";
        remote_port = 0;
        return recvfrom(m_socket.GetFD(), buffer, buffer_size, 0, nullptr, nullptr);
    }

    int Send(const void* buffer, size_t buffer_size, const std::string& remote_ip, uint16_t remote_port)
    {
        struct sockaddr_in sock_addr;
        int slen = sizeof(sock_addr);
        bzero((char *) &sock_addr, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(remote_port);
        sock_addr.sin_addr.s_addr = inet_addr(remote_ip.c_str());
        return sendto(m_socket.GetFD(), buffer, buffer_size, 0, (struct sockaddr *) &sock_addr, slen);
    }

private:
    TSocketHolder   m_socket;
    std::string     m_sock_ip;
    uint16_t        m_sock_port;
};

} // end of namespace network

#endif // __UDP_SOCK_H__
