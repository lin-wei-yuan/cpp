#include <iostream>
#include <vector>
#include <list>
#include <set>
#include<deque>
#include<forward_list>
#include <stdexcept>
using namespace std;

template<typename T>
void print(const T& container) {
  if (container.empty()) {
    cout << "Empty!" << endl;
    return;
  }
  for (typename T::const_iterator it = container.begin(); it != container.end(); ++it) {
    cout << *(it) << " ";
  }
  cout << endl;
}
