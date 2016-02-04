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
  // O(n)
  dq5.assign(dq1.begin(), dq1.end() - 1);
  print<deque<int>>(dq5);
}

void challenge(){
  deque<int> dq1;
  dq1.push_front(1); // O(1)
  dq1.push_back(10); // O(1)
  print<deque<int>>(dq1);

  deque<int> dq2;
  dq2.resize(10);//resize to take 10 elements
  print(deque<int>(dq2));//prints 10 zeros
  deque<int> dq3;
  for(int i=0; i<10; ++i){
      dq3.push_front(i);
      dq3.push_back(i);
    }
    print(deque<int>(dq3));
    dq3.pop_back();//pops the back
    dq3.pop_front();//pops the front;
    print(deque<int>(dq3));//prints dq3
    auto it = dq3[0]; //it points to value 8
    cout<<it;//prints the to value 8

}

int main () {
  challenge0();
  return 0;
}
