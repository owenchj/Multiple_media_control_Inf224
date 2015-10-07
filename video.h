#ifndef VIDEO_H
#define VIDEO_H


#include"Base.h"

class video : public Base{
  int duration;
  
 public: 
 video() : duration(0) {}

 video(string obj_name, string date, string file_name, int duration = 0) : Base(obj_name, date, file_name), duration(duration) {}

  virtual ~video(){}

  virtual void set(string obj_name, string date, string file_name, int duration){
    Base::set(obj_name, date, file_name);
    this->duration = duration;
  }
  
  virtual int get_duration()      const { return duration; }

  virtual string get_file_name()  const { return Base::get_file_name(); }
  
  virtual void print(ostream & s) const{
    Base::print(s);
    s << get_duration() << ' ' ;

    #if COUT == 1
      cout<<"duration : "<< duration << endl;
    #endif
  }  

  virtual void play() const{ 
    string player = "mpv ";
    string suffix = " &";
    string str = player + get_file_name() + suffix;
    system(str.c_str());
  }
  
  /*  virtual void play(string file_name) const{  */
  /*   string player = "mplayer "; */
  /*   string suffix = " &"; */
  /*   string str = player + file_name + suffix; */
  /*   system(str.c_str()); */
  /* } */
};

#endif


/* #if DLEVEL > 5 */
/*     #define SIGNAL  1 */
/*     #if STACKUSE == 1 */
/*         #define STACK   200 */
/*     #else */
/*         #define STACK   100 */
/*     #endif */
/* #else */
/*     #define SIGNAL  0 */
/*     #if STACKUSE == 1 */
/*         #define STACK   100 */
/*     #else */
/*         #define STACK   50 */
/*     #endif */
/* #endif */
