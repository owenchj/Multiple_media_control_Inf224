#include"MyClass.cpp"
#include<list>

class group : public base, public list<base>{
 
 string groupnom;

public:
  group(string objnom="",long date=0, string filenom="", string groupnom=""): base(objnom, date,  filenom), groupnom(groupnom){}
  ~ group(){}
  




};
