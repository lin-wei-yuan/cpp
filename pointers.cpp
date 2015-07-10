#include <iostream>
#include <vector>
#include "t.h"
using namespace std;

void challenge0() {
  int i = 10;
  int* pi = &i;

  cout << "pi = " << pi << ", *pi = " << *pi << ", size = " << sizeof(pi) <<  endl;
  cout << " size *pi =" << sizeof(*pi) << endl;
}

void challenge1() {
  vector<T> v1;

}


int main() {
  challenge0();
  return 0;
}
