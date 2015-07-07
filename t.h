#ifndef T_H
#define T_H

#include <iostream>

class T
{
int id;
public:
  T() : id(0) {
    std::cout << "T created(ctor)" << std::endl;
  }
  T(int _id) : id(_id) {
    std::cout << "T created with id = " << id << "(ctor)" << std::endl;
  }
  T(const T&) {
    std::cout<< "Copy ctor called" << std::endl;
  }
  ~T() {
    std::cout << "T deleted(dtor) id = " << id << std::endl;
  }

  T& operator=(const T& that) {
    std::cout<< "Copy operator called" << std::endl;
    return *this;
  }

  int getID() { return id; }
};

#endif
