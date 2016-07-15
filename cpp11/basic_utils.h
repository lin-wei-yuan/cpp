#ifndef T_H
#define T_H

#include <iostream>
// Use platform-specific lib
#ifndef OS_WINDOWS
#include <cxxabi.h>
#endif

namespace basic_utils
{

/**
    Returns string representation of type
*/
template<class T>
std::string typeof()
{
    auto name = typeid( T ).name();
    #ifndef OS_WINDOWS
        int status;
        auto nname = abi::__cxa_demangle(name, 0, 0, &status);
    #endif
    return std::string( nname );
}

/**
    Abstract interace for disable copying
*/
class NoCopy
{
public:
    NoCopy(const NoCopy& nc) = delete;
    void operator=(const NoCopy& nc) = delete;
    virtual ~NoCopy() {} // just for unheritance
};

/**
    Simple class for logging info about method calls
*/
class Test
{
private:
    // Current object id 
    int m_id;
public:
    // Constructors
    Test()
        : m_id(0)
    {
        std::cout << "Default Test::ctor called. id = 0" << std::endl;
    }

    Test( int _id )
        : m_id( _id )
    {
        std::cout << "Test::ctor with params called. id = " << m_id << std::endl;
    }

    Test( const Test& that )
        : m_id( that.getID() )
    {
        std::cout<< "Copy Test::ctor called. Source = " << that.getID() << std::endl;
    }

    Test( Test&& that )
        : m_id( that.getID() )
    {
        std::cout << "Move Test::ctor called. Source = " << that.getID() << std::endl;
    }

    // Destructor
    ~Test()
    {
        std::cout << "~Test::dtor called. id = " << m_id << std::endl;
    }

    // Assign operators
    Test& operator=( Test& that )
    {
        std::cout<< "Copy Test::operator without const parameter called. Source = " << that.getID() << std::endl;
        m_id = that.getID();
        return *this;
    }

    Test& operator=( const Test& that )
    {
        std::cout<< "Copy Test::operator called. Source = " << that.getID() << std::endl;
        m_id = that.getID();
        return *this;
    }

    Test& operator=( Test&& that )
    {
        std::cout << "Move Test::operator called. Source = " << that.getID() << std::endl;
        m_id = that.getID();
        return *this;
    }

    // Getters / Setters
    int getID() const
    {
        return m_id;
    }

    void setID(int _id)
    {
        m_id = _id;
    }

    // Print index of Test 
    friend std::ostream& operator<< ( std::ostream& out, const Test& that )
    {
        out << that.m_id;
        return out;
    }

};


} // End of basic_utils name



#endif
