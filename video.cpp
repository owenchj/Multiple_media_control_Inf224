#pragma once
#include"MyClass.cpp"

class video : public base{
  int duree;
  
public: 
  video() : duree(0) {}
  video(string objnom, long date, string filenom, int duree) : base(objnom, date, filenom), duree(duree) {}
  virtual ~video(){}

  virtual void setter(string objnom,long date, string filenom, int duree){
    base::setter(objnom,date, filenom);
    this->duree=duree;
  }
  
  virtual int getduree() const{ return duree; }

  virtual string getfilename() const{ return base::getfilename(); }
  
  virtual void afficher(){
    base::afficher();
    cout<<"duree: "<<duree<<endl;
  }  

  virtual void play(string filenom) const{ 
    string s1="mplayer ";
    string s2=" &";
    string str=s1+filenom+s2;
    system(str.c_str());
  }
};
