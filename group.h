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
    
    std::cout <<"Groupname: "<<group_name<<std::endl;
    for (group::const_iterator it = g.begin(); it != g.end(); it++)
      (**it).print(s);
    //g->front()->print(s);
  }

  // find a eletement and delete
  virtual bool find_delete(group &g, string file_name) const{
    for (group::const_iterator it = g.begin(); it != g.end(); ++it){
      if((**it).get_file_name() == file_name){
	g.remove(*it);
	return true;
      }
    }

    return false;
  }
    
  // play the group element
  virtual void play(group const &g) const{
    std::cout <<"play"<<std::endl;
  
    for (group::const_iterator it = g.begin(); it != g.end(); ++it)
      (**it).play();
  }


  virtual ~group(){}
};


#endif
