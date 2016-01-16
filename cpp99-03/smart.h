#ifndef _SMART_H
#define _SMART_H

#include <iostream>
#include <typeinfo>
using namespace std;

template<typename T>
class smart
{
  T* p;
public:
  smart(T* _p) : p(_p) {
    cout << "smart ctor with owned type" << typeid(p).name() << endl;
  }
  ~smart() {
    delete p;
  }
};

#endif
