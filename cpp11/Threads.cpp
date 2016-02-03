#include<threads>
#include<iostream>
using namespace std;
void challege(){
  cout<<"this is challege function"<<endl;
}

int main(){
  thread threadOne(Challenge);
  threadOne.join();//waits for the child thread to finsh
}
