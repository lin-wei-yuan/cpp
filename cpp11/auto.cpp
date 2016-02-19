#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
  int index;
public:
  A() : index(0) {}
  int const & ref() const { return index; }
  int * ptr() { return &index; }
};

void challenge1() {
  A a1;
  auto a = a1.ref();
  cout << "Output type: " << typeid(a).name() << endl;
  cout << "Output type: " << typeid(a1.ref()).name() << endl;
  cout << "Is ref: " << std::boolalpha << std::is_reference<decltype(a1.ref())>() << endl;
}

int main() {
  challenge1();
  return 0;
}
