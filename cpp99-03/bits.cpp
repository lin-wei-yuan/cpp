#include <bitset>
#include <iostream>
#include <cmath>
using namespace std;

void challenge1() {
    bitset<32> b(pow(2, 16));
    cout << b.to_string() << endl;

    // 8-bit -1
    // 1) get binary code of 1
    // -> 0000 0001
    // 2) invert all digits
    // -> 1111 1110
    // 3) plus 1
    // -> 1111 1111 => -1

    bitset<32> b1(-1);
    cout << b1.to_string() << endl;

    bitset<32> b2(-2);
    cout << b2.to_string() << endl;

    bitset<32> b3(0);
    cout << b3.to_string() << endl;

    bitset<32> b4(-0);
    cout << b4.to_string() << endl;

    bitset<32> b5(-10);
    cout << b5.to_string() << endl;

    bitset<32> b6(10.5);
    cout << b6.to_string() << endl;
}

void challenge2() {
    // left shift number << 2 equvalent to number * 2 * 2
    bitset<8> b1(2);
    b1 <<= 2;
    cout << boolalpha << "Result: " << b1.to_ulong() << ", " << (b1.to_ulong() == (2 * 2 * 2)) << endl;

    // right shift number >> 2 equvalent to number / (2 * 2)
    bitset<8> b2(16);
    b2 >>= 2;
    cout << boolalpha << "Result: " << b2.to_ulong() << ", " << (b2.to_ulong() == (16 / (2 * 2))) << endl;

    // XOR
    // 1 XOR 1 => 0
    // 1 XOR 0 => 1
    // 0 XOR 1 => 1
    // 0 XOR 0 => 0
    bitset<4> b3(9); // 0000 1001
    bitset<4> b4(3); // 0000 0011
    // 1001 XOR 0011 => 1010
    cout << (b3 ^ b4) << endl;
    // 1001 OR 0011 => 1011
    cout << (b3 | b4) << endl;
    // 1001 AND 0011 => 0001
    cout << (b3 & b4) << endl;
    // NOT 1001 => 0110
    cout << (~b3) << endl;
}

int main() {
    challenge1();
    challenge2();
    return 0;
}
