#include <iostream>
#include <cmath>
#include "../basic/basic_utils.h"
using namespace std;
using basic_utils::CaptureTime;

enum class ECTest
{
    CFLAG1,
    CFLAG2
};

constexpr int operator|( ECTest f1, ECTest f2 )
{
    return int(f1) | int(f2);
}

struct SPoint
{
    int x;
    int y;
    constexpr SPoint() : x(0), y(0) {}
    constexpr SPoint( int _x, int _y ) : x(_x), y(_y) {}
};

constexpr int Distance( const SPoint& p1, const SPoint& p2 )
{
    return std::sqrt( ( p1.x + p2.x ) * ( p1.x + p2.x ) + ( p1.y + p2.y ) * ( p1.y + p2.y ) );
}

// Factorial implementatiom
long long factorial_1( long long x )
{
    return ( x == 1 ) ? 1 : x * factorial_1( x - 1 );
}

constexpr long long factorial_2( long long x )
{
    return ( x == 1 ) ? 1 : x * factorial_2( x - 1 );
}

template< long long r >
struct SCompileTime
{
    SCompileTime() {}
    long long Result() const { return r; }
};

// Base expressions
void challenge1()
{
    constexpr int ce1 = ECTest::CFLAG1 | ECTest::CFLAG2;
    constexpr int ce2 = 1;

    constexpr SPoint p0;
    constexpr SPoint p1(2, 2);
    int dist = Distance( p0, p1);
    cout << "Distance is " << dist << endl;
}

void challenge2()
{
    constexpr long long variable = 20;

    CaptureTime<> ex;
    ex.Start();
    // @TODO: Replace on BigNumber for preventing overflow
    long long result_runtime = factorial_1( variable );
    auto execution_time =  ex.Stop();

    cout << "[Runtime] Factorial of " << variable << " is " << result_runtime 
         << " [ time is " << execution_time << " ns ]" << endl;

    ex.Start();
    // @TODO: Replace on BigNumber for preventing overflow
    // SCompileTime<factorial_2( variable )> ct;
    const long long result_compile = factorial_2( variable ); 
    // long long result_compile = ct.Result();
    execution_time =  ex.Stop();

    cout << "[Compile] Factorial of " << variable << " is " << result_compile 
         << " [ time is " << execution_time << " ns ]" << endl;
}

int main()
{
    challenge1();
    challenge2();
    return 0;
}