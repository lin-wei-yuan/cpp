#include <iostream>
#include <vector>
#include <cassert>
#include "./src/vec.h"
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
void unit(const T& c1, const X& c2) {
  static int test_id = 1;
  assert(c1.size() == c2.size());
  assert(c1.capacity() == c2.capacity());
  if (c1.size() > 0) {
    assert(*(c1.begin()) == *(c2.begin()));
    assert(*(c1.end()) == *(c2.end()));
  }
  for (size_t i = 0; i < c1.size(); ++i) {
    assert(c1.at(i) == c2.at(i));
  }
  cout << "#" << test_id <<" Passed!" << endl;
  test_id++;
}

// comparison of vec and std::vector
void challenge0() {
  // ctors
  vec<int> v0;
  vector<int> stl_v0;
  unit(v0, stl_v0);

  // vec<int> v1(4, 100);
  // vector<int> stl_v1(4, 100);
  // unit(v1, stl_v1);

  // vec<int> v2(v1);
  // vector<int> stl_v2(stl_v1);
  // unit(v2, stl_v2);
}

int main() {
  challenge0();
  return 0;
}
