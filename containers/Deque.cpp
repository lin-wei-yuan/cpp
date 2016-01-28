
#include "./utils.h"

void challenge(){
  deque<int> dq1;
  dq1.push_front(1);//push 1 to front of the deque at constant time
  dq1.push_back(10);//push 10 to the back of the deque at constant time 
  print(deque<int>(dq1));//prints the elements of 1,10
  deque<int> dq2;//creates dq2
  dq2.resize(10);//resize to take 10 elements 
  print(deque<int>(dq2));//prints 10 zeros
  deque<int> dq3;
  for(int i=0; i<10; ++i){
      dq3.push_front(i);
      dq3.push_back(i);
    }
    print(deque<int>(dq3));

}
