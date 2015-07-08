#ifndef T_H
#define T_H

#include <iostream>
#include <stdexcept>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class T
{
int id;
public:
  T() : id(0) {
    std::cout << "Default T ctor called. id = 0" << std::endl;
  }
  T(int _id) : id(_id) {
    std::cout << "Ctor with params called. id =" << id << std::endl;
  }
  T(const T& that) : id(that.getID()) {
    std::cout<< "Copy ctor called. Source=" << that.getID() << std::endl;
  }
  T(T&& that) : id(that.getID()) {
    std::cout << "Move ctor called. Source=" << that.getID() << std::endl;
  }
  ~T() {
    std::cout << "~T::dtor called.  id = " << id << std::endl;
  }

  T& operator=(const T& that) {
    std::cout<< "Copy operator called. Source = " << that.getID() << std::endl;
    id = that.getID();
    return *this;
  }
  T& operator=(T&& that) {
    std::cout << "Move operator called. Source = " << that.getID() << std::endl;
    id = that.getID();
    return *this;
  }

  int getID() const { return id; }
};

class A {
  T obj;
public:
  A(T&& _obj)
    : obj(std::move(_obj))
  {
    throw std::logic_error("From A::ctor");
  }
  ~A() {
    std::cout << "~A::dtor" << std::endl;
  }
};

class B {
  T obj;
public:
  B(T&& _obj)
    : obj(std::move(_obj))
  {
    std::cout << "B::ctor called" << std::endl;
  }
  ~B() {
    throw std::logic_error("From B:dtor");
    std::cout << "~B():dtor called" << std::endl;
  }
};
#endif
