#include <vector>
using std::vector;
#include <iostream>
using std::ostream;

class Phage
{
  
public:

  int label;

  double qd;
  double qiI;
  double qiB;
  double pmigra;
  
  Phage(): label(1), qd(0.1), qiI(0.2), qiB(0.2), pmigra(0.3) {}
  
  /*void move();
  void inject_i();
  void inject_u(); 
  void die();*/
  
};


class Bacterium
{
  
public:
  int x(); 
  int y(); 

  int demeIndex;
  int indexInDeme;
  int burst_size;
  int label;
  int ts_after_infection;
  bool infected;
  bool lysed;
  Bacterium() : label(0), infected(false), lysed(false), ts_after_infection(0), burst_size(500), demeIndex(0), indexInDeme(0) {}
};


/*class ViralModel
{
public:


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
*/

//overloading cout operator from https://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector.
template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
	out << "{";
	size_t last = v.size() - 1;
	for (size_t i = 0; i < v.size(); ++i) {
		out << v[i];
		if (i != last)
			out << ", ";
	}
	out << "}";
	return out;
}