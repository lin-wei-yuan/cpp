#include <boost/lexical_cast.hpp>
#include "./utils.h"
#include <string>

using boost::lexical_cast;

void challenge1() {
  string strOne = lexical_cast<string>(260); // converts int
  cout << strOne << endl;
  strOne = "helloworld" + lexical_cast<string>('A'); // converts a char and concantinates
  cout << strOne << endl;
  strOne = "hello world" + lexical_cast<string>(34.5); // converts double to string
  cout << strOne << endl;
}

int main() {
  challenge1();
  return 0;
}
