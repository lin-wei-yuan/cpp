#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

template<class T>
string typeof() {
  return string(typeid(T).name());
};

class NoCopy {
public:
  NoCopy() {
    cout << "NoCopy::NoCopy()" << endl;
  }
  NoCopy(const NoCopy& nc) = delete;
  void operator=(const NoCopy& nc) = delete;
  virtual ~NoCopy() {} // just for unheritance
};

class A
{
public:
  A(string _a = "unknown") : name(_a) {
    cout << "A::A()" << endl;
  };

  ~A() {
    cout << "A::~A()" << endl;
  }

  A(const A& copy) {
    cout << "A::A(copy&)" << endl;
    name = copy.get();
  }

  void operator=(const A& that) {
    cout << "A::operator=(&)" << endl;
    name = that.get();
  }

  A(A&& that) {
    cout << "A::A(&&)" << endl;
    name = that.name;
  }

  A& operator=(A&& that) {
    cout << "A::operator=(&&)" << endl;
    name = that.name;
    return *this;
  }

  string get() const {
    return name;
  }

  void print() const {
    cout << "Name: " << name << endl;
  }

private:
  string name;
};

class B : public NoCopy
{
public:
  B(int _i = -1) : index(_i) {
    cout << "B::B()" << endl;
  }

  ~B() {
    cout << "B::~B()" << endl;
  }

  B(B&& that) {
    cout << "B::B(&&)" << endl;
    index = that.get();
  }

  B& operator=(B&& that) {
    cout << "B::operator=(&&)" << endl;
    index = that.get();
    return *this;
  }

  int get() const {
    return index;
  }

protected:
  int index;
};

// variable temp + 2 copies(A::operator=())
template<class T>
void swap1(T& a, T& b) {
  T temp(a);
  // a.operator=(b);
  a = b;
  // b.operator=(temp);
  b = temp;
}

template<class T>
void swap2(T& a, T& b) {
  T temp(std::move(a));
  // Now check a
  cout << "First param with type " << typeof<T>() << " = " << &a << a.get() << endl;
  a = std::move(b);
  b = std::move(temp);
}

void challenge1() {
  A a1("test1");
  a1.print();
  A a2;
  a2.print();

  a2 = a1;
  a2.print();

  A a3(a2);
  a3.print();

  A a4 = A();
  a4.print();
}

void challenge2() {
  A test1("test1");
  A test2("test2");
  cout << "test1 = " << test1.get() << endl;
  cout << "test2 = " << test2.get() << endl;
  swap1<A>(test1, test2);
  cout << "test1 = " << test1.get() << endl;
  cout << "test2 = " << test2.get() << endl;
  swap2<A>(test1, test2);
  cout << "test1 = " << test1.get() << endl;
  cout << "test2 = " << test2.get() << endl;
}

void challenge3() {
  B test1(1);
  B test2(2);
  // Compile error(NoCopy interface)
  // swap1<B>(test1, test2);
  cout << "test1 = " << test1.get() << endl;
  cout << "test2 = " << test2.get() << endl;
  swap2<B>(test1, test2);
  cout << "test1 = " << test1.get() << endl;
  cout << "test2 = " << test2.get() << endl;
}

int main(int argc, char const *argv[]) {
  // challenge1();
  // challenge2();
  challenge3();
  return 0;
}
