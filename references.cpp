#include <iostream>

inline int tempf() {
  return 1;
}

void challenge1() {
  // compile error
  // int& temp = 1;
  // int& temp = tempf();
  const int& temp1 = 1;
  // compile error
  // temp1 = 2;
}

int main() {
  challenge1();
}
