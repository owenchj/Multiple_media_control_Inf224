#include<string>
#include<iostream>
#include<sstream>
#include "Base.h"


Base::Base(string obj_name, string date, string file_name) : obj_name(obj_name) , date(date), file_name(file_name){}  
  
void Base::set(string obj_name, string date, string file_name){
  this->obj_name =  obj_name;
  this->date = date;
  this->file_name = file_name;
}  

string  Base::get_obj_name()  const { return obj_name; }
string  Base::get_date()      const { return date;     }
string  Base::get_file_name() const { return file_name;}

void Base::print(ostream & s) const {
  s << get_obj_name() <<' '<< get_date() <<' '<< get_file_name() << ' ';
  
  #if COUT == 1
  cout << "obj name : " << get_obj_name() << endl << "date     : " <<get_date() << endl << "file name: " <<get_file_name() << endl;
  #endif
}


Base::~Base(){}
