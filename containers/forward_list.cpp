#include "./utils.h"

void challenge0(){
  // O(1)
  forward_list<int> listOne;
  print<forward_list<int>>(listOne);
  // O(n) linear time
  forward_list<int> listTwo(1,2); // takes one element of two
  print<forward_list<int>>(listTwo);
   // O(n) linear time
  forward_list<int> listThree(10);
  print<forward_list<int>>(listThree);
  // O(1)
  listThree.push_front(10);
  print<forward_list<int>>(listThree);

  forward_list<int> listFour;
  for(int i = 0; i < 10; ++i) {
    listFour.push_front(i);
  }
  // O(1)
  listFour.pop_front();
  print<forward_list<int>>(listFour);

  forward_list<int> listFive;
  listFive.push_front(1);
  listFive.clear();
  // operations
  // O(n) - size() + other.size() - 1
  listFive.merge(listFour); // merge list five with list three
  print<forward_list<int>>(listFive);
  // O(1)
  forward_list<int> listSix = { 1, 2, 6, 3, 4 };
  forward_list<int> listSeven = { 2, 4 };
  print<forward_list<int>>(listSix);
  print<forward_list<int>>(listSeven);
  listSeven.splice_after(listSix.before_begin(), listSeven);
  print<forward_list<int>>(listSix);
  print<forward_list<int>>(listSeven);
}

  int main() {
    challenge0();
    return 0;
  }
