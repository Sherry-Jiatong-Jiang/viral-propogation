#include "viral from stupid16.h"
#include <iostream>
#include <cmath>	//for rounding
#include <cstdlib>	//for random generators
#include <array>
#include <vector>
#include <ctime>	//for time(NULL) in random seed 

using namespace std;

int main()
{
	//system parameters
	double dt = 100;   //time (sec) per simulation step
	double dx = 0.1;	//unit deme length (mm)
	int tao = 50;	//(lysis time / tstep)
	int burst_size = 50;
	int X = 100, N = 100, Np = N * burst_size;//max demes, max bacteria, and max phages max phages where applicable????????????????
	int N0 = 10;		//initial phage numbers in the 1st deme
	int simulation_steps = 10;	//total simulation steps (total time/dt)
	int visualization_steps = 1;	//how many steps before each output on the screen

	bool swap = false;	//if swap is true, use swapping scheme (swapping phages and holes); if false, use random move scheme for phages. 
						//For both schemes, randomly choose right or left move, use poisson distribution for total number of phages to be randomly selected. 

	//phage probs parameters (per timestep)
	double qd = 0.01;	//death probs
	double qiI = 0.2;	//infecting infected bacteria probs
	double qiB = 0.2;	//infecting uninfected bacteria probs
	double pmigra = 0.05;	//migration probability (to both sides)

	vector <int> output_population(X);	//temporary outputof phage population distribution
	//vector <int> output_labels;	//temporary outputof phage genetic label distribution
	//double heterozygosity;	//to characterise genetic diversity at the wave front

	//intermediate parameters
	int total_phage_index = 0, total_phage_size = 0, bacterium_index = 0, phage_index = 0, left_phage_index = 0, right_phage_index = 0;
	int death_number = 0, infect_B_number = 0, infect_I_number = 0, migration_number = 0;

	int direction = 0;

	Phage* temp;

	vector <vector <Bacterium*>* > demesB(X);
	vector <vector <Phage*>* > demesP(X);
	vector <vector <Bacterium*>* > infectionTime(tao);



	/*Initialization of demes and agents*/

	/*demesB and demesP are two vectors of initial size X storing pointers which point to
	a group of vectors which represent demes of bacteria and phages respectively.
	A vector of a deme of phages, e.g., contains pointers of phage objects.*/

	int i, j, k, a = 0, b = 0, c = 0; //to be used in the for loops

	for (i = 0; i < X; i++)
	{
		demesB[i] = new vector<Bacterium*>;	//X demes of bacteria in total
		for (j = 0; j < N; j++)
		{
			(*demesB[i]).push_back(new Bacterium);	//N bacteria per deme initially
			(*demesB[i])[j]->infected = false;
			(*demesB[i])[j]->demeIndex = i;
			(*demesB[i])[j]->indexInDeme = j;
			(*demesB[i])[j]->label = 0;
			(*demesB[i])[j]->lysed = false;
			(*demesB[i])[j]->ts_after_infection = 0;
			(*demesB[i])[j]->burst_size = burst_size;
		}
	}

	for (i = 0; i < X; i++)
	{
		demesP[i] = new vector<Phage*>;	//X demes of phages in total
		if (i == 0)
		{
			for (j = 0; j < round(N0 / 2); j++)	//N0 phages in the 1st deme, 0 otherwise, initially. labels to be initialized as below
			{
				(*demesP[i]).push_back(new Phage);
				(*demesP[i])[j]->label = 1;
				(*demesP[i])[j]->pmigra = pmigra;
				(*demesP[i])[j]->qd = qd;
				(*demesP[i])[j]->qiB = qiB;
				(*demesP[i])[j]->qiI = qiI;
			}
			for (j = round(N0 / 2); j < N0; j++)
			{
				(*demesP[i]).push_back(new Phage);
				(*demesP[i])[j]->label = 2;
				(*demesP[i])[j]->pmigra = pmigra;
				(*demesP[i])[j]->qd = qd;
				(*demesP[i])[j]->qiB = qiB;
				(*demesP[i])[j]->qiI = qiI;
			}
		}
	}

	//initializing infectionTime vector
	for (i = 0; i < tao; i++)
	{
		infectionTime[i] = new vector <Bacterium*>;
	}


	//step 0 output showing initial distribuiton
	for (j = 0; j < X; j++)
	{
		output_population[j] = (*demesP[j]).size();
	}

	cout << "Current simulation step: " << 0 << endl;
	cout << "Phage population within each deme: " << output_population << endl;
	//cout << "phage 3 label:" << (*((*demesP[0])[3])).label;
	//cout << "Gene label with the largest frequency within each deme: " << output_labels << endl;
	//cout << "Heterozygosity within current frame: " << heterozygosity << endl;
	//cin >> a;



	/*Simulation steps*/

	//i: simulation timestep
	for (i = 0; i < simulation_steps; i++)
	{
		total_phage_size = 0;
		for (j = 0; j < X; j++)
		{
			total_phage_size += (*demesP[j]).size();
		}



		//create new column in infectionTime vector
		infectionTime.insert(infectionTime.begin(), new vector<Bacterium*>);

		//create new phages, and delete lysed bacteria from object storage & from infectionTime & from demesB! 
		//(not the other way round which causes memory leak!)
		if ((*infectionTime.back()).empty() == false)
		{
			int s = (*(infectionTime.back())).size();
			for (j = 0; j < s; j++)
			{
				//create a reference to the last column of infectionTime, temp
				vector<Bacterium*>& temp = *infectionTime.back();
				int label = temp[j]->label;
				int h = temp[j]->demeIndex;
				int v = temp[j]->indexInDeme;

				//create new phages
				(*demesP[h]).push_back(new Phage[burst_size]);	//is this doable????????????????????????????
				(*demesP[h])[j]->label = label;
				(*demesP[h])[j]->pmigra = pmigra;
				(*demesP[h])[j]->qd = qd;
				(*demesP[h])[j]->qiB = qiB;
				(*demesP[h])[j]->qiI = qiI;

				//delete lysed bacteria from object storage& from infectionTime& from demesB
				delete (*demesB[h])[v];
				(*demesB[h]).erase((*demesB[h]).begin() + v);
				(*infectionTime.back()).erase((*infectionTime.back()).begin() + s - 1);
			}
		}
		//delete last column in infectionTime vector
		infectionTime.erase(infectionTime.begin() + infectionTime.size() - 1);



		/*die*/

		try
		{
			death_number = round(qd * total_phage_size);
			for (k = 0; k < death_number; k++)	//any way to make this faster??????????????????
			{
				//randomly pick one phage
				srand(time(NULL));
				total_phage_index = rand() % total_phage_size + 1;
				a = total_phage_index;
				//work out vector index of phage out of total_phage_index: (*demesP[j])[b]
				for (j = 0; j < X; j++)
				{
					a = a - (*demesP[j]).size();
					if (a <= 0)
					{
						b = (*demesP[j]).size() + a;
						b = b - 1;
						break;
					}
				}
				delete (*demesP[j])[b];
				//if (b < (*demesP[j]).size())
				{(*demesP[j]).erase((*demesP[j]).begin() + b); }
				total_phage_size = total_phage_size - 1;
			}


		}
		catch (exception& e)
		{
			cout << "Standard exception: " << e.what() << endl;
		}


		/*infect uninfected and infected bacteria*/

		infect_B_number = round(qiB * total_phage_size);
		for (k = 0; k < infect_B_number; k++)
		{
			//randomly pick one phage
			srand(time(NULL));
			total_phage_index = rand() % total_phage_size;
			a = total_phage_index;
			//work out vector index of phage out of total_phage_index: (*demesP[j])[b]
			for (j = 0; j < X; j++)
			{
				a = a - (*demesP[j]).size();
				if (a <= 0)
				{
					b = (*demesP[j]).size() + a;
					b = b - 1;
					break;
				}
			}

			//randomly pick one bacterium from the same deme
			srand(time(NULL));
			bacterium_index = rand() % (*demesB[j]).size();

			//if infecting uninfected bacteria:
			if ((*((*demesB[j])[bacterium_index])).infected == false)
			{
				(*((*demesB[j])[bacterium_index])).label = (*((*demesP[j])[b])).label;
				(*((*demesB[j])[bacterium_index])).infected = true;

				//update infectionTime with newly infected bacteria
				(*infectionTime[0]).push_back((*demesB[j])[bacterium_index]);
			}

			//delete phage after infection
			delete (*demesP[j])[b];
			(*demesP[j]).erase((*demesP[j]).begin() + b);
		}


		/*migration*/

		if (swap == true)
		{
			migration_number = round(pmigra / 2 * total_phage_size);
			for (k = 0; k < migration_number; k++)
			{
				//randomly pick one phage
				srand(time(NULL));
				total_phage_index = rand() % total_phage_size + 1;
				a = total_phage_index;
				//work out vector index of phage out of total_phage_index: (*demesP[j])[b] other ways to improve speed????????????????????
				for (j = 0; j < X; j++)
				{
					a = a - (*demesP[j]).size();
					if (a <= 0)
					{
						b = (*demesP[j]).size() + a;
						b = b - 1;
						break;
					}
				}


				//randomly pick another phage from the same deme, two more from neighbouring demes (deal with repeat????????)
				srand(time(NULL));
				phage_index = rand() % (*demesP[j]).size();

				//deal with holes ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?

				//swap phages
				if (j > 0)	//if not the first deme:
				{
					srand(time(NULL));
					left_phage_index = rand() % ((*demesP[j - 1]).size());

					temp = (*demesP[j])[b];
					(*demesP[j])[b] = (*demesP[j - 1])[left_phage_index];
					(*demesP[j - 1])[left_phage_index] = temp;
				}

				if (j < X - 1)	//if not the last deme:
				{
					srand(time(NULL));
					right_phage_index = rand() % ((*demesP[j + 1]).size());

					temp = (*demesP[j])[phage_index];
					(*demesP[j])[phage_index] = (*demesP[j + 1])[right_phage_index];
					(*demesP[j + 1])[right_phage_index] = temp;
				}


			}
		}

		else
		{
			migration_number = round(pmigra * total_phage_size);
			for (k = 0; k < migration_number; k++)
			{
				//randomly pick one phage
				srand(time(NULL));
				total_phage_index = rand() % total_phage_size + 1;
				a = total_phage_index;
				//work out vector index of phage out of total_phage_index: (*demesP[j])[b] other ways to improve speed????????????????????
				for (j = 0; j < X; j++)
				{
					a = a - (*demesP[j]).size();
					if (a <= 0)
					{
						b = (*demesP[j]).size() + a;
						b = b - 1;
						break;
					}
				}
				//if in the first deme, only move to the right
				if (j == 0)
				{
					(*demesP[j + 1]).push_back((*demesP[j])[b]);
					(*demesP[j]).erase((*demesP[j]).begin() + b);
				}
				//if in the last deme, create new deme
				else if (j == X - 1)
				{
					demesP.push_back(new vector<Phage*>);

					//randomly choose to move to the left or the right (0: left; 1: right)
					srand(time(NULL));
					direction = rand() % 2;
					if (direction == 0)
					{
						(*demesP[j - 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);
					}
					else
					{
						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);
					}
					//delete first deme (only at the end in order not to mess up with indexes).
					demesP.erase(demesP.begin());
				}
				else
				{
					//randomly choose to move to the left or the right (0: left; 1: right)
					srand(time(NULL));
					direction = rand() % 2;
					if (direction == 0)
					{
						(*demesP[j - 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);
					}
					else
					{
						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);
					}
				}
			}

		}


		/*old code on bacteria lysis and new phage creation
		for (j = 0; j < X; j++)
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
		}*/

		/*temporary output*/

		if ((i + 1) % visualization_steps == 0)
		{
			for (j = 0; j < demesP.size(); j++)
			{
				output_population[j] = (*demesP[j]).size();
			}
			cout << "Current simulation step: " << i + 1 << endl;
			cout << "Phage population within each deme: " << output_population << endl;
			//cout << "Gene label with the largest frequency within each deme: " << output_labels << endl;
			//cout << "Heterozygosity within current frame: " << heterozygosity << endl;
			cin >> a;
		}

	}



}