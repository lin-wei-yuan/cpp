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
    std::cout << "Default T::ctor called. id = 0" << std::endl;
  }
  T(int _id) : id(_id) {
    std::cout << "T::Ctor with params called. id =" << id << std::endl;
  }
  T(const T& that) : id(that.getID()) {
    std::cout<< "Copy T::ctor called. Source=" << that.getID() << std::endl;
  }
  T(T&& that) : id(that.getID()) {
    std::cout << "Move T::ctor called. Source=" << that.getID() << std::endl;
  }
  ~T() {
    std::cout << "~T::dtor called.  id = " << id << std::endl;
  }

  T& operator=(const T& that) {
    std::cout<< "Copy T::operator called. Source = " << that.getID() << std::endl;
    id = that.getID();
    return *this;
  }
  T& operator=(T&& that) {
    std::cout << "Move T::operator called. Source = " << that.getID() << std::endl;
    id = that.getID();
    return *this;
  }

  int getID() const { return id; }
};

class A {
  T obj;
public:
  A() {
    std::cout << "Default A::ctor" << std::endl;
  }

  A(const A& _obj) {
    throw std::logic_error("From copy A::ctor");
  }

  A(T&& _obj)
    : obj(std::move(_obj))
  {
    throw std::logic_error("From move A::ctor");
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

class C {
  A obj;
public:
  C()
    try
      : obj(std::move(A()))
    {
      std::cout << "C::ctor called " << std::endl;
    }
    catch (const std::logic_error& le ) {
      std::cout << "C::C() cathed: " << le.what() << std::endl;
    }
};
#endif
