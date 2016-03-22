#include <iostream>

#define IS_VIRTUAL

class B {
public:
  B() { std::cout << "B" << std::endl; }
  ~B() { std::cout << "~B" << std::endl; }
  #ifdef IS_VIRTUAL
    virtual void tmp() const { std::cout << "B::tmp" << std::endl; }
  #else
    void tmp() const { std::cout << "B::tmp" << std::endl; }
  #endif
};

class D : public B {
public:
  D() { std::cout << "D" << std::endl; }
  ~D() { std::cout << "~D" << std::endl; }
  #ifdef IS_VIRTUAL
    virtual void tmp() const override { std::cout << "D::tmp" << std::endl; }
  #else
    void tmp() const { std::cout << "D::tmp" << std::endl; }
  #endif
  // Additional method
  void additional() const { std::cout << "D::additional" << std::endl; }
};

class D1 : public D {
  D1() { std::cout << "D1" << std::endl; }
  ~D1() { std::cout << "~D1" << std::endl; }
  #ifdef IS_VIRTUAL
    virtual void tmp() const override { std::cout << "D1::tmp" << std::endl; }
  #else
    void tmp() const { std::cout << "D1::tmp" << std::endl; }
  #endif
};

void challenge1() {
  D d;
  // get pointer of B type
  B* pb = &d;
  // If tmp virtual -> D::tmp
  // else B::tmp
  pb->tmp();
}

void challenge2() {
  D d;
  // C-style cast
  // Static_cast
  // reinpreter_cast
  // const_cast
  D* p1 = (D*)&d;
  B* p2 = (B*)&d;
  B* p3 = (D*)&d;
  // D* p4 = (B*)&d; error: invalid conversion from

  // If tmp virtual -> D::tmp
  // else D::tmp
  p1->tmp();
  // If tmp virtual -> D::tmp
  // else B::tmp
  p2->tmp();
  // If tmp virtual -> D::tmp
  // else B::tmp
  p3->tmp();
}

void challenge3() {
  D d;
  // @todo: dynamic_cast
}

int main()
{
  // challenge1();
  challenge2();
  return 0;
}
