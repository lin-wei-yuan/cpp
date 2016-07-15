#include <iostream>
#include <stdexcept>

class A
{
    T obj;
public:
    A()
    {
        std::cout << "Default A::ctor" << std::endl;
    }

    A( const A& _obj )
    {
        throw std::logic_error("From copy A::ctor");
    }

    A(T&& _obj)
        : obj( std::move( _obj ) )
    {
        throw std::logic_error("From move A::ctor");
    }

    ~A()
    {
        std::cout << "~A::dtor" << std::endl;
    }
};

class B
{
    T obj;
public:
    B( T&& _obj )
        : obj( std::move( _obj ) )
    {
        std::cout << "B::ctor called" << std::endl;
    }
    
    ~B()
    {
        throw std::logic_error( "From B:dtor" );
        std::cout << "~B():dtor called" << std::endl;
    }
};

class C
{
    A obj;
public:
    C() try
        : obj( std::move( A() ) )
    {
        std::cout << "C::ctor called " << std::endl;
    }
    catch( const std::logic_error& le )
    {
        std::cout << "C::C() cathed: " << le.what() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    A a;
    B b;
    C c;
    return 0;
}