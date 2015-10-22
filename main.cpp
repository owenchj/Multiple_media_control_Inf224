#include"manager.h"

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <memory>

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
  // intialize array of duration
  int tab[num_chapiter] = {1,2,3,4,5};  
  int const *tab_const = NULL;
  
  film *f = new film("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)num_chapiter, tab);  
  print_ss(f, ss);
   
  // to get the first address of the duration array in film, read-only
  tab_const = f->gettab();
  for(int i = 0; i < num_chapiter; i++)
    cout << tab_const[i] << endl; 
  
  // set film
  tab[4] = 100;
  f->set("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)num_chapiter, tab);
  print_ss(f, ss);
  // f->play();
  
  // test onject copy is ok
  // film *f_copy=new film(*f);
  film f_copy ; // only use full for a no-pointer object
  f_copy = *f;
  print_ss(&f_copy, ss);
  // change f to see whether his copy will changes 
  tab[4] = 6;
  f->set("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)num_chapiter, tab);
  print_ss(&f_copy, ss);



 
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
  //  china_group->play(*china_group);
  
  // Step 9 : test smart pointer 
  BasePtr v_s(new video("video","2105/10/6","../ressource/吾王,我愿永远做你的骑士.mp4", 149)); 
  BasePtr p_s(new photo("photo","2105/10/6","../ressource/tiantan.jpg", 1600, 1200));
  BasePtr f_s(new film("film","2105/10/6","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)num_chapiter, tab));  
  
  // raw pointer
  v_s->set("video","2105/10/20","../ressource/吾王,我愿永远做你的骑士.mp4"); 

  print_ss(&(*v_s), ss);
  print_ss(&(*p_s), ss);
  print_ss(&(*f_s), ss);
  // need not to delete the smart pointer  

  // Step 10 : test for manager
  manager m;

  // add a video
  BasePtr v_m;
  m.add_video("video","2105/10/22","../ressource/吾王,我愿永远做你的骑士.mp4", 149, v_m);
  
  BasePtr p_m;
  m.add_photo("photo","2105/10/20","../ressource/tiantan.jpg", 1600, 1200, p_m);
  
  BasePtr f_m;
  m.add_film("film","2105/10/20","../ressource/CHINA_IN_MOTION_2013.flv", 5400, (unsigned int)num_chapiter, tab, f_m);  
  
  // BasePtr g_m;
  // m.add_group("china_beauty","2015/10/10", "group","video_group", g_m);
  
   
  // add a group
  GroupPtr gg;
  m.add_group("group","2015/10/22", "china_beauty","china", gg);
  // add elements to this group
  gg->push_back(&(*v_m));
  gg->push_back(&(*p_m));
  gg->push_back(&(*f_m));
  gg->print(ss, *gg);

  // find a element
  BasePtr result;
  m.find_media("../ressource/tiantan.jpg", result);
  result->play();
  
  // test delete a element
  m.delete_media("../ressource/tiantan.jpg");
  m.find_media("../ressource/tiantan.jpg", result);
  if(result) result->play();

    
  GroupPtr find_g;
  m.find_group("china_beauty", find_g);
  m.delete_group("china_beauty");
  m.find_group("china_beauty", find_g);



    


  delete v;
  delete p; 
  delete [] media_tab;
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
