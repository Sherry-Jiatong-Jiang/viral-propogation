#include "viral from stupid16.h"
#include <iostream>
#include <fstream>
#include <cmath>	//for rounding
//#include <cstdlib>	//for random generators
#include <array>
#include <vector>
//#include <ctime>	//for time(NULL) in random seed 
#include <random>	//for random device and mt19937
#include <string>	//for "cout ambiguous" error
using namespace std;


ofstream outfileP;
//ofstream outfileB;
//ofstream outfileI;
ofstream outfileH;
ofstream outfileL;
string filenameP = "Psim001.dat";
//string filenameB = "Bsim001.dat";
//string filenameI = "Isim001.dat";
string filenameH = "Hsim001.dat";
string filenameL = "Lsim001.dat";

//random seed for sequence of random generators
unsigned int seed = 0;

//system parameters
double dt = 100;   //time (sec) per simulation step
double dx = 0.1;	//unit deme length (mm)
int tao = 5;	//(lysis time / tstep)
int burst_size = 50;	//20-50
const int X = 100;	//max demes, constant to be used to initialize array size later
int N = 1000, Np = N * burst_size;//max bacteria, and max phages max phages where applicable????????????????
int N0 = 10000;		//initial phage numbers in the 1st deme

const int simulation_steps = 1000;	//total simulation steps (total time/dt)
const int visualization_steps = 10;	//how many steps before each output on the screen
int labelling_step = 500;	//how many steps to reach equilibrium before labelling phages
const int labels = X;	// number of initial different gene labels, constant to be used to initialize array size later (should cover all demes in the wave front)

bool swapScheme = false;	//if swap is true, use swapping scheme (swapping phages and holes); if false, use random move scheme for phages. 
//For both schemes, randomly choose right or left move, use poisson distribution for total number of phages to be randomly selected. 

//phage probs parameters (per timestep)
double qd = 0;	//death probs
double qiI = 0.01;	//infecting infected bacteria probs
double qiB = 0.01;	//infecting uninfected bacteria probs
double pmigra = 0.005;	//migration probability (to both sides)

//parameters relating to output
vector <int> P_population(X);	//output of phage population distribution
vector <int> IB_population(X);	//output of total bacteria population distribution
vector <int> B_population(X);	//output of uninfected bacteria population distribution
vector <int> I_population(X);	//output of infected bacteria population distribution
double label_proportion[labels][X] = {};//output of proportional distribution of each label within each deme, and initialize to zeroes ([0] corresponding to label 1 etc)
int tot = 0;	//temporary storage of total phage population at each timestep 
double label_frequency[labels] = {};	//each element corresponds to the total frequency of a label withinin the whole population, to be used in the calculation of heterozygosity.
vector<double> heterozygosity;	//of size (simulation_steps / visualization_steps + 1), array to characterise genetic diversity at the wave front

//intermediate parameters
int total_phage_index = 0, total_phage_size = 0, bacterium_index = 0, phage_index = 0, left_phage_index = 0, right_phage_index = 0;
int death_number = 0, infect_B_number = 0, infect_I_number = 0, migration_number = 0;
int direction = 0;

Phage* temp;

vector <vector <Bacterium*>* > demesB(X);
vector <vector <Phage*>* > demesP(X);
vector <vector <Bacterium*>* > infectionTime(tao);


