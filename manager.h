
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
typedef std::shared_ptr<group> GroupPtr;

typedef map<string, BasePtr> MediaMap; 
typedef map<string, GroupPtr> GroupMap; 




class manager{
 private:
  MediaMap media;
  GroupMap media_group;

 public: 
  manager(){}
  
  virtual ~manager(){}
  
  virtual void add_video(string obj_name, string date, string file_name, int duration, BasePtr &v_s){
    BasePtr v(new video(obj_name, date, file_name, duration));
    media[file_name] = v; 
    v_s = v;
  }


  virtual void add_photo(string obj_name, string date, string file_name, float length, float width, BasePtr &p_s){
    BasePtr p(new photo(obj_name, date, file_name, length,  width));
    media[file_name] = p; 
    p_s = p;
  }
  
  virtual void add_film(string obj_name, string date, string file_name, int duration, unsigned int num_chapiter, int const *tab, BasePtr &f_s){ 
    BasePtr f(new film(obj_name, date, file_name, duration, num_chapiter, tab)); 
    media[file_name] = f; 
    f_s = f;
  }

  virtual void add_group(string obj_name, string date, string file_name, string group_name, GroupPtr & g_s){
    GroupPtr g(new group(obj_name, date, file_name, group_name));
    media_group[file_name] = g;
    g_s = g;
  }

  
  // delete a media 
  virtual void delete_media(string file_name) {
    map<string, GroupPtr>::iterator it;
    
    for(it = media_group.begin(); it != media_group.end(); it++) {
      it->second->find_delete(*(it->second), file_name);
    }

    media.erase(file_name);
  }

  // delete a group
  virtual void delete_group(string file_name) {
    media_group.erase(file_name);
  }

  // find without return for group or media
  virtual void find(string file_name) const{
    auto it = media.find(file_name);
    
    if (it == media.end()){
      cout << "not find in media" << endl;
    }
    else{
      // print result
      stringstream ss;
      ss.str("");
      cout << endl;
	
      it->second->print(ss);

#if COUT == 0
      cout << ss.str() << endl;
#endif
    }
    
    auto it_group = media_group.find(file_name);
    
    if (it_group == media_group.end()){
      cout << "not find in group" << endl;
    }
    else{
      // print result
      stringstream ss;
      ss.str("");
      cout << endl;
	
      it_group->second->print(ss, *(it_group->second));

#if COUT == 0
      cout << ss.str() << endl;
#endif
    }

  }

  // find with return a BasePtr result 
  virtual void find_media(string file_name, BasePtr & result) const{
      auto it = media.find(file_name);
      
      if (it == media.end()){
	cout << "not find" << endl;
	result = NULL;
      }
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
  
  // find with return a GroupPtr result 
  virtual void find_group(string file_name, GroupPtr & result) const{
      auto it = media_group.find(file_name);
      
      if (it == media_group.end()){
	cout << "not find" << endl;
	result = NULL;
      }
      else{
	// print result
	stringstream ss;
	ss.str("");
	cout << endl;
	
	result = it->second;
	it->second->print(ss, *result);

#if COUT == 0
	cout << ss.str() << endl;
#endif
      }
      
  }


  // play a group or a media
  virtual void play(string file_name) const{
      auto it = media.find(file_name);
      
      if (it == media.end())
	cout << "not find" << endl;
      else{
	it->second->play();
      }


      auto it_group = media_group.find(file_name);
      
      if (it_group == media_group.end())
	cout << "not find" << endl;
      else{
	it_group->second->play( *(it_group->second) );
      }

  }

};

#endif



