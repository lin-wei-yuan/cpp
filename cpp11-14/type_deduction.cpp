#include <iostream>
#include <typeinfo>
#include <defines.h>

using namespace std;
using utils::type_name;

class Test {};

int value = 73;
// Example of methods
void f1() {}
int f2() { return 0; }
int& f3() { return value; }
int&& f4() { return std::move(value); }

template<typename T>
void print()
{
    cout << type_name<T>() << endl;
}

void challenge1()
{
    // Base types
    print<int>(); // int -> (i)
    print<unsigned int>(); // unsigned int -> (j)
    print<double>(); // double -> (d)
    print<float>(); // float -> (f)
    // Classes
    print<Test>(); // Test -> (1Test)
    // Deduction types from POD
    print<decltype(1)>(); // int -> (i)
    print<decltype(1L)>(); // long -> (l)
    print<decltype(1LL)>(); // long long -> (x)
    print<decltype(1.0)>(); // double -> (d)
    print<decltype(1.0f)>(); // float -> (f)
    // Decuction types from variables
    Test test_obj;
    int test_int = 1;
    print<decltype(test_obj)>(); // Test -> (1Test)
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

// Template type deduction
/**
    template<typename T>
    void f(ParamType param);
**/

template<typename T>
void f5(T& param)
{
    cout << "T type is " << type_name<T>() << endl;
    cout << "ParamType is " << type_name<decltype(param)>() << endl;
}

template<typename T>
void f6(const T& param)
{
    cout << "T type is " << type_name<T>() << endl;
    cout << "ParamType is " << type_name<decltype(param)>() << endl;
}

template<typename T>
void f7(T* param)
{
    cout << "T type is " << type_name<T>() << endl;
    cout << "ParamType is " << type_name<decltype(param)>() << endl;
}

template<typename T>
void f8(T&& param)
{
    cout << "T type is " << type_name<T>() << endl;
    cout << "ParamType is " << type_name<decltype(param)>() << endl;
}

template<typename T>
void f9(T param)
{
    cout << "T type is " << type_name<T>() << endl;
    cout << "ParamType is " << type_name<decltype(param)>() << endl;
}

// Get array size
template<typename T, std::size_t N>
constexpr std::size_t a_size(T (&) [N]) noexcept
{
    return N;
}

void challenge2()
{
    int x = 27; // Same as Meyers lol
    const int cx = x;
    const int& rx = x;
    int* px = &x;
    const int* cpx = &x;
    const int* const cpcx = &x;
    const char ax[] = "Test";
    // 1) ParamType is a pointer or a reference but not
    //    universal(better to say forwarding) reference
    /**
        template<typename T>
        void f(T& param);
        ...
        f(expr);
    **/
    f5(x); // ParamType deduces as int &
    f5(cx); // ParamType deduces as const int&
    f5(rx); // ParamType deduces as const int&, ignoring base ref type
    f5(ax);

    cout << endl;

    f6(x); // ParamType deduces as const int&
    f6(cx); // ParamType deduces as const int&
    f6(rx); // ParamType deduces as const int&, ignoring base ref type

    cout << endl;

    f7(&x); // ParamType deduces as int*
    f7(px); // ParamType deduces as int*
    f7(cpx); // ParamType deduces as const int*

    cout << endl;

    // So, rules for template type deduction ignors * or &
    // Lets see how it works with && and params passed by value
    f8(x); // int&
    f8(cx); // const int&
    f8(rx); // const int&
    f8(27); // int&&

    cout << endl;

    f9(x);
    f9(cx);
    f9(rx);
    f9(px);
    f9(cpx);
    f9(cpcx); // COPY of `const int* const` deduced as `const int*`.
    f9(ax); // deduced as `const int*`

    std::size_t size = a_size(ax);
    cout << "Get size of static array = " << size << endl;
}

int main(int argc, char const *argv[])
{
    // challenge1();
    challenge2();
    return 0;
}