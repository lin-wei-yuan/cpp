#include "./utils.h"

void challenge0() {
  // O(n)
  deque<int> dq1(5);
  print<deque<int>>(dq1);
  // O(n)
  deque<int> dq2(5, 5);
  print<deque<int>>(dq2);
  // O(n) - between first and last
  deque<int> dq3(dq2.begin(), dq2.end());
  print<deque<int>>(dq3);
  // O(n) - size of other
  deque<int> dq4(dq2);
  print<deque<int>>(dq4);
  // O(1)
  deque<int> dq5(move(dq2));
  print<deque<int>>(dq5);
  // O(n)
  dq5.assign(5, 6);
  print<deque<int>>(dq5);
  // O(n) - between first and last
  dq5.assign(dq1.begin(), dq1.end() - 1);
  print<deque<int>>(dq5);
  // O(n)
  deque<int> dq6 = dq1;
  print<deque<int>>(dq6);
  // O(1)!
  deque<int> dq7 = move(dq1);
  print<deque<int>>(dq7);
  // Empty after moving
  print<deque<int>>(dq1);
}

void challenge1() {
  deque<int> dq1;
  for (int i = 0; i < 10; ++i) {
    // O(1)
    dq1.push_front(i);
    // O(1)
    dq1.push_back(i);
  }
  print<deque<int>>(dq1);
}

void challenge2(){
  deque<int> dq1;
  // O(1)
  dq1.push_front(1);
  // O(1)
  dq1.push_back(10);
  print<deque<int>>(dq1);
  deque<int> dq2;
  // O(n)
  dq2.resize(10);
  print(deque<int>(dq2));

  deque<int> dq3;
  for(int i=0; i<10; ++i){
    // O(1)
    dq3.push_front(i);
    // O(1)
    dq3.push_back(i);
  }
  print(deque<int>(dq3));
  // O(1)
  dq3.pop_back();
  // O(1)
  dq3.pop_front();
  print(deque<int>(dq3));
  // O(1)!
  auto it = dq3[0];
  try {
    // O(1) with cheking range
    auto it = dq3.at(dq3.size() + 1);
    cout << it << endl;
  } catch (const exception& e) {
    cout << e.what() << endl;
  }
}

int main () {
  challenge0();
  challenge1();
  challenge2();
  return 0;
}
