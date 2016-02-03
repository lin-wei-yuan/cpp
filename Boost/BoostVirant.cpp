
#include<string>
#include<iostream>
#include "boost/variant.hpp"

using boost::variant;
void challenge(){
  variant<std::string,double,int> Var;
  Var = "hello";
 std::cout<<Var<<std::endl;
  Var = 3.13;
  std::cout<<Var<<std::endl;//prints var
  Var =21;//makes var =21
  std::cout<<Var<<std::endl;//prints 21
  std::cout<<boost::get<int>(Var)<<std::endl;//prints the variant value of the int hence 21
}

struct ShowVariant: public boost::static_visitor<>{
  void operator()(int I)const{ std::cout<<I<<std::endl;}
  void operator()(std::string g)const{std::cout<<g<<std::endl;}
};
int main(){
   boost::variant<int,std::string> var;
   var = 1;
   boost::apply_vistor(showVariant{},var)
   }
