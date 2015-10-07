#include"Base.h"
#include"video.h"
#include"photo.h"
#include"film.h"
#include"group.h"

#include<iostream>
#include<sstream>
#include<string>
#include <list>

using namespace std;

#define num_chapiter 5


// print the characters of element
void print_ss(Base * b, stringstream &ss){
  cout << endl;
  ss.str("");
  b->print(ss);
 
#if COUT == 0
  cout << ss.str() << endl;
#endif
}


void playMedia(Base ** tab, unsigned int count) {
  for (unsigned int k = 0; k < count; ++k) {
    // tab[k]->play();
  }
}





int main(int argc, char **argv){
  
  stringstream ss;


  // test video
  video *v = new video();  
  // set video
  v->set("video","2105/10/6","../ressource/吾王,我愿永远做你的骑士.mp4", 149);
  print_ss(v, ss);
  //  v->play();




  // test photo
  photo *p = new photo();  
  // set photo
  p->set("photo","2105/10/6","../ressource/tiantan.jpg", 1600, 1200);
  print_ss(p, ss);
  // p->play();


  // table of polymorphisme 
  Base ** media_tab = new Base * [10];
  unsigned int count = 0;
  media_tab[count++] = v;
  media_tab[count++] = p;
  playMedia(media_tab, count);
 

  // test film
  film *f = new film();  
  // int *tab = new int[num_chapiter]; 
  // intialize array of duration
  int const tab[num_chapiter] = {1,2,3,4,5}; 
  //for(int i = 0; i < num_chapiter; i++)  tab[i] = i;

  // set film
  f->set("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)num_chapiter, tab);
  print_ss(f, ss);
  // f->play();
  



 
  // test for group
  photo **p1 = new photo * [3];
  video **v1 = new video * [2];
  film **f1 = new film * [2];
  
  p1[0] = p;
  p1[1] = new photo("photo","2105/10/10","../ressource/icons/images/copy.png", 20, 20); 
  p1[2] = new photo("photo","2105/10/10","../ressource/icons/images/paste.png", 20, 20); 
  
  v1[0] = v;
  v1[1] = new video("video","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 400);
  
  int tab_1[1] = {149};
  f1[0] = f;
  f1[1] = new film("film","2105/10/6","../ressource/吾王,我愿永远做你的骑士.mp4", 148, 1, tab_1 ); 
  

  group *video_group = new group("group","2015/10/10", "group","video_group");
  video_group->push_back(v1[0]);
  video_group->push_back(v1[1]);
  cout << video_group->size() << endl;
  video_group->print(ss, *video_group);

  group *photo_group = new group("group","2015/10/10", "group","photo_group");
  photo_group->push_back(p1[0]);
  photo_group->push_back(p1[1]);
  photo_group->push_back(p1[2]);
  cout << photo_group->size() << endl;
  photo_group->print(ss, *photo_group);

  group *film_group = new group("group","2015/10/10", "group","film_group");
  film_group->push_back(f1[0]);
  film_group->push_back(f1[1]);
  cout << film_group->size() << endl;
  film_group->print(ss, *film_group);

  group *china_group = new group("group","2015/10/10", "group","china");
  china_group->push_back(v1[0]);
  china_group->push_back(p1[0]);
  china_group->push_back(f1[0]);
  cout << china_group->size() << endl;
  china_group->print(ss, *china_group);
  
  china_group->group_playMedia(*china_group);

  delete v;
  delete p; 
  delete f;
  
  delete [] p1;
  delete [] v1;
  delete [] f1;

  delete video_group;
  delete photo_group;
  delete film_group;
  delete china_group;
  
  return 0;

}
