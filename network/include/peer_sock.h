#ifndef __PEER_SOCK_H__
#define __PEER_SOCK_H__

#include <iostream>
#include <vector>

namespace network {

typedef std::vector<char> CharBuffer;
constexpr int BUFFER_SIZE = 1500;

inline CharBuffer ToArray(const std::string& cmd)
{
    CharBuffer symbols;
    for(const auto ch: cmd)
    {
        symbols.push_back(ch);
    }
    symbols.push_back('\0');
    return symbols;
}

inline std::string ToString(const CharBuffer& buffer)
{
    std::string symbols;
    for(const auto ch: buffer)
    {
        if((int)ch > 0)
        {
            symbols += ch;
        }
    }
    return symbols;
}

template<typename TSocket>
class Peer
{
public:
    Peer(const TSocket& sock)
    : m_socket(sock)
    {}

    void Send(const CharBuffer& data)
    {
        size_t size = data.size();
        for(size_t i = 0; i < size; i += BUFFER_SIZE)
        {
            size_t tmp = ((size - i) >= BUFFER_SIZE) ? BUFFER_SIZE : (size - i);
            const char* pointer = &(*(data.begin() + i));
            if(0 > m_socket.Send(pointer, tmp))
            {
                throw std::logic_error("Failed to sent data. Errno is " + std::to_string(errno));
            }
        }
    }

    CharBuffer Receive()
    {
        char buffer[BUFFER_SIZE];
        int status = m_socket.Receive(buffer, BUFFER_SIZE);
        if(status == -1)
        {
            throw std::logic_error("Receiving data failed. Errno is " + std::to_string(errno));
        }
        return std::vector<char>(std::begin(buffer), std::begin(buffer) + status);
    }

private:
    TSocket m_socket;
};

} // end of namespace network

#endif // __PEER_SOCK_H__
