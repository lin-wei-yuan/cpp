#include <iostream>
#include <cmath>
#include <defines.h>

using namespace std;
using utils::CaptureTime;

enum class ECTest
{
    CFLAG1,
    CFLAG2
};

constexpr int operator|(ECTest f1, ECTest f2)
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

constexpr int Distance(const SPoint &p1, const SPoint &p2)
{
    return std::sqrt((p1.x + p2.x) * (p1.x + p2.x) + (p1.y + p2.y) * (p1.y + p2.y));
}

/**
    Factorial implementation
*/
// Non-template run-time calculation
long long factorial_1(long long x)
{
    return (x == 1) ? 1 : x * factorial_1(x - 1);
}

// Non-template compile-time calculation
template<long long N>
struct SCompileTime
{
    long long Result()
    {
        return N;
    };
};

constexpr long long factorial_2(long long x)
{
    return (x == 1) ? 1 : x * factorial_2(x - 1);
}

// Template compile-time calculation (C++03 style)
template<long long N>
struct SFactorial
{
    enum { value = N * SFactorial < N - 1 >::value };
};

template<>
struct SFactorial<0>
{
    enum { value = 1 };
};

// Base expressions
void challenge1()
{
    constexpr int ce1 = ECTest::CFLAG1 | ECTest::CFLAG2;
    constexpr int ce2 = 1;
    UNUSED(ce1);
    UNUSED(ce2);
    constexpr SPoint p0;
    constexpr SPoint p1(2, 2);
    int dist = Distance(p0, p1);
    cout << "Distance is " << dist << endl;
}

void challenge2()
{
    constexpr long long variable = 20;
    CaptureTime<> ex;
    // 170 ns
    ex.Start();
    long long result = factorial_1(variable);
    auto execution_time =  ex.Stop();
    cout << "[Runtime] Factorial of " << variable << " is " << result
         << " [ time is " << execution_time << " ns ]" << endl;
    // 31 ns
    ex.Start();
    result = SFactorial<variable>::value;
    execution_time = ex.Stop();
    cout << "[Compile] Factorial of " << variable << " is " << result
         << " [ time is " << execution_time << " ns ]" << endl;
    // 38 ns
    ex.Start();
    SCompileTime<factorial_2(variable)> ct;
    result = ct.Result();
    execution_time =  ex.Stop();
    cout << "[Compile] Factorial of " << variable << " is " << result
         << " [ time is " << execution_time << " ns ]" << endl;
}

int main()
{
    challenge1();
    challenge2();
    return 0;
}