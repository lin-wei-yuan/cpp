#include <iostream>
#include <boost/variant.hpp>
#include <string>

using namespace std;
using boost::variant;

void challenge1() {
  variant<string, int> var;
  var = "hello";
  cout << boost::get<string>(var);
  var = 20;
  cout << boost::get<int>(var);
}

struct showVariant : public static_vistor<> {
  void operator() (int I) const {
    cout << I << endl;
  }
  void operator() (const std::string& g) const {
    cout << g << endl;
  }
};

int main() {
  challenge1()
 }

