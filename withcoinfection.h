#include <vector>
using namespace std;


class Bacterium
{
  
public:

  int label;
  int infectionStep;
  bool infected;
  bool lysed;
  vector <int> labels;
  vector <int> steps;
  Bacterium() : label(0), infected(false), lysed(false), infectionStep(0), labels({}), steps({}) {}
};

