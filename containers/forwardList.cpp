#include "./utils.h"


void challenge(){
  // o(1)
  forward_list<int> listOne;
  print(forward_list<int>(listOne));//prints empty list 
  //o(n) linear time
  forward_list<int> listTwo(1,2);//takes one element of two
  print(forward_list<int>(listTwo));//prints 2 
  // o(n) linear time
