#include <iostream>
#include <stdexcept>

class Base
{};

template<typename T>
class A
{
    T obj;
public:
    A()
    {
        std::cout << "Default A::ctor" << std::endl;
    }

    A(const A &_obj)
    {
        throw std::logic_error("From copy A::ctor");
    }

    A(T &&_obj)
        : obj(std::move(_obj))
    {
        throw std::logic_error("From move A::ctor");
    }

    ~A()
    {
        std::cout << "~A::dtor" << std::endl;
    }
};

template<typename T>
class B
{
    T obj;
public:
    B(T &&_obj)
        : obj(std::move(_obj))
    {
        std::cout << "B::ctor called" << std::endl;
    }

    ~B()
    {
        std::cout << "~B():dtor called" << std::endl;
        throw std::logic_error("From B:dtor");
    }
};

template<typename T>
class C
{
    T obj;
public:

    C() try
:
        obj(std::move(T()))
    {
        std::cout << "C::ctor called " << std::endl;
    }
    catch (const std::logic_error &le)
    {
        std::cout << "C::C() cathed: " << le.what() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    A<Base> a;
    B<Base> b(Base());
    C<A<Base>> c;
    return 0;
}