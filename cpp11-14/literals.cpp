#include <iostream>
#include <complex>
using namespace std;

typedef unsigned long long int ull32_t;

template<typename T>
void print(const std::complex<T>& c)
{
    cout << "[" << c.real() << ", " << c.imag() << "i]" << endl;
}

// Use _i literal for because literals without _ reserved by C++ STL
constexpr std::complex<long double> operator "" _i(long double x)
{
    return { 0, x };
}

constexpr std::complex<ull32_t> operator "" _i(ull32_t x)
{
    return { 0, x };
}

// Work with dynamical memory
/*constexpr*/ std::string operator "" _ex(const char* str)
{
    return std::move(std::string(str));
}

/*constexpr*/ std::string operator "" _s(const char* str, size_t n)
{
    return std::move(std::string(str, n));
}

void challenge1()
{
    std::complex<ull32_t> test1 = 11_i;
    print(test1);
    std::complex<long double> test2 = 2.0l + 2.0_i;
    print(test2);

    std::string test3 = 123_ex;
    std::string test4 = "123"_s;
    cout << test3 << ", " << test4 << endl;
}

int main(int argc, char const *argv[])
{
    challenge1();
    return 0;
}