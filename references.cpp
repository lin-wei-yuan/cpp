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

/* Vector implementation */
template<typename U>
class vec
{
  U* m_arr;
  size_t m_size;
  size_t m_capacity;
public:
  vec(size_t size, U element) {
    m_arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = element;
    }
    m_size = size;
    m_capacity = size;
  }

  vec() {
    m_arr = new int[0];
    m_size = 0;
    m_capacity = 0;
  }

  vec(size_t size) {
    m_arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
      m_arr[i] = 0;
    }
    m_size = size;
    m_capacity = size;
  }

  vec(const vec<U>& other) {

  }

  ~vec() {
    delete[] m_arr;
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  U& operator[](int index) noexcept {
    return m_arr[index];
  }
};

void challenge2() {
  vec<int> v;
  vector<int> stl_v;
  cout << v.size() << ", " << v.capacity() << endl;
  cout << stl_v.size() << ", " << stl_v.capacity() << endl;
}

int main() {
  // challenge1();
  challenge2();
}
