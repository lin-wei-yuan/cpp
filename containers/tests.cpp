#include <iostream>
#include <vector>
#include "./vec.h"
using namespace std;
using containers::vec;

template<typename T>
void print(const T& container) {
  cout << endl;
  cout << "Container: size[" << container.size() << "]";
  cout << " capacity[" << container.capacity() << "]" << endl;
  cout << "Elements: " << endl;
  if (container.size() == 0) {
    cout << "Empty" << endl;
    return;
  }
  for (size_t i = 0; i < container.size(); ++i) {
    cout << container[i] << " ";
  }
  cout << endl;
}

template<typename T, typename X>
void assert(const T& c1, const X& c2) {

}

// comparison of vec and std::vector
void challenge0() {
  // ctors
  vec<int> v0;
  vector<int> stl_v0;
  print<vec<int>>(v0);
  print<vector<int>>(stl_v0);

  vec<int> v1(4, 100);
  vector<int> stl_v1(4, 100);
  print<vec<int>>(v1);
  print<vector<int>>(stl_v1);

  vec<int> v2(v1);
  vector<int> stl_v2(stl_v1);
  print<vec<int>>(v2);
  print<vector<int>>(stl_v2);
}

int main() {
  challenge0();
  return 0;
}
