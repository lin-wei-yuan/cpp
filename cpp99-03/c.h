#include "./a.h"

class C {
  A obj;
public:
  C()
    try
      : obj(A())
    {
      std::cout << "C::ctor called " << std::endl;
    }
    catch (const std::logic_error& le ) {
      std::cout << "C::C() cathed: " << le.what() << std::endl;
    }
};
