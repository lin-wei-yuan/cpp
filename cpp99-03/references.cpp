#include <iostream>
#include <vector>
#include "t.h"
using namespace std;

inline T tempf() {
  return T(2);
}

// Memory leak!
inline T& tempr() {
  return *(new T(4));
}

void print(const T& var) {
  cout << "T with " << var.getID() << ": " << var << ", " << &var << endl;
}

void challenge1() {
  T temp = 4;
  print(temp);
  // compile error
  // T& temp0 = 5; // T(5) - temprorary object
  // works
  T& temp1 = temp;
  print(temp1);

  // compile error
  // T& temp2 = tempf();
  T temp2 = tempf();
  T& temp3 = temp2;
  print(temp2);
  print(temp3);

  // work
  T& temp4 = tempr();
  print(temp4);
  // Do not forget fix memory leak
  delete &temp4;

  const T& temp5 = 5;
  print(temp5);

  // lol
  // const T& const temp6 = 6; //cannot be applied
  // T& const temp6 = 6; //cannot be applied
}

void challenge2() {
  int i = 10;
  cout << "i ["<< &i << "] = " << i << endl;
}

int main() {
  // challenge1();
  challenge2();
}
