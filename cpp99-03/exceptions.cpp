#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <memory>

using namespace std;

class D
{
    int i;
public:
    D() : i(0)
    {
        if(i == 1)
        {
            throw std::runtime_error("Exception in ctor");
        }
        cout << "D::D()" << endl;
    }
    D(int _i) : i(_i) { cout << "D::D(int)" << endl; }
    ~D()
    {
        if(i == 3)
        {
            // Gets warning int C++98
            throw std::runtime_error("Exception in dtor");
        }
        cout << "D::~D()" << endl;
    }
    void set(int _i) { i = _i;}
    int get() const { return i; }
};

class simpleException
{
public:
    simpleException() { cout << "init exception" << endl; }
    ~simpleException() { cout << "Dtor of an exception" << endl; }
    void what() const { cout << "WTF?" << endl; }
};

// Regenerate throw
bool isFixed = false;

void letstry()
{
    cout << "Before try" << endl;
    try
    {
        cout << "Inside try: begin" << endl;
        if (!isFixed)
        {
            throw simpleException();
        }
        else
        {
            cout << "Fixed!" << endl;
        }
        cout << "Inside try: end" << endl;
    }
    catch(const simpleException& e)
    {
        e.what();
        cout << "Generated: " << typeid(e).name() << endl;
        if (!isFixed)
        {
            isFixed = true;
            throw;
        }
    }
}

void challenge1()
{
    try
    {
        letstry();
    }
    catch (...)
    {
        if (isFixed)
        {
            cout << "Everything is okay" << endl;
        }
        else
        {
            cout << "Still not fixed! terminate()" << endl;
        }
    }
}

template<typename T>
void lestMakeLeak2_1(int i)
{
    T* p = new T();
    if(i == 0)
    {
        throw std::logic_error("Ruine challenge2");
    }
    delete p;
}

template<typename T>
void lestMakeLeak2_2(int i)
{
    std::auto_ptr<T> p(new T());
    if (i == 0)
    {
        throw std::logic_error("Ruine challenge2");
    }
}

// Check if T call dtor
template<typename T>
void challenge2()
{
    try {
        // Dtor called
        lestMakeLeak2_1<T>(10);
        // Dtor could not be called => memory leak
        lestMakeLeak2_1<T>(0);
    } catch (...) {
        cout << "Catched!" << endl;
    }
    // using smart pointer
    try {
        // Dtor called
        lestMakeLeak2_2<T>(10);
        // Dtor also called
        lestMakeLeak2_2<T>(0);
    } catch (...) {
        cout << "Catched!" << endl;
    }
}

// Test auto_ptr
template<typename T>
void challenge3()
{
    auto_ptr<T> p1(new T());
    auto_ptr<T> p2 = p1;
    // Segmentation Fault
    // cout << p1.get()->getIndex() << endl;
    // p2 owned new T(), p1 == NULL
    cout << p2.get()->getIndex() << endl;
    const auto_ptr<T> cp1(new T());
    // auto_ptr<T> cp2(cp1); // - compilation error
    // cp1.release(); // - compilation error
}

// Exceptions in ctors
template<typename T>
void challenge4()
{
    try
    {
        D obj(1);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

// Exceptions in dtors
template<typename T>
void challenge5()
{
    try
    {
        // std::unexpected()
        // B obj(T(1));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

// Exceptions and methods
template<typename T>
void f_throw(int ex_id) throw(std::logic_error, simpleException)
{
    T test(1);
    if (ex_id == 1)
    {
        throw std::logic_error("Test std::logic_error");
    }
    if (ex_id == 2)
    {
        throw simpleException();
    }
    // std::unexpected
    if(ex_id == 3)
    {
        throw std::runtime_error("std::unexpected");
    }
}

// Exceptions f() throw(...) {}
template<typename T>
void challenge6()
{
    try
    {
        // f_throw(1); // logic_error
        // f_throw(2); // simpleException
        f_throw<T>(3); // std::unexpected
    }
    catch(const std::logic_error& le)
    {
        std::cout << le.what() << std::endl;
    }
    catch(const simpleException& se)
    {
        se.what();
    }
}

// Exceptions in initializer list
template<typename T>
void challenge7() {
    try
    {
        D obj(3);
    }
    catch (const std::logic_error& le)
    {
        std::cout << "Emulation of exception in initializer list failed" << std::endl;
    }
}

// yet another bad practice to prevent memory leaks
template<typename T>
void challenge8()
{
    T* test;
    try
    {
        test = new T;
        throw std::logic_error("Logic error");
    }
    catch(...)
    {
        delete test;
    }
}
/* -------------------- */
int main() {
    // challenge1<D>();
    // challenge2<D>();
    // challenge3<D>();
    // challenge4<D>();
    // challenge5<D>();
    // challenge6<D>();
    // challenge7<D>();
    challenge8<D>();
    return 0;
}
