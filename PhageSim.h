#include <vector>
using std::vector;
#include <iostream>
using std::ostream;


class Bacterium
{
  
public:

  int label;
  int infectionStep;
  bool infected;
  bool lysed;
  Bacterium() : label(0), infected(false), lysed(false), infectionStep(-1){}
};

