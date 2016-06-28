#include <iostream>
using namespace std;

class hello
{
public:
    hello()
    {
        cout << "ctor hello" << endl;
    }
    ~hello()
    {
        cout << "dtor hello" << endl;
    }
};
