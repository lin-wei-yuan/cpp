#include <iostream>
#include <vector>
#include <list>
using namespace std;

void print_vector(const vector<int>& v) {
  for(size_t i = 0; i < v.size(); ++i) {
    cout << v.at(i) << "( " << &v.at(i) << ")" << endl;
  }
  cout << endl;
  cout << endl;
}
/* Vector */
void challenge1() {
  // init
  vector<int> v1;
  print_vector(v1);
  vector<int> v2(10, 1);
  print_vector(v2);
  vector<int> v3(10);
  print_vector(v3);
  vector<int> v4(v3);
  print_vector(v4);
  vector<int> v5(v3.begin(), v3.end());
  print_vector(v5);
  // cpp11
  // vector<int> v6({ 1 , 2});
  // print_vector(v6);

  // Accessors
  vector<int> v6(10, 5);
  print_vector(v6);
  vector<int> v7 = v6;
  print_vector(v7);
  vector<int> v8;
  v8.assign(10, 5);
  print_vector(v8);
  v8.assign(v2.begin(), v2.end());
  print_vector(v8);

  // v8
  int index = v8.at(0);
  cout << index << endl;

  v8.at(0) = 9;
  print_vector(v8);
  // Iterators
  for(vector<int>::iterator it =  v8.begin(); it != v8.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
  for(vector<int>::const_iterator it =  v8.begin(); it != v8.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
  for(vector<int>::reverse_iterator it =  v8.rbegin(); it != v8.rend(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
  cout << v8.capacity() << endl;
  // v8.reserve(11);
  cout << v8.capacity() << endl;

  v8.push_back(1);
  cout << v8.capacity() << endl;
  print_vector(v8);

  v8.resize(5, 10);
  cout << v8.capacity() << endl;
  cout << v8.size() << endl;
  print_vector(v8);
}

void print_list(const list<int>& l) {
  for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
    cout << *it << " (" << &(*it) << ")" << endl;
  }
}

void challenge2() {
  int numbers[] = { 1, 2, 3, 4, 5 };
  list<int> l1(numbers, numbers + 5);
  print_list(l1);
  list<int> l2;
  for (int i = 0; i < 10; ++i) {
    l2.push_back(i);
  }
  print_list(l2);

  for (int i = 0; i < 10; ++i) {
    l2.push_front(i);
  }
  print_list(l2);
  for (int i = 0; i < 10; ++i) {
    l2.pop_front();
  }
  print_list(l2);

  for (int i = 0; i < 10; ++i) {
    l2.pop_back();
  }
  print_list(l2);
}




int main() {
  // challenge1();
  challenge2();
  return 0;
}
