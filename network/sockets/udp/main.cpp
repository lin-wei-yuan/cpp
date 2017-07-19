#include <iostream>
#include <bitset>
#include <sstream>

#include "Socket.h"
using namespace network;
using namespace std;

constexpr int SERVER_PORT = 33333;

int main(int argc, char const *argv[])
{
    try
    {
        UDPSocket s("0", SERVER_PORT);
    }
    catch(const exception& ex)
    {
        cout << "Exception: " << ex.what() << endl;
    }
    return 0;
}
