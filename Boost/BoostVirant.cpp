#include<string>
#include<iostream>
#include "boost/variant.hpp"
using boost::variant
void challenge(){
  variant<string,double,int> Var;
  Var = "hello";
  cout<<Var<<endl;
  Var = 3.13;//
  cout<<Var<<endl;//prints var
  Var =21;//makes var =21
  cout<<Var<<endl;//prints 21
  cout<<boost::get<int>(Var)<<endl;//prints the variant value of the int hence 21
}
