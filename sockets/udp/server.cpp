
#include "CSocket.h"
#include <bitset>
#include <sstream>

constexpr int SERVER_PORT = 3334;


struct SSyncPacket
{
    uint32_t proto;
    uint32_t session_id;
    uint64_t timestamp;
};


int main(int argc, char const *argv[])
{
    std::cout << sizeof(SSyncPacket) << std::endl;
    try
    {
        CSocket s( SERVER_PORT );
        while( true )
        {
            auto packet = s.ReceiveData();
            SSyncPacket data;
            memcpy(&data, packet.data, sizeof(data));
            // Get proto name 
            std::bitset<32> bset( data.proto );
            std::string str_repr = bset.to_string();
            std::stringstream sstream(str_repr);
            std::string output;
            while(sstream.good())
            {
                std::bitset<8> bits;
                sstream >> bits;
                char c = char(bits.to_ulong());
                output += c;
            }
            // Get timestamp
            std::cout << "[" << packet.address << ":" << packet.port << "]" 
                      << output << " " << data.session_id << " " 
                      << data.timestamp << std::endl;
        }
    }
    catch( const std::exception& ex )
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    return 0;
}
