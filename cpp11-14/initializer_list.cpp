#include <iostream>
#include <vector>
#include <defines.h>

using namespace std;
using utils::type_name;

void f1(const std::initializer_list<int> &list)
{
    cout << "initializer_list size is " << list.size() << endl;
    for (const auto &element : list)
        cout << element << " ";
    cout << endl;
}

ostream &operator<<(ostream &s, const vector<int> list)
{
    for (const auto &element : list)
        s << element << " ";
    s << endl;
    return s;
}

void f2(const std::initializer_list<vector<int>> &list)
{
    cout << "initializer_list size is " << list.size() << endl;
    for (const auto &element : list)
        cout << element;
}

void challenge1()
{
    auto ilist = { 1, 2, 3, 4, 5 };
    cout << "Type of ilist is " << type_name<decltype(ilist)>() << endl;
    f1( ilist );
    // Unable to deduce nested constructions
    // auto ivlist = { { 1, 2, 3, 4 }, { 1, 2, 3 }, { 1, 2 } };
    std::initializer_list<vector<int>> ivlist = { { 1, 2, 3, 4 }, { 1, 2, 3 }, { 1, 2 } };
    f2( ivlist );
}

// Prevent narrowing
void challenge2()
{
    int x = 5;
    int x1 = { 5 };

    UNUSED(x);
    UNUSED(x1);

    // narrowing conversion of ‘5.0999999999999996e+0’ from ‘double’ to ‘int’ inside { }
    // int x2 = { 5.1 };
}


int main(int argc, char const *argv[])
{
    challenge1();
    challenge2();
    return 0;
}