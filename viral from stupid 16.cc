#include "ecolab.h"
using namespace ecolab;
#define MAP vmap
#include "graphcode.h"
#include "graphcode.cd"
using namespace GRAPHCODE_NS;
#include "ref.h"
#include "stupid16.h"
#include "stupid16.cd"
#include "pack_graph.h"
#include "ecolab_epilogue.h"

#include <sstream>
#include <iomanip>

//viralModel viralModel;
//make_model(viralModel);  //macro command

/* use phageArch to set initial state of created phages */
//Phage phageArch;
//make_model(phageArch);

/* use BacteriaArch to set initial state of created Bacterias */
//Bacteria BacteriaArch;
//ace smake_model(BacteriaArch);

inline Cell* getCell(GraphID_t id) 
{
  assert(id==(*getCell(viralModel.objects[id]))[0].ID);
  return getCell(viralModel.objects[id]);
}

inline int ran(int n) {return n*viralModel.u.rand();}

int Phage::x() {return getCell(cellID)->x;}
int Phage::y() {return getCell(cellID)->y;}

int Bacteria::x() {return getCell(cellID)->x;}
int Bacteria::y() {return getCell(cellID)->y;}

inline void Phage::move()
{
  int newX, newY, nbr_idx;
  objref* newCellref=NULL;
  Cell* newCell=getCell(cellID), *myCell=newCell;
  double best_food=myCell->food_avail;

  // shuffle neighbourhood list, leaving the first element point to phage's
  // current cell
  //  random_shuffle(myCell->begin()+1,myCell->end());
  // the above did not work, because Ptrlist::iterator doesn't contain 
  // iterator_category (and other similar properties)
  //copy objref pointers into a temporary vector, then shuffle
  vector <objref*> neighbourlist(myCell->size());
  int i=0;
  for (Ptrlist::iterator nbr=myCell->phageNbrhd.begin(); nbr!=myCell->phageNbrhd.end(); nbr++)   //shorthand for pointerlist, number, phageheighborhood.
    neighbourlist[i++]=&*nbr;
  random_shuffle(neighbourlist.begin()+1,neighbourlist.end(),ran);

  // find an unoccupied cell in the neighbourhood
  for ( vector <objref*>::iterator nbr=neighbourlist.begin(); 
	nbr!=neighbourlist.end(); nbr++)
    {
      Cell* nCell=getCell(**nbr);
      if (!nCell->occupied() && nCell->food_avail>best_food)
	{
	  newCell=nCell;
	  newCellref=*nbr;
	  best_food=newCell->food_avail;
	}
    }
  if (newCell==myCell)  //no better unoccupied neighbours
    return;  
  // swap myself to new cell
  newCell->movephage(*myCell);
  cellID=newCellref->ID;
}

void Phage::die() 
{getCell(cellID)->phage.clear();}

/* return true if phage dies */
inline bool Phage::mortality()
{
  Cell &myCell=*getCell(cellID);
  if (size>repro_size)
    {
      for (int i=0; i<5; i++) // generate 5 new phages
	for (int j=0; j<5; j++) // 5 goes at placement
	  {
	    objref& birth_ref=myCell.phageNbrhd[viralModel.u.rand()*myCell.size()];
	    Cell& birth_loc=*getCell(birth_ref);
	    if (!birth_loc.occupied())
	      {
		birth_loc.addphage(phageArch);
		viralModel.phages.push_back(birth_loc.phage.back());
		break;
	      }
	  }
      return true;
    }

  if (viralModel.u.rand()>survivalProbability) return true;
  else return false;
}
  
void Space::setup(int nx_, int ny_, int moveDistance, bool toroidal_ ,
		  double max_food_production)
{
  nx=nx_, ny=ny_;
  assert(moveDistance <= nx/2 && moveDistance <= ny/2 );
  toroidal=toroidal_;
  
  for (int i=0; i<nx; i++)
    for (int j=0; j<ny; j++)
      {
	objref& o=objects[mapid(i,j)];
	AddObject(Cell(),o.ID);
	*getCell(o)=Cell(i,j,max_food_production);
      }
  for (int i=0; i<nx; i++)
    for (int j=0; j<ny; j++)
      {
	objref& o=objects[mapid(i,j)];
	/* connect up a square neighbourhood of size 2*moveDistance+1 */
	o->push_back(o); //self is first reference on neigbourhood list
	for (int ii=-moveDistance; ii<=moveDistance; ii++)
	  for (int jj=-moveDistance; jj<=moveDistance; jj++)
	    if (ii!=0 || jj!=0)
	      o->push_back(objects[mapid(i+ii,j+jj)]);
      }
  //Set up phage and Bacteria neighbourhood lists
  for (int i=0; i<nx; i++)
    for (int j=0; j<ny; j++)
      {
	objref& o=objects[mapid(i,j)];
	Cell& cell=*getCell(o);
	cell.phageNbrhd=cell;
	// wire up Bacteria neighbourhood - use Moore neighborhood, even though specification 
	// is ambiguous
	for (int ii=-1; ii<=1; ii++)
	  for (int jj=-1; jj<=1; jj++)
	    cell.BacteriaNbrhd.push_back(objects[mapid(i+ii,j+jj)]);
	assert(o.ID==mapid(cell.x,cell.y));
      }
  rebuild_local_list();
}

