#include "Socket.h"
#include <vector>
#include <cmath>

namespace network {

#define DEBUG_

constexpr size_t BUFFER_SIZE = 512; //bytes

template<typename TSocket>
class Peer
{
public:

    Peer( uint16_t src_port )
    : m_receiver("0", src_port)
    , m_src_port(src_port)
    {}

    void SetDestinationPeer(const std::string& ip, uint16_t port)
    {
        m_dest_ip = ip;
        m_dest_port = port;
    }

    void Send(const std::string& cmd)
    {
        std::vector<char> symbols;
        for(auto ch: cmd)
        {
            symbols.push_back(ch);
        }
        symbols.push_back('\0');
        size_t chunk_count{(size_t)ceil(symbols.size() / BUFFER_SIZE + 0.5)};
        #ifdef DEBUG_
        std::cout << "Chunks: " << chunk_count << std::endl;
        #endif
        std::vector<std::vector<char>> chunks(chunk_count);
        for(size_t index = 0; index < chunk_count; ++index)
        {
            for(size_t buf_index = 0; buf_index < BUFFER_SIZE; ++buf_index)
            {
                if(index * BUFFER_SIZE + buf_index < symbols.size())
                {
                    chunks.at(index).push_back(symbols.at(index * BUFFER_SIZE + buf_index));
                }
            }
        }
        // Split to
        for(const auto& chunk: chunks)
        {
            #ifdef DEBUG_
            std::cout << "Send chunk with size " << chunk.size() << std::endl;
            #endif
            m_sender.Send(chunk.data(), chunk.size(), m_dest_ip, m_dest_port);
        }
    }

    std::string Receive()
    {
        std::string response;
        bool isEOS = false;
        while(!isEOS)
        {
            char buffer[BUFFER_SIZE];
            m_receiver.Receive(buffer, BUFFER_SIZE);
            for(size_t i = 0; i < BUFFER_SIZE; ++i)
            {
            #ifdef DEBUG_
                std::cout << "Sym [" << buffer[i] << "] = " << (int)buffer[i] << std::endl;
            #endif
                if((int)buffer[i] > 0)
                {
                #ifdef DEBUG_
                    std::cout << "Appended " << buffer[i] << std::endl;
                #endif
                    response += buffer[i];
                }
                else if((int) buffer[i] == 0)
                {
                    #ifdef DEBUG_
                        std::cout << "Found end of string" << std::endl;
                    #endif
                        isEOS = true;
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        return response;
    }

private:
    TSocket     m_sender;
    TSocket     m_receiver;
    uint16_t    m_src_port;
    std::string m_dest_ip;
    uint16_t    m_dest_port;
};

} // end of namespace network