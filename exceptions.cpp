#include <iostream>
using namespace std;

class simpleException {
public:
  simpleException() {
    cout << "init exception" << endl;
  }
  ~simpleException() {
    cout << "Dtor of an exception" << endl;
  }
  void what() const {
    cout << "WTF?" << endl;
  }
};

// Regenerate throw
bool isFixed = false;

void letstry() {
  cout << "Before try" << endl;
  try {
    cout << "Inside try: begin" << endl;
    if (!isFixed) {
      throw simpleException();
    } else {
      cout << "Fixed!" << endl;
    }
    cout << "Inside try: end" << endl;
  } catch(const simpleException& e) {
    e.what();
    if (!isFixed) {
      isFixed = true;
      throw;
    }
  }
}

void challenge1() {
  try {
    letstry();
  } catch (...) {
    if (isFixed) {
      cout << "Everything is okay" << endl;
    } else {
      cout << "Still not fixed! terminate()" << endl;
    }
  }
}

int main() {
  challenge1();
  return 0;
}