GraphID_t Space::mapid(int x, int y)
{
  assert(x>=-nx && y>=-ny);
  if (toroidal)    
    {
      /* place x and y into [0..nx,ny) */
      if (x<0 || x>=nx) 
	x=(x+nx)%nx;
      if (y<0 || y>=ny)  //setting up toroidal coordinate.
	y=(y+ny)%ny;
    }
  else
    if (x<0 || x>=nx || y<0 || y>=ny)
      return bad_ID;
  return x+nx*y;
}
    
void viralModel::addphages(TCL_args args)
{
  int  nphages=args;
  Cell *cell;
  for (int i=0; i<nphages; i++)
    {
      do
	{
	  cell=randomCell();
	} while (cell->occupied());
      cell->addphage(phageArch);
      /* initialise phage to a random size accrdoing to initphageDist */
      double sz=initphageDist->rand();
      cell->phage[0]->size=(sz>0)? sz: 0;
      phages.push_back(cell->phage[0]);
    }
}

void viralModel::addBacterias(TCL_args args)
{
  int  nBacterias=args;
  Cell *cell;
  for (int i=0; i<nBacterias; i++)
    {
      do
	{
	  cell=randomCell();
	} while (cell->Bacteria.size()>0);
      cell->addBacteria(BacteriaArch);
      Bacterias.push_back(cell->Bacteria[0]);
    }
}

struct phageMore         //overloading boolean comparison operator for use by next funciton
{
  bool operator()(const classdesc::ref<Phage>& x, const classdesc::ref<Phage>& y) 
  {
    return x->size > y->size;
  }
};

void viralModel::movephages()
{
  sort(phages.begin(),phages.end(),phageMore());    //sort phages by size. begin & end: return first and last elements in an array. what's the point???
  for (size_t i=0; i<phages.size(); i++)
    phages[i]->move();
  tstep++;
}

/*void viralModel::birthdeath()
{
  vector<int> deathlist;
  for (size_t i=0; i<phages.size(); i++)
    if (phages[i]->mortality())
      deathlist.push_back(i);
  for (int i=deathlist.size()-1; i>=0; i--)
    {
      phages[deathlist[i]]->die();
      phages.erase(phages.begin()+deathlist[i]);      //die and mortality???
    }
}*/

/*void Phage::grow()
{
  Cell *cell=getCell(cellID);
  double incr=std::min(max_consumption,cell->food_avail); 
  size+=incr;
  cell->food_avail-=incr;
}*/

inline char hexdigit(int i)
{ assert(i<16); return i<10? i+'0': i+'a'-10;}          //???

void Phage::draw(const eco_string& canvas)
{
  tclcmd c;
  char h[3];
  int v = size<10? 255-int(size*25.6): 0;
  h[0]=hexdigit(v/16);
  h[1]=hexdigit(v%16);
  h[2]='\0';
  int scale=viralModel.scale;
  c << canvas << "create rectangle" << (scale*x()) << (scale*y()) << 
    (scale*(x()+1)) << (scale*(y()+1));
  c |" -fill #ff"|h|h;
  c << "-tags phages\n";
}

void Bacteria::move(Cell& to, Cell& from)
{
  to.Bacteria.push_back(from.Bacteria.back());
  from.Bacteria.clear();
  assert(to[0].ID==viralModel.mapid(to.x,to.y));
  cellID=to[0].ID;
}


/*void Bacteria::hunt()
{
  Cell* myCell=getCell(cellID);
  //shuffle neighbourhood list (we must copy again, as per note in Phage::move()
  vector <objref*> neighbourlist(myCell->BacteriaNbrhd.size());
  int i=0;
  for (Ptrlist::iterator nbr=myCell->BacteriaNbrhd.begin(); nbr!=myCell->BacteriaNbrhd.end(); nbr++)
    neighbourlist[i++]=&*nbr;
  random_shuffle(neighbourlist.begin(),neighbourlist.end(),ran);

  vector<objref*>::iterator nbr;
  for (nbr=neighbourlist.begin(); nbr!=neighbourlist.end() && getCell(**nbr)->phage.size()==0; nbr++);
  if (nbr!=neighbourlist.end())
    {
      Cell* newCell=getCell(**nbr);
      viralModel.killphage(newCell->phage[0]);
      if (newCell->Bacteria.size()==0) // move only if destination is empty
	move(*newCell,*myCell);
   }
  else // move to first unoccupied location in shuffled list (or remain still)
    {
      for (nbr=neighbourlist.begin(); 
	   (*nbr)->ID!=cellID && getCell(**nbr)->Bacteria.size()>0; nbr++);
      if ((*nbr)->ID!=cellID)
	move(*getCell(**nbr),*myCell);
    }
}*/
      
