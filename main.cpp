#include"Base.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int main(int argc, char **argv){
  /*
  string objnom="car";
  string filenom="/home/owen";
  long date=12345;
  
  
  base *b=new base();
  base *c=new base(objnom, date, filenom); 
  video *v=new video();
  photo *p=new photo();
  b->afficher();  
  c->afficher();  
  b->setter("moto", 23456, "/home/owen/moto");
  b->afficher();
  v->setter("video",12,"/home/owen/video",90);
  p->setter("video",v->getduree(),"/home/owen/photo","Paris");
  v->afficher();
  p->afficher();
  delete b;
  delete c;

  int i=0;
  base** tab=new base*[10];
  tab[i++]=new photo("photo", date, filenom, "beijing");
  tab[i++]=new photo("photo", date, filenom, "paris");
  tab[i++]=new video("video", date, filenom, 34);
  tab[i++]=new video("video", date, filenom, 50);
  for (int k = 0; k < i; k++) {
    cout << "objnom = " << tab[k]->getobjnom() << endl;
  }
  delete [] tab;
  */
  
  // static const int count=10;
  // int *tab1=new int[count];
  // for(int k=0;k<count;k++) tab1[k]=k;

  // int *tab2=new int[count+4];
  // for(int k=0;k<count+4;k++)  tab2[k]=k;
  // film *f=new film("film",20150219,"/home/owen/inf224/ressource/CHINA_IN_MOTION_2013.flv", 251, count, tab1);
  // f->afficher();
  // f->modifier (count+4, tab2);
  // f->afficher();
  // f->play(f->getfilename());
  
  // video *v=new video("video",20150220,"/home/owen/inf224/ressource/吾王,我愿永远做你的骑士.mp4", 251);
  // v->play(v->getfilename());

  // photo *p=new photo("photo",20150220,"/home/owen/inf224/ressource/doxygen.jpg", "Paris");
  // p->play(p->getfilename());

  // delete v;
  // delete v;
  // delete f;
  // delete [] tab1;
  // delete [] tab2;
  Base *b = new Base("film", "2015/9/9");  

  stringstream ss;
  b->print(ss);
  b->set("a","b","l");
  b->print(ss);
  delete b;
  return 0;
}
