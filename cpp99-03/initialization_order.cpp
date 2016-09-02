#include <iostream>
using namespace std;

// Basic classes
class A
{
public:
    A() { std::cout << "A::ctor" << std::endl; }
    ~A() { std::cout << "~A::ctor" << std::endl; }
};

class B
{
public:
    B() { std::cout << "B::ctor" << std::endl; }
    ~B() { std::cout << "~B::ctor" << std::endl; }
};

class C
{
public:
    C() { std::cout << "C::ctor" << std::endl; }
    ~C() { std::cout << "~C::ctor" << std::endl; }
};

class D
{
public:
    D() { std::cout << "D::ctor" << std::endl; }
    ~D() { std::cout << "~D::ctor" << std::endl; }
};

class E
{
public:
    E() { std::cout << "E::ctor" << std::endl; }
    ~E() { std::cout << "~E::ctor" << std::endl; }
};

// Inheritance tree order
// First, left-to-right, classes with virtual inheritance
class Test : public A, virtual public B, public C
{
    // Declaration order 
    E m_e;
    D m_d;
public:
    Test() { std::cout << "Test::ctor" << std::endl; }
    ~Test() { std::cout << "~Test::ctor" << std::endl; }
};


int main(int argc, char const *argv[])
{
    /**
        B::ctor -> Virtual inheritance
        A::ctor -\
        C::ctor - | - non-virtual inheritance from left to right
        E::ctor -\
        D::ctor - | - fields ib Test from top to bottom 
        Test::ctor - ctor of Test class
    */
    Test t;
    return 0;
}
