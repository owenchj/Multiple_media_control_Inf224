#ifndef FILM_H
#define FILM_H

#include"video.h"

class film : public video{
private:
  unsigned int num_chapiter;
  int *tab; 
public:
  film(){}

  film (string obj_name, string date, string file_name, int duration, unsigned int num_chapiter = 0, int *tab = NULL) : video(obj_name, date, file_name, duration), num_chapiter(num_chapiter), tab(tab){}

  ~film(){delete []tab;}

  virtual void set(string obj_name, string date, string file_name, int duration, unsigned int num_chapiter, int *tab){ 
    video::set(obj_name, date, file_name, duration);
    this->tab = tab;
    this->num_chapiter = num_chapiter;
  }
  virtual unsigned int get_num_chapiter() const {return num_chapiter;}

  virtual int * gettab() const { return tab; }

  virtual void print(ostream & s) const {
    video::print(s);

    cout<<"The number of chapiter is  "<< get_num_chapiter() << endl;
    for(unsigned int k=0; k<num_chapiter; k++)
      cout<<"The duration of chapiter "<<k<<" is "<<tab[k]<<endl;
  }

  virtual void play(string file_name) const{ 
    
  }

};

#endif
