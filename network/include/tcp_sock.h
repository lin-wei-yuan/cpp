#ifndef __TCP_SOCK_H__
#define __TCP_SOCK_H__

#include "fd_sock.h"

#include <iostream>
#include <strings.h> // bzero
#include <unistd.h> // close

namespace network {

constexpr int TCP_CONNECTION_Q_SIZE = 5;
/*
    PassiveSocket class usually represents server side socket aka master socket.
*/
template<typename TSocketHolder> class PassiveSocket;
/*
    ActiveSocket class usually represents client side socket aka slave socket.
*/
template<typename TSocketHolder> class ActiveSocket;

using TCPProto = SocketHolder<AF_INET, SOCK_STREAM, 0>;
typedef ActiveSocket<TCPProto> TCPActiveSocket;
typedef PassiveSocket<TCPProto> TCPPassiveSocket;

template<typename TSocketHolder>
class PassiveSocket
{
public:
    PassiveSocket(const std::string& ip = std::string(), uint16_t port = 0)
    : m_sock_ip(ip)
    , m_sock_port(port)
    {
        struct sockaddr_in sock_addr;
        bzero((char *) &sock_addr, sizeof(sock_addr));
        if(m_sock_ip.empty() || m_sock_ip == "0")
        {
            sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else
        {
            sock_addr.sin_addr.s_addr = inet_addr(m_sock_ip.c_str());
        }

        sock_addr.sin_port = htons(m_sock_port);
        sock_addr.sin_family = AF_INET;

        if(0 > bind(m_socket.GetFD(), (struct sockaddr *)&sock_addr, sizeof(sock_addr)))
        {
            throw std::runtime_error("Socket binding failed");
        }
    }

    std::pair<std::string, uint16_t> WaitConnection()
    {
        struct sockaddr_in remote_addr;
        unsigned int slen = sizeof(remote_addr);
        bzero((char *) &remote_addr, sizeof(remote_addr));
        listen(m_socket.GetFD(), TCP_CONNECTION_Q_SIZE);
        m_remote_socket = accept(m_socket.GetFD(), (struct sockaddr*)&remote_addr, &slen);
        if(0 > m_remote_socket.GetFD())
        {
            throw std::runtime_error("Socket accepting failed");
        }
        return std::make_pair(inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));
    }

    int Receive(void* buffer, size_t buffer_size)
    {
        return read(m_remote_socket.GetFD(), buffer, buffer_size);
    }

    int Send(const void* buffer, size_t buffer_size)
    {
        return send(m_remote_socket.GetFD(), buffer, buffer_size, 0);
    }
private:
    TSocketHolder   m_socket;
    TSocketHolder   m_remote_socket;
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
    {
        struct sockaddr_in sock_addr;
        bzero((char *) &sock_addr, sizeof(sock_addr));
        sock_addr.sin_addr.s_addr = inet_addr(m_sock_ip.c_str());
        sock_addr.sin_port = htons(m_sock_port);
        sock_addr.sin_family = AF_INET;
        if(0 > connect(m_socket.GetFD(), (struct sockaddr*)&sock_addr, sizeof(sock_addr)))
        {
            throw std::runtime_error("Socket connection failed");
        }
    }

    int Receive(void* buffer, size_t buffer_size)
    {
        return read(m_socket.GetFD(), buffer, buffer_size);
    }

    int Send(const void* buffer, size_t buffer_size)
    {
        return write(m_socket.GetFD(), buffer, buffer_size);
    }

private:
    TSocketHolder   m_socket;
    std::string     m_sock_ip;
    uint16_t        m_sock_port;
};

} // end of namespace network

#endif // __TCP_SOCK_H__
