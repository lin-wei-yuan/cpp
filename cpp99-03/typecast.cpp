#pragma GCC diagnostic ignored "-Wunused-variable"

#include <iostream>
#include <typeinfo>
using namespace std;

class D
{
    int i;
public:
    D() : i(0) { cout << "D::D()" << endl; }
    D(int _i) : i(_i) { cout << "D::D(int)" << endl; }
    ~D() { cout << "D::~D()" << endl; }
    void set(int _i) { i = _i;}
    int get() const { return i; }
};

class E : public D
{
    double d;
public:
    E() : d(0.0) { cout << "E::E()" << endl; }
    E(double _d) : d(_d) { cout << "E::E(double)" << endl; }
    ~E() { cout << "E::~E()" << endl; }
    void set(double _d) { d = _d;}
    double get() const { return d; }
};

// Const cast
void challenge0()
{
    const D* d = new D(1);
    // d->set(2);
    D* d1 = const_cast<D*>(d);
    d1->set(2);
    // *i = 'T';
    cout << d1->get() << ", " << d->get() << endl;
    delete d;
}
// Static_cast
void challenge1()
{
    // basic types
    int ii = 10;
    double test = 10;
    double dd = static_cast<double>(ii);
    float tmp_f = static_cast<float>(ii);
    cout << typeid(ii).name() << "["<< ii << "], "
         << typeid(dd).name() << "["<< dd << "], "
         << typeid(tmp_f).name() << "["<< tmp_f << "], " << test << endl;

    // User types
    // Upcast
    E* e1 = new E(0.1);
    D* d1 = static_cast<D*>(e1);
    cout << e1->get() << ", " << d1->get() << endl;
    delete e1;
    // downcast
    // undefined behavior
    D* d2 = new D(2);
    E* e2 = static_cast<E*>(d2);
    cout << d2->get() << ", " << e2->get() << endl;
    delete d2;
}

class nonVirtual {
public:
    nonVirtual() { cout << "nonVirtual::nonVirtual()" << endl; }
    ~nonVirtual() { cout << "nonVirtual::~nonVirtual()" << endl; }
};

class AnonVirtual : public nonVirtual {
public:
    AnonVirtual() { cout << "AnonVirtual::AnonVirtual()" << endl; }
    ~AnonVirtual() { cout << "AnonVirtual::~AnonVirtual()" << endl; }
};
class BnonVirtual : public AnonVirtual
{
public:
    BnonVirtual() { cout << "BnonVirtual::BnonVirtual()" << endl; }
    ~BnonVirtual() { cout << "BnonVirtual::~BnonVirtual()" << endl; }
};

class Base {
public:
    Base() { cout << "Base::Base()" << endl; }
    virtual ~Base() { cout << "Base::~Base()" << endl; }
    virtual void print() { cout << "Base::print()" << endl; }
};

class A : public Base
{
public:
    A() { cout << "A::A()" << endl; }
    virtual ~A() { cout << "A::~A()" << endl; }
    virtual void print() { cout << "A::print()" << endl; }
};

class B : public A
{
public:
    B() { cout << "B::B()" << endl; }
    virtual ~B() { cout << "B::~B()" << endl; }
    virtual void print() { cout << "B::print()" << endl; }
};

void challenge2()
{
    // Use non polymorphic classes
    // source type is not polymorphic - compile error
    // nonVirtual* nv = new nonVirtual();
    // BnonVirtual* bnv = dynamic_cast<BnonVirtual*>(nv);

    // Use polymorphic
    // Upcasting(from derived class to base)
    B* b = new B;
    Base* tmp_base = new Base;
    if (Base* base = dynamic_cast<Base*>(b))
    {
        base->print();
    }
    else
    {
        cout << "base is null" << endl;
    }
    // Crosscasting
    if (A* a = dynamic_cast<A*>(b))
    {
        a->print();
    }
    else
    {
        cout << "a is null" << endl;
    }
    // Downcasting
    // tmp_b == null
    if (B* tmp_b = dynamic_cast<B*>(tmp_base))
    {
        tmp_b->print();
    }
    else
    {
        cout << "tmp_b is null" << endl;
    }
    delete b;
}

typedef void(B::*pmemory)();
typedef void(Base::*pmemory_polymoph)();

// Pointer to member
void challenge3()
{
    B* b = new B;
    pmemory p = &B::print;
    b->print(); // direct call
    (b->*p)();
    delete b;
    // Polymorph classes
    Base* base = new B;
    pmemory_polymoph pp = &Base::print;
    base->print();
    (base->*pp)();
    delete base;
}

int main() {
    // challenge0();
    // challenge1();
    // challenge2();
    challenge3();
    return 0;
}
