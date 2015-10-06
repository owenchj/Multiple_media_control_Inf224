#ifndef PHOTO_H
#define PHOTO_H


#include"Base.h"

class photo : public Base{
  float length;
  float width;

public:

 photo() : length(0.0), width(0.0) {}

 photo(string obj_name, string date, string file_name, float length, float width) : Base(obj_name, date, file_name), length(length), width(width) {}

  virtual ~photo(){}

  virtual void set(string obj_name, string date, string file_name, float length, float width){
    Base::set(obj_name, date, file_name);
    this->length = length;    
    this->width = width;    
  }
  
  virtual float get_length() const { return length; }
  
  virtual float get_width()  const { return width; }
  
  virtual void print(ostream & s) const {
    Base::print(s);
    s << get_length() << ' ' << get_width()  << ' ';
    // cout<<"length: "<<length<<endl;
  }
  
  virtual string get_file_name() const { return Base::get_file_name(); }

  virtual void play() const {  
    string player="eog ";
    string suffix=" &";
    string str = player + get_file_name() + suffix;
    system(str.c_str());
  }

  /* virtual void play(string file_name) const {   */
  /*   string player="eog "; */
  /*   string suffix=" &"; */
  /*   string str = player + file_name + suffix; */
  /*   system(str.c_str()); */
  /* } */


};

#endif
