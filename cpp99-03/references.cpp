#include <iostream>
#include <vector>
using namespace std;

template<typename T>
inline T tempf()
{
    return T(2);
}

// Memory leak!
template<typename T>
inline T& tempr()
{
    return *(new T(4));
}

template<typename T>
void challenge1()
{
    T temp = 4;
    // compile error
    // T& temp0 = 5; // T(5) - temprorary object
    // works
    T& temp1 = temp;
    cout << temp1.get() << endl;

    // compile error
    // T& temp2 = tempf();
    T temp2 = tempf<T>();
    T& temp3 = temp2;
    cout << temp2.get() << endl;
    cout << temp3.get() << endl;

    // work
    T& temp4 = tempr<T>();
    // Do not forget fix memory leak
    delete &temp4;

    const T& temp5 = 5;

    // lol
    // const T& const temp6 = 6; //cannot be applied
    // T& const temp6 = 6; //cannot be applied
}

class Base
{
public:
    Base(int i)
    : m_int(i)
    {}

    ~Base() {}

    int get() const { return m_int; }

protected:
    int m_int;
};

int main()
{
    challenge1<Base>();
    return 0;
}
