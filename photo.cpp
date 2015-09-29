#pragma once
#include"MyClass.cpp"

class photo : public base{
  string lieu;

public:

  photo() : lieu(""){}
  photo(string objnom, long date, string filenom, string lieu) : base(objnom, date, filenom), lieu(lieu) {}
  virtual ~photo(){}

  virtual   void setter(string objnom,long date, string filenom, string lieu){
    base::setter(objnom,date, filenom);
    this->lieu=lieu;    
  }
  
  virtual   string getlieu() const{ return lieu; }
  
  virtual   void afficher(){
    base::afficher();
    cout<<"lieu: "<<lieu<<endl;
  
}
  virtual string getfilename() const{ return base::getfilename(); }

  virtual void play(string filenom) const{ 
    string s1="eog ";
    string s2=" &";
    string str=s1+filenom+s2;
    system(str.c_str());
  }

};
