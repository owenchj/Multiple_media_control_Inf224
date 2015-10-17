#ifndef FILM_H
#define FILM_H

#include"video.h"

class film : public video{

 private:
  unsigned int num_chapiter;
  int *tab; 

 public:
  film():num_chapiter(),tab(NULL){}

  film (string obj_name, string date, string file_name, int duration, unsigned int num_chapiter = 0, int const *tab = NULL) : video(obj_name, date, file_name, duration), num_chapiter(num_chapiter){
    this->tab = new int[num_chapiter];
    for( unsigned int i = 0 ; i < num_chapiter; i++)
      this->tab[i] = tab[i];
  }
  
  ~film(){ delete []tab;}

  virtual void set(string obj_name, string date, string file_name, int duration, unsigned int num_chapiter, int const *tab){ 
    
    video::set(obj_name, date, file_name, duration);
    
    for( unsigned int i = 0 ; i < num_chapiter; i++){
      this->tab[i] = tab[i];
    }
    
    this->num_chapiter = num_chapiter;
  }
  
  virtual unsigned int get_num_chapiter() const {return num_chapiter;}

  virtual int const* gettab() const { return tab; }

  virtual void print(ostream & s) const {
    video::print(s);
   
    s << get_num_chapiter() << endl;
    for(unsigned int k=0; k<num_chapiter; k++)
      s <<"The duration of chapiter "<<k<<" is "<<tab[k]<<endl;
	
    
#if COUT == 1
    cout<<"num chapiter: "<< get_num_chapiter() << endl;
    for(unsigned int k=0; k<num_chapiter; k++)
      cout<<"The duration of chapiter "<<k<<" is "<<tab[k]<<endl;
#endif
  }


  // define the copy
 film(const film&from) : video(from) {
    
    num_chapiter = from.num_chapiter;
    
    if (from.tab){
      tab = new int[from.num_chapiter];
      for( unsigned int i = 0 ; i < num_chapiter; i++)
	tab[i] = from.tab[i];
    }
    else tab = NULL;
  }
  
  virtual film & operator=(const film& from) {

    video::operator=(from); 
    num_chapiter = from.num_chapiter;

    if (tab && from.tab){
      for( unsigned int i = 0 ; i < num_chapiter; i++)
	tab[i] = from.tab[i];
    }
    else {
      delete []tab;
      if(from.tab){ 
	tab = new int[num_chapiter];
	for( unsigned int i = 0 ; i < num_chapiter; i++)
	  tab[i] = from.tab[i];
      }
      else tab = NULL;
    }
    
    return *this;
  }

  
};

#endif
