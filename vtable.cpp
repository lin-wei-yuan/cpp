#include <iostream>
using namespace std;

class A
{
public:
  virtual void foo() { cout << "A::foo" << endl; }
  virtual void baz() { cout << "A::baz" << endl; }
  void bar() {cout << "A::bar" << endl;}
};


class B : public A
{
public:
  void foo() { cout << "B::foo" << endl; }
  void baz() {cout << "B::baz" << endl;}
  virtual void bar() {cout << "B::bar" << endl;}
};

int main() {
  B* obj = new B;
  obj->foo();
  obj->baz();
  obj->bar();
}
