// #define _DEBUG

#ifdef _DEBUG
  #include <iostream>
  using namespace std;
#endif


class A
{
public:
  A() {
    #ifdef _DEBUG
      cout << "A::A" << endl;
    #endif
  }
  virtual void foo() {
    #ifdef _DEBUG
      cout << "A::foo" << endl;
    #endif
  }
  virtual void baz() {
    #ifdef _DEBUG
      cout << "A::baz" << endl;
    #endif
  }
  void bar() {
    #ifdef _DEBUG
      cout << "A::bar" << endl;
    #endif
  }
  virtual ~A() {
    #ifdef _DEBUG
      cout << "A::~A" << endl;
    #endif
  }
};


class B : public A
{
public:
  B() {
    #ifdef _DEBUG
      cout << "B::B" << endl;
    #endif
  }
  void foo() {
    #ifdef _DEBUG
      cout << "B::foo" << endl;
    #endif
  }
  void baz() {
    #ifdef _DEBUG
      cout << "B::baz" << endl;
    #endif
  }
  void bar() {
    #ifdef _DEBUG
      cout << "B::bar" << endl;
    #endif
  }
  virtual ~B() {
    #ifdef _DEBUG
      cout << "B::~B" << endl;
    #endif
  }
};

int main() {
  A* obj = new B;
  obj->foo();
  obj->baz();
  obj->bar();
  delete obj;
}
