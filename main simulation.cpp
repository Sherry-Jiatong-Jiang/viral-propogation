#include "viral from stupid16.h"
//#include <cstdlib>
#include <array>
#include <vector>

using namespace std;

int main() {

	//system parameters
	int nx, ny;  //dimensions of space
	urand u;     //random generator for positions
	double dt;   //time per simulation step
	double dx;	//unit deme length
	int tao;	//lysis time / tstep
	int Np, N, X;//max phages, max bacteria, and max demes
	int N0;		//initial phage numbers in the 1st deme
	
	//phage probs parameters
	double qd;
	double qiI;
	double qiB;
	double pmigra;

	int i, j; //to be used in the for loops
	
	//Initialization of demes and agents

	vector <vector <Bacterium*>* > demesB;
	vector <vector <Phage*>* > demesP;
	

	//demesB and demesP are two vectors storing pointers which point to
	//a group of vectors which represent demes of bacteria and phages respectively.
	//A vector of a deme of phages, e.g., contains pointers of phage objects.
	for (i = 0; i <= X; i++)
	{
		demesB.push_back(new vector<Bacterium*>);
		for (j = 0; j <= N; j++)
		{
			(*demesB[i]).push_back(new Bacterium);
			(*demesB[i])[j]->infected = 0;
			(*demesB[i])[j]->label = false;
			(*demesB[i])[j]->lysed = false;
			(*demesB[i])[j]->t_before_lysis = tao;
		}
	}

	for (i = 0; i <= X; i++)
	{
		demesP.push_back(new vector<Phage*>);
		for (j = 0; j <= N0; j++)
		{
			(*demesP[i]).push_back(new Phage);
			(*demesP[i])[j]->label = 1;
			(*demesP[i])[j]->pmigra = pmigra;
			(*demesP[i])[j]->qd = qd;
			(*demesP[i])[j]->qiB = qiB;
			(*demesP[i])[j]->qiI = qiI;
		}
	}


	
	


}