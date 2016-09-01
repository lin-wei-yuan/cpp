#include <iostream>
#include <thread>
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
class A : public Test
{
public:
    A() { std::cout << "A::ctor" << std::endl; }
    ~A() { std::cout << "~A::ctor" << std::endl; }
};

void thread_method1( int test, int& test1 )
{}

void challenge3()
{}

int main(int argc, char const *argv[])
{
    // challenge1();
    try
    {
        challenge2();
    }
    catch( ... ) {}

    return 0;
}