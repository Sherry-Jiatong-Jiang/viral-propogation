#include "viral from stupid16.h"
#include <iostream>
#include <cmath>	//for rounding
#include <cstdlib>	//for random generators
#include <array>
#include <vector>
#include <time.h>	//for time(NULL) in random seed 

using namespace std;

int main() 
{

	//system parameters
	int nx, ny;  //dimensions of space
	double dt;   //time per simulation step
	double dx;	//unit deme length
	int tao = 0;	//(lysis time / tstep)
	int Np = 0, N = 0, X = 0;//max phages, max bacteria, and max demes
	int N0 = 0;		//initial phage numbers in the 1st deme
	int simulation_steps = 0;	//total simulation steps (total time/dt)
	
	//phage probs parameters (per timestep)
	double qd = 0;	//death probs
	double qiI = 0;	//infecting infected bacteria probs
	double qiB = 0;	//infecting uninfected bacteria probs
	double pmigra = 0;	//migration probability (to both sides)

	int burst_size = 0;

	int total_phage_index = 0, total_phage_size = 0, bacterium_index = 0, phage_index = 0, left_phage_index = 0, right_phage_index = 0;
	int death_number = 0, infect_B_number = 0, infect_I_number = 0, migration_number = 0;
	Phage* temp;

	vector <vector <Bacterium*>* > demesB;
	vector <vector <Phage*>* > demesP;
	vector <vector <Bacterium*>* > infectionTime;

	/*Initialization of demes and agents*/
	
	/*demesB and demesP are two vectors storing pointers which point to
	a group of vectors which represent demes of bacteria and phages respectively.
	A vector of a deme of phages, e.g., contains pointers of phage objects.*/

	int i, j, k, w, a=0, b=0; //to be used in the for loops

	for (i = 0; i <= X; i++)
	{
		demesB.push_back(new vector<Bacterium*>);	//X demes of bacteria in total
		for (j = 0; j <= N; j++)
		{
			(*demesB[i]).push_back(new Bacterium);
			(*demesB[i])[j]->infected = 0;
			(*demesB[i])[j]->label = false;
			(*demesB[i])[j]->lysed = false;
			(*demesB[i])[j]->ts_after_infection = 0;	//N bacteria per deme initially
		}
	}

	for (i = 0; i <= X; i++)
	{
		demesP.push_back(new vector<Phage*>);	//X demes of phages in total
		for (j = 0; j <= N0; j++)
		{
			if (i == 0)
			{
				(*demesP[i]).push_back(new Phage);	//N0 phages in the 1st deme, 0 otherwise, initially.
				(*demesP[i])[j]->label = 1;
				(*demesP[i])[j]->pmigra = pmigra;
				(*demesP[i])[j]->qd = qd;
				(*demesP[i])[j]->qiB = qiB;
				(*demesP[i])[j]->qiI = qiI;
			}
		}
	}

	/*Simulation steps*/

	//i: simulation timestep
	for (i = 0; i <= simulation_steps; i++)
	{	
		for (j = 0; j <= X; j++)
		{
			total_phage_size += (*demesP[j]).size();
		}

		/*die*/
		death_number = std::round(qd * total_phage_size);
		for (k = 0; k <= death_number; k++)
		{
			//randomly pick one phage
			srand(time(NULL));
			total_phage_index = rand() % total_phage_size;
			//work out vector index of phage out of total_phage_index: (*demesP[j])[b]
			for (j = 0; j <= X; j++) 
			{a = total_phage_index - (*demesP[j]).size();
			if (a < 0) 
			{ 
				b = (*demesP[j]).size() + a;
				break; 
			}
			}
			delete (*demesP[i])[j];
			(*demesP[i]).erase((*demesP[i]).begin() + j);
		}

		/*infect uninfected bacteria*/

		infect_B_number = std::round(qiB * total_phage_size);
		for (k = 0; k <= infect_B_number; k++)
		{
			//randomly pick one phage
			srand(time(NULL));
			total_phage_index = rand() % total_phage_size;
			//work out vector index of phage out of total_phage_index: (*demesP[j])[b]
			for (j = 0; j <= X; j++)
			{
				a = total_phage_index - (*demesP[j]).size();
				if (a < 0)
				{
					b = (*demesP[j]).size() + a;
					break;
				}
			}

			//randomly pick one bacterium from the same deme
			srand(time(NULL));
			bacterium_index = rand() % (*demesB[j]).size();
			(*((*demesB[j])[bacterium_index])).label = (*((*demesP[j])[b])).label;
			(*((*demesB[i])[bacterium_index])).infected = true;

			//update infectionTime pointer vector
			(*infectionTime[0]).push_back((*demesB[j])[bacterium_index]);

			//delete phage
			delete (*demesP[j])[b];
			(*demesP[j]).erase((*demesP[j]).begin() + b);
		}

		/*infect infected bacteria???????????????????????*/

		/*migration*/

		migration_number = std::round(pmigra / 2 * total_phage_size);
		for (k = 0; k <= migration_number; k++)
		{
			//randomly pick one phage
			srand(time(NULL));
			total_phage_index = rand() % total_phage_size;
			//work out vector index of phage out of total_phage_index: (*demesP[j])[b]
			for (j = 0; j <= X; j++)
			{
				a = total_phage_index - (*demesP[j]).size();
				if (a < 0)
				{
					b = (*demesP[j]).size() + a;
					break;
				}
			}
			//randomly pick another phage from the same deme, two more from neighbouring demes (deal with repeat????????)
			srand(time(NULL));
			phage_index = rand() % (*demesP[j]).size();

			//deal with 1st and last deme???????????????????????
			if (j > 0)
			{
				srand(time(NULL));
				left_phage_index = rand() % (*demesP[j - 1]).size();
			}
			if (j < X)
			{
				srand(time(NULL));
				right_phage_index = rand() % (*demesP[j + 1]).size();
			}

			//swap phages deal with holes??????????????????
			temp = (*demesP[j])[b];
			(*demesP[j])[b] = (*demesP[j - 1])[left_phage_index];
			(*demesP[j - 1])[left_phage_index] = temp;

			temp = (*demesP[j])[phage_index];
			(*demesP[j])[phage_index] = (*demesP[j + 1])[right_phage_index];
			(*demesP[j + 1])[right_phage_index] = temp;
			
		}

		//check bacteria state and begin lysis

		//update bacteria infectionTime vector
		infectionTime = infectionTime.insert(infectionTime.begin(), (*demesB[j])[k]);


		for (j = 0; j <= X; j++)
		{
			for (k = 0; k < (*demesB[j]).size(); k++)
			{
				if ((*((*demesB[j])[k])).infected == true && (*((*demesB[j])[k])).ts_after_infection == tao)
					{
					for (w = 0; w < burst_size; w++)
					{
						(*demesP[j]).push_back(new Phage);
						(*demesP[j])[(*demesP[j]).size() - 1]->label = (*((*demesB[j])[k])).label;
						(*demesP[j])[(*demesP[j]).size() - 1]->pmigra = pmigra;
						(*demesP[j])[(*demesP[j]).size() - 1]->qd = qd;
						(*demesP[j])[(*demesP[j]).size() - 1]->qiB = qiB;
						(*demesP[j])[(*demesP[j]).size() - 1]->qiI = qiI;
					}
				}
			}
		}

	}
	


}