void Bacteria::draw(const eco_string& canvas)
{
  tclcmd c;
  int scale=viralModel.scale;
  c << canvas << "create rectangle" << (scale*x()) << (scale*y()) << 
    (scale*(x()+1)) << (scale*(y()+1)) << " -fill #0000ff -tags Bacterias\n";
}
  
void Cell::draw(const eco_string& canvas)
{
  assert((*this)[0].ID==viralModel.mapid(x,y));
  tclcmd c;
  char h[3];
  int v = food_avail<0.5? int(food_avail*512.0): 255;
  h[0]=hexdigit(v/16);
  h[1]=hexdigit(v%16);
  h[2]='\0';
  int scale=viralModel.scale;
  c << canvas << "create rectangle" << (scale*x) << (scale*y) << 
    (scale*(x+1)) << (scale*(y+1));
  c |" -fill #00"|h|"00";
  c << "-tags cells\n";
}

void viralModel::drawphages(TCL_args args)
{
  eco_string canvas=args;
  tclcmd c;
  c << canvas << "delete phages\n";
  for (size_t i=0; i<phages.size(); i++)
    phages[i]->draw(canvas);
}

void viralModel::drawBacterias(TCL_args args)
{
  eco_string canvas=args;
  tclcmd c;
  c << canvas << "delete Bacterias\n";
  for (size_t i=0; i<Bacterias.size(); i++)
    Bacterias[i]->draw(canvas);
}

void viralModel::drawCells(TCL_args args)
{
  eco_string canvas=args;
  tclcmd c;
  c << canvas << "delete cells\n";
  for (omap::iterator i=objects.begin(); i!=objects.end(); i++)
    {
      Cell& cell=*getCell(*i);
      if (cell.Bacteria.size())
	cell.Bacteria[0]->draw(canvas);
      else if (cell.phage.size())
	cell.phage[0]->draw(canvas);
      else
	cell.draw(canvas);
    }
}

/*void viralModel::grow()
{
  for (Ptrlist::iterator i=begin(); i!=end(); i++)
    {
      Cell *cell=getCell(*i);
      cell->grow_food();
      if (cell->phage.size()>0)
	cell->phage[0]->grow();
    }
}*/

/** return a TCL object representing a phage 
    (if one exists at that location, and phage passed as third parameter) */

eco_string viralModel::probe(TCL_args args)
{
  int x=args, y=args;
  x/=scale; y/=scale; //reduce to application coordinates
  bool phage = strcmp(args,"phage")==0;
  eco_strstream id;
  static int cnt=0;
  Cell& cell=*getCell(*getObjAt(x,y));
  if (phage && cell.occupied())
    {
      id | "phage" | cnt++;
      TCL_obj(null_TCL_obj,id.str(),*cell.phage[0]);
    }
  else
    {
      id | "cell" | cnt++;
      TCL_obj(null_TCL_obj,id.str(),cell);
    }
  return id.str();
}

struct Prod_store
{
  int x,y;
  double p;
  Prod_store(int x,int y,double p): x(x), y(y), p(p) {}
};

/*void viralModel::read_food_production(TCL_args args)
{
  char* filename=args;
  int moveDistance=args;

  FILE *food_input=fopen(filename,"r");
  //discard first 3 lines
  for (int i=0; i<3; i++)
    for (int c=fgetc(food_input); c!='\n' && c!=EOF; c=fgetc(food_input));

  int x, y, nx=0, ny=0;
  double prod;

  vector<Prod_store> prod_store;

  while (fscanf(food_input,"%d %d %lg",&x,&y,&prod)==3)
    {
      nx=std::max(nx,x+1); ny=std::max(ny,y+1);
      prod_store.push_back(Prod_store(x,y,prod));
    }

  fclose(food_input);

  Space::setup(nx,ny,moveDistance,false,0.1);
  for (vector<Prod_store>::iterator i=prod_store.begin(); i!=prod_store.end(); i++)
    getCell(*getObjAt(i->x,i->y))->food_production=i->p;
}*/


void viralModel::killphage(classdesc::ref<Phage>& phage)
{
  phages.erase(find(phages.begin(),phages.end(),phage));
  phage->die();
}

/*void viralModel::hunt()
{
  for (size_t i=0; i<Bacterias.size(); i++)
    Bacterias[i]->hunt();
}*/
