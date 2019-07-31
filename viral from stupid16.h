#include <array>

class Phage
{
  
public:
  int x(); 
  int y(); 

  int label;

  double qd;
  double qiI;
  double qiB;
  double pmigra;
  
  Phage(): label(1), qd(0.1), qiI(0.2), qiB(0.2), pmigra(0.3) {}
  
  void move();
  void inject_i();
  void inject_u(); 
  void die();
  
};


class Bacterium
{
  
public:
  int x(); 
  int y(); 

  int burst_size;
  int label;
  int ts_after_infection;
  bool infected;
  bool lysed;
  Bacterium(): label(0), infected(false), lysed(false), ts_after_infection(10), burst_size(500) {}
};


class ViralModel
{
public:

//int nx, ny;  //dimensions of space

  //urand u;     //random generator for positions ????????????
  int tstep;   //timestep - updated each time movephages is called
 
  void addphages();
  void removeBacteria();
  void movephages();
  void drawphages();
  void drawBacteria();
  void drawCells();
  void killphage();
  void infect();
  void lyse();
  void moveframe();
};
