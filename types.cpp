#include <iostream>
#include <limits>
#include <typeinfo>
#include <cmath>

using namespace std;

const size_t BITS = 8;

template<typename T>
void print(const T& var) {
  cout << endl;
  cout << "Type name: " << typeid(var).name() << endl;
  cout << "Min size: " << numeric_limits<T>::min() << endl;
  cout << "Max size: " << numeric_limits<T>::max() << endl;
  cout << "Is type signed: " << ((numeric_limits<T>::is_signed) ? "true" : "false") << endl;
  cout << "Size in bytes: " << sizeof(T) << endl;
  if (numeric_limits<T>::is_integer) {
    if (numeric_limits<T>::is_signed) {
      cout << "Size: [-2 ^ " << (sizeof(T) * BITS - 1) <<  ",  2 ^ "<< (sizeof(T) * BITS - 1) << " - 1]" << endl;
      cout << "[" << - std::pow(2, (sizeof(T) * BITS - 1)) << ", " << std::pow(2, (sizeof(T) * BITS - 1)) - 1  << "]" << endl;
    } else {
      cout << "Size: [0,  2 ^ "<< (sizeof(T) * BITS) << " - 1]" << endl;
      cout << "[0, " << std::pow(2, (sizeof(T) * BITS - 1)) - 1  << "]" << endl;
    }
  }
}

void challenge1() {
  int a0 = 10;
  print<int>(a0);
  unsigned int a1 = 10;
  print<unsigned int>(a1);
  signed int a2 = 10; // same as int
  print<signed int>(a2);

  unsigned short int a3 = 10;
  print<unsigned short int>(a3);
  short int a4 = 10;
  print<short int>(a4);

  unsigned long int a5 = 10;
  print<unsigned long int>(a5);
  long int a6 = 10;
  print<long int>(a6);

  char a7 = 'a';
  print<char>(a7);

  float a8 = 123.0f;
  print<float>(a8);

  double a9 = 123.0;
  print<double>(a9);

  bool a10 = true;
  print<bool>(a10);

  // void a11; // incomplete type
  // print<void>(a11);
}

int main() {
  challenge1();
}
