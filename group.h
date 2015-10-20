#ifndef GROUP_H
#define GROUP_H

#include "Base.h"
#include<list>

class group : public Base, public list<Base *>{
  
 private:
  string group_name;

 public:
  
 group():group_name("group_1"){};
 group(string obj_name, string date, string file_name, string group_name = "group_1" ) : Base(obj_name, date,  file_name), group_name(group_name){}

  virtual string get_group_name()  const { return group_name; }
  
  // print the group element
  virtual void print(ostream & s, group const &g) const{
    
    for (group::const_iterator it = g.begin(); it != g.end(); it++)
      (**it).print(s);
    //g->front()->print(s);
    
 }

  // play the group element
  virtual void play(group const &g) const{
    for (group::const_iterator it = g.begin(); it != g.end(); ++it)
      (**it).play();
  }


  virtual ~group(){}
};


#endif
