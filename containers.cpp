#include <iostream>
#include <vector>
#include <list>
#include <set>
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

/* Vector */
void challenge1() {
  // O(1)
  vector<int> v1;
  print<vector<int>>(v1);
  // O(n), linear in count
  vector<int> v2(10, 1);
  print<vector<int>>(v2);
  // O(n), linear in count
  vector<int> v3(10);
  print<vector<int>>(v3);
  // O(n), linear in v3.size
  vector<int> v4(v3);
  print<vector<int>>(v4);
  // O(n), linear in distance between begin and end
  vector<int> v5(v3.begin(), v3.end());
  print<vector<int>>(v5);
  // cpp11
  #ifdef __cplusplus
    // O(n), linear in initializer_list size
    vector<int> v5_1({ 1 , 2});
    print<vector<int>>(v5_1);
  #endif

  // Accessors
  // O(n), linear in count
  vector<int> v6(10, 5);
  print<vector<int>>(v6);
  // O(n), linear in size of v6
  vector<int> v7 = v6;
  print<vector<int>>(v7);
  // O(n), linear in count
  vector<int> v8;
  v8.assign(10, 5);
  print<vector<int>>(v8);
  // O(n), linear in distance between begin and end
  v8.assign(v2.begin(), v2.end());
  print<vector<int>>(v8);

  // O(1), const
  int index = v8.at(0);
  cout << index << endl;
  // Return reference
  v8.at(0) = 9;
  // Generate std::out_of_range
  try {
    cout << v8.at(v8.size()) << endl;
  } catch(const std::out_of_range& e) {
    cout << e.what() << endl;
  }

  // No bounds checking is performed
  v8[0] = 1;
  // SF
  // v8[v8.size()] = 1;

  print<vector<int>>(v8);
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

  cout << v8.capacity() << ", " << v8.size() << endl;
  v8.reserve(11); // capacity = 11, size = 10
  v8.push_back(1); // capacity = 11, size = 11
  v8.push_back(1);  // capacity = 22(previous capacity x2), size = 11
  cout << v8.capacity() << ", " << v8.size() << endl;

  print<vector<int>>(v8);
  // Linear in the difference between the current size and count.
  v8.resize(5, 10);
  cout << v8.capacity() << endl;
  cout << v8.size() << endl;
  print<vector<int>>(v8);

  //Modifiers
  int numbers[] = { 1, 2, 3, 4, 5 };
  vector<int> v9(numbers, numbers + 5);
  // O(1 + dist(it, end))
  v9.insert(v9.end(), 6);
  print<vector<int>>(v9);
  // SF
  // v9.erase(v9.end());
  // O(n), linear in dist(it)
  v9.erase(v9.end() - 1);
  print<vector<int>>(v9);
  // Amortized O(1)
  v9.push_back(10);
  print<vector<int>>(v9);
  // O(1)
  v9.pop_back();
}

/* List */
void challenge2() {
  int numbers[] = { 1, 2, 3, 4, 5 };
  list<int> l1(numbers, numbers + 5);
  print<list<int>>(l1);

  list<int> l2;
  for (int i = 0; i < 10; ++i) {
    l2.push_back(i);
  }
  print<list<int>>(l2);

  for (int i = 0; i < 10; ++i) {
    l2.push_front(i);
  }
  print<list<int>>(l2);

  for (int i = 0; i < 10; ++i) {
    l2.pop_front();
  }
  print<list<int>>(l2);
  for (int i = 0; i < 10; ++i) {
    l2.pop_back();
  }
  print<list<int>>(l2);
}

/* Set */
void challenge3() {
  int numbers[] = { 1, 3, 2, 4, 5, 5, 4, 3, 2, 1 };
  set<int>  s1(numbers, numbers + 10);
  print<set<int>>(s1);

  cout << s1.size() << endl;
  // O(logn)
  cout << s1.count(2) << endl;
  // O(logn)
  auto search = s1.find(3);
  if (search != s1.end()) {
    cout << (*search) << endl;
  } else {
    cout << "not found!" << endl;
  }
  // insert overloads
  auto result = s1.insert(6);
  // std::pair<it, bool>
  cout << (*result.first) << ", " << result.second << ", " << std::distance(s1.begin(), result.first) << endl;
  print<set<int>>(s1);
  // O(1) if before of after result.first, else O(logn)
  auto it = s1.insert(result.first, 8);
  cout << (*it) << endl;
}

int main() {
  challenge1();
  // challenge2();
  // challenge3();
  return 0;
}
