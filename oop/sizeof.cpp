#include <iostream>
using namespace std;

struct A
{};

struct NonEmptyA
{
    int a;
    char b;
};

#pragma pack(push, 1)
struct NonEmptyAWithPack
{
    int a;
    char b;
};
#pragma pack(pop)

int main(int argc, char const *argv[])
{
    cout << "empty A: " << sizeof(A) << endl;
    // With '#pragma pack(push, 4)' the size of NonEmptyA is 8( 4 + 1 + 3(pack))
    cout << "A: " << sizeof(NonEmptyA) << endl;
    // With '#pragma pack(push, 1)' the size is 5 (int + char)
    cout << "A with packing: " << sizeof(NonEmptyAWithPack) << endl;
    return 0;
}