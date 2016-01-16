#include "./t.h"

class A {
  T t;
public:
  A() {
    std::cout << "Default A::ctor" << std::endl;
  }

  A(const A& _obj) : t(_obj.getT()) {
    throw std::logic_error("From copy A::ctor");
  }

  A(const T& _obj) : t(_obj) {
    throw std::logic_error("From A::ctor with T params");
  }
  ~A() {
    std::cout << "~A::dtor" << std::endl;
  }

  T getT() const {
    return t;
  }
};
