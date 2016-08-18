#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <functional>

#include "../basic/basic_utils.h"
using namespace std;
using basic_utils::typeof;

// Question: Do we use this in function body ?
template<typename T>
using SomeMap = std::map<T, std::vector<std::pair<T, T>>>;

template<typename T, typename U>
using SomeMapN = std::map<T, std::vector<std::pair<T, U>>>;

// Tempate alias( aka template typedef )
void challenge0()
{
    std::map<int, std::vector<std::pair<int, int>>> some_var;
    // using template alias
    SomeMap<int> alias_map;
    SomeMapN<int, std::string> alias_map_N;
}

// Variadic templates
// Lets write some implementation of printf function
void printf_( const std::string& result )
{
    cout << "Result is " << result << endl;
}

template<typename T, typename... Args> // Args is parameter pack
void printf_( const std::string& result, T value, Args... args )
{
    std::string converted = std::to_string( value );
    std::string pattern = "%s";
    std::string copy = std::move( result );
    size_t itt = copy.find( '%' );
    if( itt < copy.size() )
    {
        copy.replace( itt, pattern.size(), converted );
    }
    printf_(copy, args... );
}

void challenge1()
{
    printf_( "Test string for printf_ with param %s and %s", 11, 21 );
}

// std::tuple
void challenge2()
{
    std::tuple<int, int, double> t1( 1, 2, 3.0 );
    cout << "Type is " << typeof<decltype(t1)>() << endl;
    size_t size = tuple_size<decltype(t1)>::value;
    cout << "Elements count is " << size << endl;
    // @TODO: find some way for output this values in cycle
    // <N> requires values on compile time
    cout << "Index 0 is " << get<0>(t1) << endl;
    cout << "Index 1 is " << get<1>(t1) << endl;
    cout << "Index 2 is " << get<2>(t1) << endl;

    auto t2 = make_tuple( "string", 2, 2LL );
    cout << "Type of t2 is " << typeof<decltype(t2)>() << endl;
}

// std::bind and std::function
void challenge3()
{
    // Create functor with params int int int and return type int
    std::function<int (int, int, int)> f;
    f = []( int f, int s, int additional ) { return f + s + additional; };
    cout << f( 1, 1, 2 ) << endl;
    // Use carrying
    auto ff = std::bind( f, std::placeholders::_1, std::placeholders::_2, 3 );
    cout << ff( 1, 1 ) << endl;
}

int main(int argc, char const *argv[])
{
    // challenge0();
    // challenge1();
    // challenge2();
    challenge3();
    return 0;
}