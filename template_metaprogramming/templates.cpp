#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

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

int main(int argc, char const *argv[])
{
    challenge0();
    challenge1();
    return 0;
}