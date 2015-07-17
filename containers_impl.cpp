#include <iostream>
#include <vector>
#include "vec.h"
using namespace std;
using containers::vec;

void challenge0() {
  vec<int> v;
  vector<int> stl_v;
  cout << v.size() << ", " << v.capacity() << endl;
  cout << stl_v.size() << ", " << stl_v.capacity() << endl;
}

int main() {
  challenge0();
  return 0;
}
