#include <iostream>

using namespace std;


class A {
public:
  int x = 2;
  virtual int getX() const {
    return x;
  }
};

class B : public A {
public:
  int x = 1;
   int getX() const {
    return x;
  }
};

int main() {
  A* c = new B();
  cout << c->x << " " << c->getX() << endl; // 2 1
  delete c;
  return 0;
}
