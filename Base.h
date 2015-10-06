#ifndef BASE_H
#define BASE_H

// '1' for cout, '0' for sstream
#ifndef COUT
#define COUT 0
#endif


#include<string>
#include<iostream>
using namespace std;

class Base{
 private:
  string obj_name;
  string date;
  string file_name;
  
 public:
  Base(string obj_name = "INF224", string date = "2015/9/30", string file_name = "TP");
  virtual ~Base();
  virtual string  get_obj_name() const;
  virtual string  get_date() const;
  virtual string  get_file_name() const;
  virtual void    set(string obj_name,string date, string file_name);
  virtual void    print(ostream & s) const;
};
   
#endif
