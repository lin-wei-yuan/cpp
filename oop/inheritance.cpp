#include <iostream>

using namespace std;

class Zero {
public:
  Zero() { cout << "Zero()"<< endl; }
  Zero(int i) { cout << "Zero() - " << i << endl; }
  ~Zero() { cout << "~Zero()"<< endl; }
};

class One {
public:
  One() { cout << "One()"<< endl; }
  One(int i) { cout << "One() - " << i << endl; }
  ~One() { cout << "~One()"<< endl; }
};

class A
{
  Zero z;
  One o;
public:
  A() { cout << "A()"<< endl; }
  ~A() { cout << "~A()"<< endl; }

  void message() const { cout << "A message" << endl;}
};

class B
{
  Zero z;
  One o;
public:
  B() { cout << "B()"<< endl; }
  ~B() { cout << "~B()"<< endl; }

  void message() const { cout << "B message" << endl;}
};

class C
{
public:
  C() { cout << "C()"<< endl; }
  ~C() { cout << "~C()"<< endl; }

  void message() const { cout << "C message" << endl;}
};

class Child : public A, public C, public B {
  Zero z1;
  One o1;
public:
  Child() : o1(1), z1(1) { cout << "Child()" << endl; }
  ~Child() { cout << "~Child()" << endl; }

  void message() const { cout << "Child message" << endl;}
};

void challenge1() {
  Child c1;
  c1.message(); // not work if Child class doesnt have message method - ambiguos
}

class A1
{
public:
  A1() { cout << "A1()"<< endl; }
  virtual ~A1() { cout << "~A1()"<< endl; }

  virtual void message() const { cout << "A1 message" << endl;}
};

class B1: public A1
{
public:
  B1() { cout << "B1()"<< endl; }
  ~B1() { cout << "~B1()"<< endl; }

  void message() const { cout << "B1 message" << endl;}
};

class C1: public B1
{
public:
  C1() { cout << "C1()"<< endl; }
  ~C1() { cout << "~C1()"<< endl; }

  void message() const { cout << "C1 message" << endl;}
};

class D1 : public C1
{
public:
  D1() { cout << "D1()"<< endl; }
  ~D1() { cout << "~D1()"<< endl; }

  void message() const { cout << "D1 message" << endl;}
};

void challenge2() {
  A1 *c1 = new B1;
  c1->message();
  delete c1;
}

void challenge3() {
  A1 *c2 = new D1;
  c2->message();
  delete c2;
}

int main() {
  // challenge1();
  // challenge2();
  challenge3();
  return 0;
}


