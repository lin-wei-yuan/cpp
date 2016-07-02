#include <iostream>
#include <typeinfo>
using namespace std;

// Use platform-specific lib
#ifndef OS_WINDOWS
#include <cxxabi.h>
#endif

void f1() {}
int f2() { return 0; }

template<typename T>
void print()
{
    auto name = typeid(T).name();

#ifndef OS_WINDOWS
    int status;
    name = abi::__cxa_demangle(name, 0, 0, &status);
#endif
    cout << name << endl;
}

class A
{
public:
    A() {}
    ~A() {}
};

class B : public A
{
public:
    B() {}
    ~B() {}
};

void challenge1()
{
    // Base types 
    print<int>();
    print<unsigned int>();
    print<double>();
    print<float>();
    // Classes
    print<A>();
    print<B>();
    // Deduction types from rvalue
    print<decltype(1)>();
    print<decltype(1L)>();
    print<decltype(1LL)>();
    print<decltype(1.0)>();
    print<decltype(1.0f)>();
    // Decuction types from variables
    A test_obj;
    int test_int = 1;
    print<decltype(test_obj)>();
    print<decltype(test_int)>();
    print<decltype((test_int))>();

    print<decltype(f1)>();
    print<decltype(f1())>();
    print<decltype(f2)>();
    print<decltype(f2())>();
}

int main(int argc, char const *argv[])
{
    challenge1();
    return 0;
}