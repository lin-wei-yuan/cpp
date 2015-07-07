#include <iostream>
#include <typeinfo>
#include "stacktrace.h"
#include "smart.h"
#include "t.h"
#include <stdexcept>
#include <memory>
using namespace std;

class simpleException {
public:
  simpleException() {
    cout << "init exception" << endl;
  }
  ~simpleException() {
    cout << "Dtor of an exception" << endl;
  }
  void what() const {
    cout << "WTF?" << endl;
  }
};

// Regenerate throw
bool isFixed = false;

void letstry() {
  cout << "Before try" << endl;
  try {
    cout << "Inside try: begin" << endl;
    if (!isFixed) {
      throw simpleException();
    } else {
      cout << "Fixed!" << endl;
    }
    cout << "Inside try: end" << endl;
  } catch(const simpleException& e) {
    e.what();
    cout << "Generated: " << typeid(e).name() << endl;
    if (!isFixed) {
      isFixed = true;
      throw;
    }
  }
}

void challenge1() {
  try {
    // print_stacktrace();
    letstry();
  } catch (...) {
    if (isFixed) {
      cout << "Everything is okay" << endl;
    } else {
      cout << "Still not fixed! terminate()" << endl;
    }
  }
}

void lestMakeLeak2_1(int i) {
  T* p = new T();
  if (i == 0) {
    throw std::logic_error("Ruine challenge2");
  }
  delete p;
}

void lestMakeLeak2_2(int i) {
  smart<T> p(new T());
   if (i == 0) {
    throw std::logic_error("Ruine challenge2");
  }
}

// Check if T call dtor
void challenge2() {
  try {
    // Dtor called
    lestMakeLeak2_1(10);
    // Dtor could not be called => memory leak
    lestMakeLeak2_1(0);
  } catch (...) {
    cout << "Catched!" << endl;
  }
  // using smart pointer
  try {
    // Dtor called
    lestMakeLeak2_2(10);
    // Dtor also called
    lestMakeLeak2_2(0);
  } catch (...) {
    cout << "Catched!" << endl;
  }
}

// Test auto_ptr
void challenge3() {
  auto_ptr<T> p1(new T());
  auto_ptr<T> p2 = p1;
  // Segmentation Fault
  // cout << p1.get()->getID() << endl;
  // p2 owned new T(), p1 == NULL
  cout << p2.get()->getID() << endl;
  const auto_ptr<T> cp1(new T());
  // auto_ptr<T> cp2(cp1); // - compilation error
  // cp1.release(); // - compilation error
}

// @TODO: Exceptions in ctors
// @TODO: Exceptions in dtors

/* -------------------- */
int main() {
  // print_stacktrace();
  // challenge1();
  // challenge2();
  challenge3();
  return 0;
}
