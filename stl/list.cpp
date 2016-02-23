#include "./utils.h"

/* List */
void challenge() {
  int numbers[] = { 1, 2, 3, 4, 5 };
  list<int> l1(numbers, numbers + 5);
  print<list<int> >(l1);

  list<int> l2;
  for (int i = 0; i < 10; ++i) {
    l2.push_back(i);
  }
  print<list<int> >(l2);

  for (int i = 0; i < 10; ++i) {
    l2.push_front(i);
  }
  print<list<int> >(l2);

  for (int i = 0; i < 10; ++i) {
    l2.pop_front();
  }
  print<list<int> >(l2);
  for (int i = 0; i < 10; ++i) {
    l2.pop_back();
  }
  print<list<int> >(l2);

  list<int> l3 (numbers, numbers + 5);
  // O(1)
  l3.erase(l3.begin());
  print<list<int> >(l3);
  // O(n), n = distance(begin, end)
  l3.erase(l3.begin(), l3.end());
  print<list<int> >(l3);
  // List operations
  list<int> l4 (numbers, numbers + 5);
  list<int> l5 (numbers, numbers + 5);
  // O(size() + size() - 1)
  l4.merge(l5);
  print<list<int> >(l4);
  print<list<int> >(l5); // Empty

  list<int> l6 (numbers, numbers + 5);
  print<list<int> >(l6);
  // O(n)
  l6.reverse();
  print<list<int> >(l6);
  // O(nlog(n))
  l6.sort();
  print<list<int> >(l6);

  print<list<int> >(l4);
  // O(n)
  l4.unique();
  print<list<int> >(l4);
}


int main() {
  challenge();
  return 0;
}
