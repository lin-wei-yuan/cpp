#include<threads>
#include<iostream>
using namespace std;
void challege(){
  cout<<"this is challege function"<<endl;
}

void challengeTwo(int number,string name){
   mutex myMutex;//creates my mutex
   myMutex.lock();//locks the cout from other threads
   for(int i=0; i<number; ++i){
    cout<<name<<endl;//prints name 100 times
    }//closing of for loop
    myMutex.unlock();//unlocks mutex once thread is done
}//closing of the challenge function


int main(){
   thread threadOne(Challenge);
   thread myThread(challengeTwo,10,"gavin");//thread object taking three parametres
   thread myThread2(challengeTwo,10,"goodship");//thread object taking three parametres
   myThread.join();//main waits for mythread to finsh
   myThread2.join();//main waits for mythread2 to finish
   threadOne.join();//waits for the child thread to finsh
}