int main()
{

	//random_device rd;
	mt19937 e{ seed }; // or std::default_random_engine e{rd()};

	/*Initialization of demes and agents*/

	/*demesB and demesP are two vectors of initial size X storing pointers which point to
	a group of vectors which represent demes of bacteria and phages respectively.
	A vector of a deme of phages, e.g., contains pointers of phage objects.*/

	int i, j, k, a = 0, b = 0, c = 0, w = 0; //to be used in the for loops

	for (i = 0; i < X; i++)
	{
		demesB[i] = new vector<Bacterium*>;	//X demes of bacteria in total
		for (j = 0; j < N; j++)
		{
			(*demesB[i]).push_back(new Bacterium);	//N bacteria per deme initially
			(*demesB[i])[j]->infected = false;
			(*demesB[i])[j]->demeIndex = i;
			//(*demesB[i])[j]->indexInDeme = j;
			(*demesB[i])[j]->label = 0;
			(*demesB[i])[j]->lysed = false;
			(*demesB[i])[j]->ts_after_infection = 0;
			(*demesB[i])[j]->burst_size = burst_size;
		}
	}

	for (i = 0; i < X; i++)
	{
		demesP[i] = new vector<Phage*>;	//X demes of phages in total
		
			//for (j = 0; j < round(N0 / 2); j++)	//N0 phages in the 1st deme, 0 otherwise, initially. labels to be initialized as below
			//{
			//	(*demesP[i]).push_back(new Phage);
			//	(*demesP[i])[j]->label = 1;
			//	(*demesP[i])[j]->pmigra = pmigra;
			//	(*demesP[i])[j]->qd = qd;
			//	(*demesP[i])[j]->qiB = qiB;
			//	(*demesP[i])[j]->qiI = qiI;
			//}
			//for (j = round(N0 / 2); j < N0; j++)
			//{
			//	(*demesP[i]).push_back(new Phage);
			//	(*demesP[i])[j]->label = 2;
			//	(*demesP[i])[j]->pmigra = pmigra;
			//	(*demesP[i])[j]->qd = qd;
			//	(*demesP[i])[j]->qiB = qiB;
			//	(*demesP[i])[j]->qiI = qiI;
			//}
			for (j = 0; j < N0; j++)	
			{
				(*demesP[i]).push_back(new Phage);
				(*demesP[i])[j]->label = 0;
				(*demesP[i])[j]->pmigra = pmigra;
				(*demesP[i])[j]->qd = qd;
				(*demesP[i])[j]->qiB = qiB;
				(*demesP[i])[j]->qiI = qiI;
			}

	}

	//initializing infectionTime vector
	for (i = 0; i < tao; i++)
	{
		infectionTime[i] = new vector <Bacterium*>;
	}


	//step 0 output showing initial distribution
	for (j = 0; j < X; j++)
	{
		P_population[j] = (*demesP[j]).size();
		IB_population[j] = (*demesB[j]).size();
		I_population[j] = 0;

		for (k = 0; k < (*demesB[j]).size(); k++)
		{
			if ((*demesB[j])[k]->infected == true)
			{
				I_population[j] += 1;
			}
		}
		
		B_population[j] = IB_population[j] - I_population[j];
		
		for (k = 0; k < (*demesP[j]).size(); k++)
		{
			for (i = 0; i < labels; i++)
			{
				if ((*demesP[j])[k]->label == i + 1)	//+1 because actual label is greater than index.(start from 0 and 1) 
				{
					label_proportion[i][j] += 1;
				}
			}
		}
		
		
	}
	//calculate heterozygosity before dividing labels into proportions!
	tot = 0;
	heterozygosity.push_back(0);
	for (k = 0; k < labels; k++)
	{
		label_frequency[k] = 0;
	}
	for (j = 0; j < X; j++)
	{
		tot += P_population[j];
	}
	for (k = 0; k < labels; k++)
	{
		for (j = 0; j < X; j++)
		{
			label_frequency[k] += label_proportion[k][j];
		}
		label_frequency[k] /= tot;
	}
	for (k = 0; k < labels; k++)
	{
		heterozygosity.back() += label_frequency[k] * (1 - label_frequency[k]);
	}

	//calcalate real label_proportions
	for (j = 0; j < X; j++)
	{
		for (w = 0; w < labels; w++)
		{
			if (P_population[j] != 0)
			{
				label_proportion[w][j] = label_proportion[w][j] / P_population[j];	//why 1.001?????????????????????????????
			}
		}
	}
	cout.precision(2);
	cout << "Current simulation step: " << 0 << endl;
	//cout << "Phage population within each deme: " << P_population << endl;
	//cout << "Uninfected Bacteria population within each deme: " << B_population << endl;
	//cout << "Infected Bacteria population within each deme: " << I_population << endl;
	//for (k = 0; k < labels; k++)	//reduce this section after making code modular??????????????????????????
	//{
	//	cout << "Label " << k + 1 << " proportion within each deme: ";
	//	for (j = 0; j < X; j++)
	//	{
	//		cout << label_proportion[k][j] << ", ";
	//	}
	//	cout << endl;
	//}
	//cout << "Heterozygosity within current frame: " << heterozygosity[0] << endl;



	/*Simulation steps*/

	//i: simulation timestep
	for (i = 0; i < simulation_steps; i++)
	{
		
		/*if at equilibrium, label phages*/
		if (i == labelling_step)
		{
			for (k = 0; k < labels; k++)
			{
				for (j = 0; j < (*demesP[k]).size(); j++)
				{
					(*demesP[k])[j]->label = k + 1;
				}

			}
		}

		total_phage_size = 0;
		for (j = 0; j < X; j++)
		{
			total_phage_size += (*demesP[j]).size();
		}


		/*Lyse and release*/

		//create new column in infectionTime vector
		infectionTime.insert(infectionTime.begin(), new vector<Bacterium*>);

		//create new phages, and delete lysed bacteria from object storage & from infectionTime & from demesB! 
		//(not the other way round which causes memory leak!)
		int s = (*(infectionTime.back())).size();

		if ((*infectionTime.back()).size() != 0)
		{
			for (j = 0; j < s; j++)
			{
				int label = (*infectionTime.back())[j]->label;
				int h = (*infectionTime.back())[j]->demeIndex;

				//create new phages
				for (k = 0; k < burst_size; k++)	//make this faster??????????????????????????
				{
					(*demesP[h]).push_back(new Phage);
					(*demesP[h]).back()->label = label;	//same label as the infected bacteria
					(*demesP[h]).back()->pmigra = pmigra;
					(*demesP[h]).back()->qd = qd;
					(*demesP[h]).back()->qiB = qiB;
					(*demesP[h]).back()->qiI = qiI;
				}
				//delete lysed bacteria from object storage & from demesB
				//first find bacteria coordinate
				for (k = 0; k < (*demesB[h]).size(); k++)
				{
					if ((*demesB[h])[k] == (*infectionTime.back())[j])
					{
						delete (*demesB[h])[k];
						(*demesB[h]).erase((*demesB[h]).begin() + k);
					}
				}
			}
		}
		//delete the last element in infectionTime vector and the vector it points to
		delete infectionTime.back();
		infectionTime.erase(infectionTime.begin() + infectionTime.size() - 1);



		/*die*/

		try
		{
			death_number = round(qd * total_phage_size);
			for (k = 0; k < death_number; k++)	//any way to make this faster??????????????????
			{
				//randomly pick one phage
				/*srand(time(NULL));
				total_phage_index = rand() % total_phage_size + 1;*/

				
				uniform_int_distribution<int> dist1{ 1, total_phage_size};
				// get random numbers with:
				total_phage_index = dist1(e);

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

		infect_B_number = std::round(qiB * total_phage_size);
		for (k = 0; k < infect_B_number; k++)
		{
			//randomly pick one phage
			/*srand(time(NULL));
			total_phage_index = rand() % total_phage_size + 1;*/

			
			uniform_int_distribution<int> dist2{ 1, total_phage_size};
			// get random numbers with:
			total_phage_index = dist2(e);

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

			//randomly pick one bacterium from the same deme if bacteria exist in that deme
			if ((*demesB[j]).size() > 0)
			{
				/*srand(time(NULL));
				bacterium_index = rand() % (*demesB[j]).size();*/

			
				int size = (*demesB[j]).size() - 1;
				uniform_int_distribution<int> dist3{ 0, size};
				// get random numbers with:
				bacterium_index = dist3(e);

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
				total_phage_size = total_phage_size - 1;
			}
		}


		/*migration*/

		if (swapScheme == true)	//complete this optoin????????????????????????
		{
			migration_number = round(pmigra / 2 * total_phage_size);
			for (k = 0; k < migration_number; k++)
			{
				////randomly pick one phage
				//srand(time(NULL));	
				//total_phage_index = rand() % total_phage_size + 1;

				uniform_int_distribution<int> dista{ 1, total_phage_size };
				total_phage_index = dista(e);
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
				/*srand(time(NULL));
				phage_index = rand() % (*demesP[j]).size();*/
				
				int size1 = (*demesP[j]).size() - 1;
				uniform_int_distribution<int> distb{ 0, size1};
				// get random numbers with:
				phage_index = distb(e);

				//deal with holes ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?

				//swap phages
				if (j > 0)	//if not the first deme:
				{
					/*srand(time(NULL));
					left_phage_index = rand() % ((*demesP[j - 1]).size());*/

					int size2 = (*demesP[j - 1]).size() - 1;
					uniform_int_distribution<int> distc{ 0, size2};
					left_phage_index = distc(e);

					temp = (*demesP[j])[b];
					(*demesP[j])[b] = (*demesP[j - 1])[left_phage_index];
					(*demesP[j - 1])[left_phage_index] = temp;
				}

				if (j < X - 1)	//if not the last deme:
				{
					/*srand(time(NULL));
					right_phage_index = rand() % ((*demesP[j + 1]).size());*/

					int size3 = (*demesP[j + 1]).size() - 1;
					uniform_int_distribution<int> distd{ 0, size3 };
					right_phage_index = distd(e);

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
				/*srand(time(NULL));
				total_phage_index = rand() % total_phage_size + 1;*/

				//randomly pick one phage
				
				uniform_int_distribution<int> dist4{ 1, total_phage_size};

				// get random numbers with:
				total_phage_index = dist4(e);


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
					demesB.push_back(new vector<Bacterium*>);
					for (k = 0; k < N; k++)
					{
						(*demesB[j + 1]).push_back(new Bacterium);	//N bacteria per deme initially
						(*demesB[j + 1])[k]->infected = false;
						(*demesB[j + 1])[k]->demeIndex = j + 1;	//keep original deme index as attribute, not to be changed when frame moves.
						(*demesB[j + 1])[k]->label = 0;
						(*demesB[j + 1])[k]->lysed = false;
						(*demesB[j + 1])[k]->ts_after_infection = 0;
						(*demesB[j + 1])[k]->burst_size = burst_size;
					}

					////randomly choose to move to the left or the right (1: left; 0: right)
					//srand(time(NULL));
					//direction = rand() % 2;


					//randomly pick one phage
					
					uniform_int_distribution<int> dist5{ 0, 1 };
					// get random numbers with:
					direction = dist5(e);


					if (direction == 1)
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
					demesB.erase(demesB.begin());
				}
				else
				{
					////randomly choose to move to the left or the right (1: left; 0: right)
					//srand(time(NULL));
					//direction = rand() % 2;


					//randomly pick one phage
				
					uniform_int_distribution<int> dist6{ 0, 1 };

					// get random numbers with:
					direction = dist6(e);



					if (direction == 1)
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
			//reinitialize label_proportion every time
			for (j = 0; j < demesP.size(); j++)
			{
				for (w = 0; w < labels; w++)
				{
					label_proportion[w][j] = 0;
				}
			}

			for (j = 0; j < demesP.size(); j++)
			{
				P_population[j] = (*demesP[j]).size();
				IB_population[j] = (*demesB[j]).size();
				I_population[j] = 0;
				for (k = 0; k < (*demesB[j]).size(); k++)
				{
					if ((*demesB[j])[k]->infected == true)
					{
						I_population[j] += 1;
					}
				}
				B_population[j] = IB_population[j] - I_population[j];
				//calculate label population
				for (k = 0; k < (*demesP[j]).size(); k++)
				{
					for (w = 0; w < labels; w++)
					{
						if ((*demesP[j])[k]->label == w + 1)	//+1 because actual label is greater than index.(start from 0 and 1) 
						{
							label_proportion[w][j] += 1;
							break;
						}
					}
				}

			}

			//calculate heterozygosity before dividing labels into proportions!
			tot = 0;
			heterozygosity.push_back(0);
			for (k = 0; k < labels; k++)
			{
				label_frequency[k] = 0;
			}
			for (j = 0; j < X; j++)
			{
				tot += P_population[j];
			}
			for (k = 0; k < labels; k++)
			{
				for (j = 0; j < X; j++)
				{
					label_frequency[k] += label_proportion[k][j];
				}
				label_frequency[k] /= tot;
			}
			for (k = 0; k < labels; k++)
			{
				heterozygosity.back() += label_frequency[k] * (1 - label_frequency[k]);
			}

			//calcalate real label_proportions
			for (j = 0; j < X; j++)
			{
				for (w = 0; w < labels; w++)
				{
					if (P_population[j] != 0)
					{
						label_proportion[w][j] = label_proportion[w][j] / P_population[j];
					}
				}
			}
			cout << "Current simulation step: " << i + 1 << endl;
			/*cout << "Phage population within each deme: " << P_population << endl;
			cout << "Uninfected bacteria population within each deme: " << B_population << endl;
			cout << "Infected bacteria population within each deme: " << I_population << endl;*/
			

			outfileP.open(filenameP, ios::app);
			for (j = 0; j < X; j++)
			outfileP << P_population[j] << " ";
			outfileP << endl;
			/*outfile.close();*/

			/*outfileB.open(filenameB, ios::app);*/			
			for (j = 0; j < X; j++)
				outfileP << B_population[j] << " ";
			outfileP << endl;
			/*outfileB.close();*/
			
			/*outfileI.open(filenameI, ios::app);*/
			for (j = 0; j < X; j++)
				outfileP << I_population[j] << " ";
			outfileP << endl;
			outfileP.close();

			if (i + 1 >= labelling_step)
			{
				outfileL.open(filenameL, ios::app);
				for (k = 0; k < labels; k++)	//reduce this section after making code modular???????????????????????????????
				{
					for (j = 0; j < X; j++)
					{
						outfileL << label_proportion[k][j] << " ";
					}
					outfileL << endl;
				}
				outfileL.close();

				outfileH.open(filenameH, ios::app);
				outfileH << heterozygosity.back() << " ";
				outfileH.close();
			}


		}

	}


	

	cin >> a;
}