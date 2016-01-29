#include "./utils.h"
void challenge(){
  // o(1)
  forward_list<int> listOne;
  print(forward_list<int>(listOne));//prints empty list 
  //o(n) linear time
  forward_list<int> listTwo(1,2);//takes one element of two
  print(forward_list<int>(listTwo));//prints 2 
  // o(n) linear time
  forward_list<int>listThree(10);//makes a foward list of size ten
  cout<<listThree.size();//prints the size of 10
  print(forward_list<int>(listThree));//prints 10 values of zero
  listThree.push_front(10);//pushs interger to to front of foward_list o(1)
  print(foward_list<int>(listThree);//o(n)
  for(int i=0; i<10; ++i){
        listFour.push_front(i);
    }//push 0 to 9 to front of list
   
   //modifers
   listFour.pop_front();//removes 9 from the forward list
   print(forward_list<int>(listFour));
   forward_list<int> listFive;//create a new forward list
   listFive.push_front(1);//push to the front of the forward list
   listFive.clear();//clears list five
   //operations
   listFive.merge(listFour);//merge list five with list three
   print(forward_list<int>(listFive));
   forward_list<int>listSix={1,2,6,3,4};
   forward_list<int>listSeven={2,4};
   listSeven.splice_after(listSix.before_begin(),listSeven);//splice listseven
   print(forward_list<int>(listSix));//list six contains 2412634
   print(forward_list<int>(listSeven));//list seven is now empty
   
}
  
