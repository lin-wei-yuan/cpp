#include "defines.h"

int main(int argc, char const *argv[])
{
    try
    {
        cout << "Master socket." << endl;
        Peer<UDPSocket> master(SERVER_PORT);
        cout << "Write command: ";
        std::string symbol;
        cin >> symbol;
        cout << "Command is [" << symbol << "]" << endl;
        cout << "Repeating: ";
        int repeats{0};
        cin >> repeats;
        string cmd;
        for (int i = 0; i < repeats; ++i)
        {
            cmd += symbol;
        }
        master.SetDestinationPeer("0", 33334);
        master.Send(cmd);
    }
    catch(const exception& ex)
    {
        cout << "Exception: " << ex.what() << endl;
    }
    return 0;
}
