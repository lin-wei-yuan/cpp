#include <iostream>
#include <typeinfo>
using namespace std;

// Use platform-specific lib
#ifndef OS_WINDOWS
#include <cxxabi.h>
#endif

int value = 73;
// Example of methods
void f1() {}
int f2() { return 0; }
int& f3() { return value; }
int&& f4() { return std::move(value); }

template<typename T>
void print()
{
    auto name = typeid(T).name();

#ifndef OS_WINDOWS
    int status;
    auto nname = abi::__cxa_demangle(name, 0, 0, &status);
#endif
    cout << nname << " -> (" << name << ")" << endl;
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
    print<int>(); // int -> (i)
    print<unsigned int>(); // unsigned int -> (j)
    print<double>(); // double -> (d)
    print<float>(); // float -> (f)
    // Classes
    print<A>(); // A -> (1A)
    print<B>(); // B -> (1B)
    // Deduction types from POD
    print<decltype(1)>(); // int -> (i)
    print<decltype(1L)>(); // long -> (l)
    print<decltype(1LL)>(); // long long -> (x)
    print<decltype(1.0)>(); // double -> (d)
    print<decltype(1.0f)>(); // float -> (f)
    // Decuction types from variables
    A test_obj;
    int test_int = 1;
    print<decltype(test_obj)>(); // A -> (1A)
    print<decltype(test_int)>(); // int -> (i)
    print<decltype((test_int))>(); // int -> (i)
    // Deduction function types
    print<decltype(f1)>(); // void () -> (FvvE)
    print<decltype(f1())>(); // void -> (v)
    print<decltype(f2)>(); // int () -> (FivE)
    print<decltype(f2())>(); // int -> (i)
    // Lvalue and rvalue references
    print<decltype(f3)>(); // int& () -> (FRivE)
    print<decltype(f3())>(); // int -> (i)
    print<decltype(f4)>(); // int&& () -> (FOivE)
    print<decltype(f4())>(); // int -> (i)
    // Pointers
    int aa = 2;
    int* p = &aa;
    int* np = p;
    int** npp = &np;
    int*** nppp = &npp;
    print<decltype(p)>(); // int* -> (Pi)
    print<decltype(np)>(); // int* -> (Pi)
    print<decltype(npp)>(); // int** -> (PPi)
    print<decltype(nppp)>(); // int*** -> (PPPi)
    // Templates
    print<decltype(print<int>)>();
}

int main(int argc, char const *argv[])
{
    challenge1();
    return 0;
}