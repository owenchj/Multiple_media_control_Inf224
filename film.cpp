#include"video.cpp"
class film : public video{
private:
  unsigned int nbrchap;
  int *tab; 
public:
  film(){}
  film (string objnom, long date, string filenom, int duree, unsigned int nbrchap=0, int *tab=NULL) : video(objnom, date, filenom, duree), nbrchap(nbrchap), tab(tab){

  }
  ~film(){delete []tab;}

  virtual void modifier(unsigned int nbrchap, int *tab){ 
    this->tab = tab;
    this->nbrchap=nbrchap;
  }
  virtual unsigned int getnbrchap() const {return nbrchap;}
  virtual int * gettab() const { return tab; }
  virtual void afficher() {
    video::afficher();
    cout<<"Le nombre du chapitre "<<"est "<<nbrchap<<endl;
    for(unsigned int k=0; k<nbrchap; k++)
      cout<<"La duree du chapitre "<<k<<" est "<<tab[k]<<endl;
  }

  virtual string getfilename() const{ return video::getfilename(); }

  virtual void play(string filenom) const{ 
    string s1="mplayer ";
    string s2=" &";
    string str=s1+filenom+s2;
    system(str.c_str());
  }

};
