#include <arrays.h>

class Phage
{
  //GraphID_t cellID;  // Graphcode ID of cell where this phage is located
  //CLASSDESC_ACCESS(Phage);
  friend class Cell;
public:
  int x(); 
  int y(); 

  int label;

  //double size;
  //double repro_size;
  //double max_consumption;
  //double survivalProbability;

  double qd;
  double qiI;
  double qiB;
  double pmigra;
  
  Phage(): label(1), qd(0.1), qiI(0.2), qiB(0.2), pmigra(0.3) {}
  
  void move();

  void inject_i();
  void inject_u(); 
  
  void die();
  
  //bool mortality();                       //mortality???
  //void draw(const eco_string& canvas);
};

class Cell;

class Bacteria
{
  //GraphID_t cellID;  // Graphcode ID of cell where this phage is located
  //CLASSDESC_ACCESS(Bacteria);
  friend class Cell;
  //void move(Cell& to, Cell& from);
public:
  int x(); 
  int y(); 
  //void hunt();
  //void draw(const eco_string& canvas);

  int label;
  int t_before_lysis;
  bool infected;
  bool lysed;
  Bacteria(): label(0), infected(false), lysed(false), t_before_lysis(tao) {}
};


class Cell: public Object<Cell,GRAPHCODE_NS::object>  //???
{
  //CLASSDESC_ACCESS(Cell);
public:
  unsigned x,y;
  //double food_avail, food_production, max_food;
  vector<classdesc::ref<Phage> > phage;
  Ptrlist phageNbrhd; 
  vector<classdesc::ref<Bacteria> > Bacteria;
  Ptrlist BacteriaNbrhd;
  bool full() {return phage.size()>Np;}
  Cell() {}
  //Cell(unsigned x_, unsigned y_, double mfp=0.01):
    //x(x_), y(y_), food_avail(0), food_production(mfp), max_food(100) {}

  Cell(unsigned x_, unsigned y_):
    x(x_), y(y_), phage=vector<classdesc::ref<Phage> >(), bacteria= vector<classdesc::ref<Bacteria> >  {} //bacteria initialization?????
    
  void addphage(const Phage& b) {
    phage.resize(1); *phage[0]=b;
    phage[0]->cellID=begin()->ID; 
  }
  void removeBacteria(const Bacteria& b) {
    Bacteria.resize(1); *Bacteria[0]=b;
    Bacteria[0]->cellID=begin()->ID; 
  }
  void movephage(Cell& from) { 
    assert(from.size()>0);
    assert(!full());
    if (&from==this) return;
    phage=from.phage; 
    from.phage.clear(); 
  }
  
  //void grow_food() {food_avail+=food_production;}
  //void draw(const eco_string& canvas);
};

/* casting utilities */
inline Cell* getCell(objref& x) {assert(x->size()==0 || x.ID==(*x)[0].ID); return dynamic_cast<Cell*>(&*x);}
inline const Cell* getCell(const objref& x) {return dynamic_cast<const Cell*>(&*x);}

/* casting utilities */
inline Phage* getphage(objref& x)   {return dynamic_cast<Phage*>(&*x);}
inline const Phage* getphage(const objref& x)   {return dynamic_cast<const Phage*>(&*x);}

class Space: public Graph
{
  bool toroidal;
  //CLASSDESC_ACCESS(Space);
 public:
  //int nx, ny;  //dimensions of space
  int nx, nb, np;  //dimensions of space

  int moving_deme;

  urand u;
  //Space(): nx(0), ny(0) {}
  Space(): nx(0), nb(0), np(0) {}
  //void setup(int nx, int ny, int moveDistance, bool toroidal, 
	     //double max_food_production);
  void setup(int nx, int ny, int moveDistance, bool toroidal);
 // GraphID_t mapid(int x, int y);
  objref* getObjAt(int x, int y) {return &objects[mapid(x,y)];}
  Cell* randomCell() {return getCell(*getObjAt(u.rand()*nx,u.rand()*ny));}
};

class ViralModel: public Space, TCL_obj_t
{
  //CLASSDESC_ACCESS(ViralModel);
public:
  urand u;     //random generator for positions
  int tstep;   //timestep - updated each time movephages is called
  //int scale;   //no. pixels used to represent phages
  vector<classdesc::ref<Phage> > phages; 
  vector<classdesc::ref<Bacteria> > Bacterias; 
  random_gen *initphageDist; //Initial distribution of phage sizes
  ViralModel(): initphageDist(&u) {}
  //void setup(TCL_args args) {
  //  int nx=args, ny=args, moveDistance=args;
  //  bool toroidal=args;
  //  double max_food_production=args;
  //  Space::setup(nx,ny,moveDistance,toroidal,max_food_production);

  void setup(TCL_args args) {                              //where???
    int nx=args, nb=args, np=args, moveDistance=args;
    bool toroidal=args;
    Space::setup(nx,nb,np,moveDistance,toroidal);
  }
  // addphages(int nphages);
  void addphages(TCL_args args);
  void removeBacterias(TCL_args args);
  void movephages();
  //void birthdeath();
  void drawphages(TCL_args args);
  void drawBacterias(TCL_args args);
  void drawCells(TCL_args args);
  //void grow();
  void killphage(classdesc::ref<Phage>& phage);
  //void hunt();
  void infect();
  void lyse();
  void moveframe();
  /** return a TCL object representing a phage 
      (if one exists at that location, and phage passed as third paramter) */
  //eco_string probe(TCL_args); 
  ecolab::array<double> phagesizes() {
    ecolab::array<double> r;
    for (size_t i=0; i<phages.size(); i++)
      r <<= phages[i]->size;
    return r;
  }
  double max_phagesize() {
    double r=0;
    for (size_t i=0; i<phages.size(); i++)
      r = std::max(phages[i]->size,r);
    return r;
  }
  //void read_food_production(TCL_args);
};
