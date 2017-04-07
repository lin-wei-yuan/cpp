#include <iostream>
#include <vector>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A::A" << endl;
    }
    virtual void foo()
    {
        cout << "A::foo" << endl;
    }
    virtual void baz()
    {
        cout << "A::baz" << endl;
    }
    void bar()
    {
        cout << "A::bar" << endl;
    }
    virtual ~A()
    {
        cout << "A::~A" << endl;
    }
};

class B : public A
{
public:
    B()
    {
        cout << "B::B" << endl;
    }
    void foo()
    {
        cout << "B::foo" << endl;
    }
    void baz()
    {
        cout << "B::baz" << endl;
    }
    void bar()
    {
        cout << "B::bar" << endl;
    }
    virtual ~B()
    {
        cout << "B::~B" << endl;
    }
};

class Base
{
public:
    virtual void print() const = 0;
    virtual ~Base() {}
};

class Derived_1 : public Base
{
public:
    void print_2();
};

class Derived_2 : public Base
{
public:
    void print() const {};
};

template<typename T>
class D
{
    T first;
    T second;
public:
    D()
    : first(), second()
    {
        cout << "D::D()" << endl;
    }
    virtual ~D()
    {
        cout << "D::~D()" << endl;
    }
    virtual void print() const
    {
        cout << "D::print() const" << endl;
    }
    void print_2() const
    {
        cout << "D::print_2() const" << endl;
    }
};

template<typename T>
class E : public D<T>
{
    T third;
    T fourth;
public:
    E(): third(), fourth()
    {
        cout << "E::E()" << endl;
    }
    virtual ~E()
    {
        cout << "E::~E()" << endl;
    }
    virtual void print() const
    {
        cout << "E::print() const" << endl;
    }
    void print_2() const
    {
        cout << "E::print_2() const" << endl;
    }
};

void challenge1()
{
    std::vector<D<A>*> v;
    v.push_back(new D<A>);
    v.push_back(new E<A>);

    for (size_t i = 0; i < v.size(); ++i)
    {
        v.at(i)->print();
        v.at(i)->print_2();
        delete v.at(i);
    }
}

void challenge2()
{
    // Base* test = new Derived_1; // abstract
    Base* test = new Derived_2;
    delete test;
}

void challenge3()
{
    A* obj = new B;
    obj->foo();
    obj->baz();
    obj->bar();
    delete obj;
}

int main()
{
    // challenge1();
    // challenge2();
    challenge3();
    return 0;
}
