#include <iostream>
#include "basic_utils.h"

using namespace std;
using basic_utils::Test;

// Swap implementation that make a lot of copies
// variable temp + 2 copies(A::operator=())
template<class T>
void swap_copy( T& first, T& second ) // <- without const
{
    // Copy ctor called
    T temp( first ); // temp contains copy of object with id 1
    // a.operator=(T& b); <- without const
    first = second; // <- 'first' contains copy of object with id 2
    // b.operator=(temp);
    second = temp; //  <- second contains copy of object with id 1
}

// Swap implementation that use move semantic
// 1 object creation
template<class T>
void swap_move( T& first, T& second )
{
    // Create variable for storing 'first' variable
    // 'first' now in unspecified BUT valid state (17.6.5.15 [lib.types.movedfrom])
    T temp( std::move( first ) );
    // 'first' now specified and contain 'second'
    // 'second' now is unspecified but in valid state
    first = std::move( second );
    // 'first' and 'second' now are both specified
    // 'temp' unspecified and will be destroyed
    second = std::move( temp );
}

void challenge1()
{
    Test first( 1 );
    Test second( 2 );
    swap_copy( first, second );
}

void challenge2()
{
    Test third( 3 );
    Test fourth( 4 );
    swap_move( third, fourth );
}

int main( int argc, char const *argv[] )
{
    challenge1();
    challenge2();
    return 0;
}
