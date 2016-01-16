#include <iostream>
#include <vector>
#include "./t.h"
using namespace std;

// #define _DEBUG

class Base {
public:
  virtual void print() const = 0;
  virtual ~Base() {}
};

class Derived_1 : public Base {
public:
  void print_2();
};

class Derived_2 : public Base{
public:
  void print() const {};
};

class D
{
  T first;
  T second;
public:
  D() : first(T(1)), second(T(2)) {
    #ifdef _DEBUG
      cout << "D::D()" << endl;
    #endif
  }
  virtual ~D() {
    #ifdef _DEBUG
      cout << "D::~D()" << endl;
    #endif
  }
  virtual void print() const { cout << "D::print() const" << endl; }
  void print_2() const { cout << "D::print_2() const" << endl; }
};


class E : public D
{
  T third;
  T fourth;
public:
  E(): third(T(3)), fourth(T(4)) {
    #ifdef _DEBUG
      cout << "E::E()" << endl;
    #endif
  }
  virtual ~E() {
    #ifdef _DEBUG
      cout << "E::~E()" << endl;
    #endif
  }
  virtual void print() const { cout << "E::print() const" << endl; }
  void print_2() const { cout << "E::print_2() const" << endl; }
};

void challenge1() {
  std::vector<D*> v;
  v.push_back(new D);
  v.push_back(new E);

  for (size_t i = 0; i < v.size(); ++i) {
    v.at(i)->print();
    v.at(i)->print_2();
    delete v.at(i);
  }
}

void challenge2() {
    // Base* test = new Derived_1; // abstract
  Base* test = new Derived_2;
  delete test;
}

int main() {
  // challenge1();
  challenge2();
}
