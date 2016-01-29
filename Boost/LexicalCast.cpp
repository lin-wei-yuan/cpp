#include <boost/lexical_cast.hpp>
#include "./utils.h"
#include<string>
using boost::lexical_cast;

void challenge(){
   int numberOne =260;//int definition
   string strOne =lexical_cast<string>(numberOne);//converts numberOne to str
   cout<<strOne;//prints the StrOne
}
