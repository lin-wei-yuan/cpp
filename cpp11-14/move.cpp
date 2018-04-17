#include <iostream>
#include <memory>
#include <string>
#include <defines.h>
using namespace std;

class Test
{
public:
    Test(int i) {};
};

// Swap implementation that make a lot of copies
// variable temp + 2 copies(A::operator=())
template<class T>
void swap_copy(T &first, T &second) // <- without const
{
    // Copy ctor called
    T temp(first); // temp contains copy of object with id 1
    // a.operator=(T& b); <- without const
    first = second; // <- 'first' contains copy of object with id 2
    // b.operator=(temp);
    second = temp; //  <- second contains copy of object with id 1
}

// Swap implementation that use move semantic
// 1 object creation
template<class T>
void swap_move(T &first, T &second)
{
    // Create variable for storing 'first' variable
    // 'first' now in unspecified BUT valid state (17.6.5.15 [lib.types.movedfrom])
    T temp(std::move(first));
    // 'first' now specified and contain 'second'
    // 'second' now is unspecified but in valid state
    first = std::move(second);
    // 'first' and 'second' now are both specified
    // 'temp' unspecified and will be destroyed
    second = std::move(temp);
}

// How perfect forwarding works
class A
{
public:
    A(int i_) : i(i_) {}

private:
    int i;
};

class D
{
public:
    D()
    {
        cout << "D::ctor" << endl;
    }

    D(A &p1)
    {
        cout << "D(A&)::ctor" << endl;
    }

    D(int p1, double p2)
    {
        cout << "D(int, double)::ctor" << endl;
    }

    D(int p1, double p2, const std::string &p3)
    {
        cout << "D( int, double, string)::ctor" << endl;
    }
};

// Shared ptr factory without parameters
// template<typename T>
// std::shared_ptr<T>
// make_shared()
// {
//     return std::shared_ptr<T>( new T );
// }

// template<typename T, typename P1>
// std::shared_ptr<T>
// make_shared( const P1& p )
// {
//     return std::shared_ptr<T>( new T(p) );
// }

template<class T, class P1>
std::shared_ptr<T>
make_shared(P1 &&p)
{
    return std::shared_ptr<T>(new T(std::forward<P1>(p)));
}

// --------------------------------------------
void challenge1()
{
    Test first(1);
    Test second(2);
    swap_copy(first, second);
}

void challenge2()
{
    Test third(3);
    Test fourth(4);
    swap_move(third, fourth);
}

void challenge3()
{
    // auto sp = make_shared<Test>();
    // auto dsp0 = make_shared<D>();
    A i = 1;
    // Uses make_shared( const P1& p ) and creates D object with non-const A& reference
    // auto dsp1 = make_shared<D>( i );
    // Caused compile-time error
    // Because we convert rvalue to non-const ref
    auto dsp2 = make_shared<D>(i);
}

int main(int argc, char const *argv[])
{
    challenge1();
    challenge2();
    challenge3();
    return 0;
}
