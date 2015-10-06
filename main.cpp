#include"Base.h"
#include"video.h"
#include"photo.h"
#include"film.h"

#include<iostream>
#include<sstream>
#include<string>
#include <list>

using namespace std;

#define num_chapiter 10

int main(int argc, char **argv){
 
  Base *b = new Base("film", "2015/9/9");  

  stringstream ss;
  b->print(ss);
  cout << ss.str() << endl;
  // change the value 
  b->set("base","base","base");
  ss.str("");
  b->print(ss);
  cout << ss.str() << endl;

  // test video
  video *v = new video();  
  // set video
  v->set("video","2105/10/6","../ressource/吾王,我愿永远做你的骑士.mp4", 149);
  ss.str("");
  v->print(ss);
  cout << ss.str() << endl;
  // v->play();


  // test video
  photo *p = new photo();  
  // set photo
  p->set("photo","2105/10/6","../ressource/tiantan.jpg", 1600, 1200);
  ss.str("");
  p->print(ss);
  cout << ss.str() << endl;
  // p->play();
  
  
  list<Base*> media;

  media.push_back(b);
  media.push_back(v);
  media.push_back(p);
  cout << media.size() << endl;

  for (auto it : media){
    ss.str("");
    it->print(ss);
    cout << ss.str() << endl;
  }

  film *f = new film();  
  int *tab = new int[num_chapiter]; 
  
  for(int i = 0; i < num_chapiter; i++)
    tab[i] = i;
  // set film
  f->set("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)10, tab);
  ss.str("");
  f->print(ss);


  delete b;
  delete v;
  delete p; 
  delete f;
  delete []tab;


  return 0;

}
