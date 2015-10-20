
#ifndef MANAGER_H
#define MANAGER_H


#include <map>
#include <memory>
#include <iostream>
#include <sstream>

#include"Base.h"
#include"video.h"
#include"photo.h"
#include"film.h"
#include"group.h"

typedef std::shared_ptr<Base> BasePtr;

typedef map<string, BasePtr> MediaMap; 


class manager{
 private:
  MediaMap media;
  
 public: 
  manager(){}
  
  virtual ~manager(){}
  
  virtual void add_video(string obj_name, string date, string file_name, int duration, BasePtr &v_s){
    BasePtr v(new video(obj_name, date, file_name, duration));
    media[obj_name] = v; 
    v_s = v;
  }


  virtual void add_photo(string obj_name, string date, string file_name, float length, float width, BasePtr &p_s){
    BasePtr p(new photo(obj_name, date, file_name, length,  width));
    media[obj_name] = p; 
    p_s = p;
  }
  
  virtual void add_film(string obj_name, string date, string file_name, int duration, unsigned int num_chapiter, int const *tab, BasePtr &f_s){ 
    BasePtr f(new film(obj_name, date, file_name, duration, num_chapiter, tab)); 
    media[obj_name] = f; 
    f_s = f;
  }

  virtual void add_group(string obj_name, string date, string file_name, string group_name, BasePtr & g_s){
    BasePtr g(new group(obj_name,  date, file_name, group_name));
    media[obj_name] = g; 
    g_s = g;
  }

  virtual void find(string obj_name, BasePtr & result) const{
      auto it = media.find(obj_name);
      
      if (it == media.end())
	cout << "not find" << endl;
      else{
	// print result
	stringstream ss;
	ss.str("");
	cout << endl;
	
	result = it->second;
	it->second->print(ss);
#if COUT == 0
	cout << ss.str() << endl;
#endif
      }
  }
  

 
  /* virtual void play() const{  */
  /*   string player = "mpv "; */
  /*   string suffix = " &"; */
  /*   string str = player + get_file_name() + suffix; */
  /*   system(str.c_str()); */
  /* } */

};

#endif



