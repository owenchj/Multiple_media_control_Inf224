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


// print the characters of element
void print_ss(Base * b, stringstream &ss){
  cout << endl;
  ss.str("");
  b->print(ss);
 
#if COUT == 0
  cout << ss.str() << endl;
#endif
}



int main(int argc, char **argv){
  
  stringstream ss;

  // test base
  Base *b = new Base("film", "2015/9/9");  
  print_ss(b, ss);
  // change the value 
  b->set("base","base","base");
  print_ss(b, ss);



  // test video
  video *v = new video();  
  // set video
  v->set("video","2105/10/6","../ressource/吾王,我愿永远做你的骑士.mp4", 149);
  print_ss(v, ss);
  //v->play();




  // test photo
  photo *p = new photo();  
  // set photo
  p->set("photo","2105/10/6","../ressource/tiantan.jpg", 1600, 1200);
  print_ss(p, ss);
  //  p->play();



  
  // list polymorphisme 
  list<Base*> media;
  // add element to list
  media.push_back(b);
  media.push_back(v);
  media.push_back(p);
  // the length of list
  cout << media.size() << endl;
  // print the charaters of each elements in the list
  for (auto it : media) print_ss(it, ss);



  // test film
  film *f = new film();  
  int *tab = new int[num_chapiter]; 
  // intialize array of duration
  for(int i = 0; i < num_chapiter; i++)  tab[i] = i;
  // set film
  f->set("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)10, tab);
  print_ss(f, ss);
  // f->play();
  
  delete b;
  delete v;
  delete p; 
  delete f;
  delete []tab;


  return 0;

}
