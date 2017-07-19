#include "defines.h"

int main(int argc, char const *argv[])
{
    try
    {
        cout << "Slave socket." << endl;
        Peer<UDPSocket> slave(SLAVE_PORT);
        cout << "Command from master = [" << slave.Receive() << "]" << endl;
    }
    catch(const exception& ex)
    {
        cout << "Exception: " << ex.what() << endl;
    }
    return 0;
}
