#include <iostream>
#include <vector>
#include <cassert>
#include <typeinfo>
#include "./src/vec.h"
using namespace std;
using containers::vec;

template<typename T>
void print(const T& container) {
  cout << endl;
  cout << "Typename " << typeid(container).name() << endl;
  cout << "Container: size[" << container.size() << "]";
  cout << " capacity[" << container.capacity() << "]" << endl;
  cout << "Elements: " << endl;
  if (container.size() == 0) {
    cout << "Empty" << endl;
    return;
  }
  cout << "By index : ";
  for (size_t i = 0; i < container.size(); ++i) {
    cout << container[i] << " ";
  }
  cout << endl << "Iterator : ";
  for (typename T::const_iterator it = container.begin(); it != container.end(); ++it) {
    cout << *it << " ";
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
  }
  for (size_t i = 0; i < c1.size(); ++i) {
    assert(c1.at(i) == c2.at(i));
  }
  cout << "=---------------------------=" <<endl;
  cout << "#" << test_id <<" Passed!" << endl;
  print<T>(c1);
  print<X>(c2);
  cout << "=---------------------------=" <<endl;
  test_id++;
}

// comparison of vec and std::vector
void challenge0() {
  // ctors
  vec<int> v0;
  vector<int> stl_v0;
  unit(v0, stl_v0);

  vec<int> v1(5);
  vector<int> stl_v1(5);
  unit(v1, stl_v1);

  vec<int> v2(4, 101);
  vector<int> stl_v2(4, 101);
  unit(v2, stl_v2);

  vec<int> v3(v1);
  vector<int> stl_v3(stl_v1);
  unit(v3, stl_v3);

  vec<int> v4(v2.begin(), v2.end());
  vector<int> stl_v4(stl_v2.begin(), stl_v2.end());
  unit(v4, stl_v4);
}

int main() {
  challenge0();
  return 0;
}
