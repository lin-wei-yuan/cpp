#include <iostream>
#include <thread>
#include <chrono>
#include "../basic/basic_utils.h"

using basic_utils::typeof;
using basic_utils::Test;

class thread_guard
{
private:
    std::thread& m_t;
public:
    explicit thread_guard( std::thread& t )
        : m_t(t)
    {}

    ~thread_guard()
    {
        if( m_t.joinable() )
        {
            m_t.join();
        }
    }

    thread_guard( const thread_guard& ) = delete;
    thread_guard& operator=( const thread_guard& ) = delete;
};

void challenge1()
{
    // Ctor were called 3 times
    // Default ctor( default with params if we call with int param)
    Test worker; 
    // Copy ctor and move ctor( why? )
    // we pass lvalue to thread ctor and thats why worker obj is copied 
    std::thread t1{ worker };
    if( t1.joinable() )
    {
        t1.join();
    }
    // Now we have 2 forwards
    std::thread t2{ std::move(worker) };
    if( t2.joinable() )
    {
        t2.join();
    }

    // Use lambda 
    std::thread t3{ []() { std::cout << "I am lambda!" << std::endl; } };
    if( t3.joinable() )
    {
        t3.join();
    }
}

void challenge2()
{
    std::thread t{ Test() };
    thread_guard g( t );
    throw std::logic_error( "RAII" );
}

// Thread object params
struct Holder
{
    int var;
    Holder( int var_ )
        :var(var_)
    {
        std::cout << "Holder::ctor" << std::endl;
    }

    Holder()
    : Holder(0)
    {}

    ~Holder() { std::cout << "~Holder::dtor is " << var << std::endl; }
};

class A
{
public:
    A() { std::cout << "A::ctor" << std::endl; }
    ~A() { std::cout << "~A::dtor" << std::endl; }

    void thread_method( Holder val, Holder& ref, std::unique_ptr<Holder>&& ptr )
    {
        std::cout << "[thread] val is " << val.var
                  << ", ref is " << ref.var << std::endl;
        std::cout << "[thread] Wait for 5 sec...";
        std::this_thread::sleep_for( std::chrono::seconds(5) );
        std::cout << " Exit!" << std::endl;
        ref.var++;
        (*ptr).var++;
    }
};

void challenge3()
{
    A a;
    Holder val(5);
    Holder ref(10);
    Holder* ptr = new Holder(20);
    std::unique_ptr<Holder> p{ ptr };

    {
        std::thread t { &A::thread_method, &a, val, std::ref(ref), std::move(p) };
        thread_guard g{ t };
    }

    std::cout << "By ref variable is " << ref.var << std::endl;
    std::cout << "Moved pointer variable is " << ptr->var << std::endl;
}

int main(int argc, char const *argv[])
{
    // challenge1();
    // try
    // {
    //     challenge2();
    // }
    // catch( ... ) {}
    challenge3();

    return 0;
}