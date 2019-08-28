#include "testsearchtime.h"
#include <iostream>
#include <fstream>
#include <cmath>	//for rounding
#include <array>
#include <vector>
#include <random>	//for random device and mt19937

using namespace std;

ifstream initfile;

ofstream outfileP;
ofstream outfileH;
ofstream outfileL;
ofstream outfileF2;

string initfilename = "init001.txt";



int main()
{
	
	/*parameters whose final values will be read from init file */

	//files that keep P, B, I populations, heterozygosity, labelling proportions, and framemoving steps and frame positions at each step.
	string filenameP = "sim001P.dat";	//must be different everytime! otherwise will always append to previous file.
	string filenameH = "sim001H.dat";
	string filenameL = "sim001L.dat";
	string filenameF2 = "sim001F2.dat";
	//random seed for sequence of random generators
	unsigned int seed = 1;
	bool binomial = false;
	//system parameters
	double dt = 1;   //1 unit simulation step time (min) only for record
	double dx = 31.62;	//31.62 (sqrt(1000) for matlab simulation) unit deme length (um) only for record
	int tao = 50;	//(15-25 for T7) lysis time (steps)
	int burst_size = 50;	//(50, 10-400)
	int X = 100;	//max demes in frame
	int N = 1000, Np = N * burst_size;//max bacteria, and max phages
	int N0 = 1000;		//initial phage numbers in the each deme (N0 and N only affecting initial distribuiton, and can be accounted for by tuning probabilities)
	int Nx = 10;	//initial number of demes which have phages
	int simulation_steps = 4000;	//total simulation steps (total time/dt)
	int visualization_steps = 10;	//how many steps before each output on the screen
	int labelling_step = 2000;	//how many steps to reach equilibrium before labelling phages
	//phage probs parameters (per timestep)
	double qd = 0;	//(0) death probs
	double qiI = 0.01;	//(try different orders of mag) infecting infected bacteria probs
	double qiB = 0.01;	//(try different orders of mag) infecting uninfected bacteria probs
	double pmigra = 0.05;	//(0.2, 0.1-0.3) migration probability     (move to either side with pmigra/2, with exception of 1st deme which only can move to right with migra/2)


	int i, j, k, a = 0, b = 0, c = 0, w = 0; //to be used in the for loops
	string paraName;

	initfile.open(initfilename, ios::in);
	for (j = 0; j < 21; j++)
	{
		try
		{
			initfile >> paraName;
			if (paraName == "filenameP:")
				initfile >> filenameP;
			else if (paraName == "filenameH:")
				initfile >> filenameH;
			else if (paraName == "filenameL:")
				initfile >> filenameL;
			else if (paraName == "filenameF2:")
				initfile >> filenameF2;
			else if (paraName == "seed:")
				initfile >> seed;
			else if (paraName == "binomial:")
				initfile >> binomial;
			else if (paraName == "dt:")
				initfile >> dt;
			else if (paraName == "dx:")
				initfile >> dx;
			else if (paraName == "tao:")
				initfile >> tao;
			else if (paraName == "burst_size:")
				initfile >> burst_size;
			else if (paraName == "X:")
				initfile >> X;
			else if (paraName == "N:")
				initfile >> N;
			else if (paraName == "N0:")
				initfile >> N0;
			else if (paraName == "Nx:")
				initfile >> Nx;
			else if (paraName == "simulation_steps:")
				initfile >> simulation_steps;
			else if (paraName == "visualization_steps:")
				initfile >> visualization_steps;
			else if (paraName == "labelling_step:")
				initfile >> labelling_step;
			else if (paraName == "qd:")
				initfile >> qd;
			else if (paraName == "qiI:")
				initfile >> qiI;
			else if (paraName == "qiB:")
				initfile >> qiB;
			else if (paraName == "pmigra:")
				initfile >> pmigra;
			else
			{
				std::cout << "INITFILE READING ERROR!" << endl;
				simulation_steps = 0;
				break;
			}
		}
		catch (exception& e)
		{
			std::cout << "Standard exception: " << e.what() << endl;
		}

	}
	initfile.close();


	


	int labels = X;	// << X for current initialization scheme! number of initial different gene labels, constant to be used to initialize array size later

	//parameters relating to output
	vector <int> P_population(X);	//output of phage population distribution
	//vector <int> IB_population(X);	//output of total bacteria population distribution
	vector <int> B_population(X);	//output of uninfected bacteria population distribution
	vector <int> I_population(X);	//output of infected bacteria population distribution
	vector <vector<double>> label_proportion(labels);//output of proportional distribution of each label within each deme, and initialize to zeroes ([0] corresponding to label 1 etc)
	int tot = 0;	//temporary storage of total phage population at each timestep 
	vector<double> label_frequency(labels);	//each element corresponds to the total frequency of a label withinin the whole population, to be used in the calculation of heterozygosity.
	vector<double> heterozygosity;	//of size (simulation_steps / visualization_steps + 1), array to characterise genetic diversity at the wave front

	//intermediate parameters
	int total_phage_index = 0, total_phage_size = 0, bacterium_index = 0, phage_index = 0, left_phage_index = 0, right_phage_index = 0;
	int death_number = 0, infect_B_number = 0, infect_I_number = 0, migration_number = 0;
	int direction = 0;
	int FramePos = 0;	//keeps track of how many demes the frame has moved forward by.

	vector <vector <Bacterium*>* > demesB(X);
	vector <vector <Phage*>* > demesP(X);


	//random_device rd;
	mt19937 e{ seed }; // or std::default_random_engine e{rd()};

	
					


    /*Initialization of demes and agents*/

	/*demesB and demesP are two vectors of initial size X storing pointers which point to
	a group of vectors which represent demes of bacteria and phages respectively.
	A vector of a deme of phages, e.g., contains pointers of phage objects.*/

	for (i = 0; i < X; i++)
	{
		demesB[i] = new vector<Bacterium*>;	//X demes of bacteria in total
		for (j = 0; j < N; j++)
		{
			(*demesB[i]).push_back(new Bacterium);	//N bacteria per deme initially
			(*demesB[i])[j]->infected = false;
			(*demesB[i])[j]->label = 0;
			(*demesB[i])[j]->lysed = false;
			(*demesB[i])[j]->infectionStep = -1;
		}
	}

	for (i = 0; i < X; i++)
	{
		demesP[i] = new vector<Phage*>;	//X demes of phages in total

		if (i < Nx)
		{
			for (j = 0; j < N0; j++)
			{
				(*demesP[i]).push_back(new Phage);
				(*demesP[i])[j]->label = 0;
			}
		}

	}

	


	/*step 0 output showing initial distribution*/

	//initialize label_proportion vector dimension
	vector <double> lab_prop(X);
	for (j = 0; j < labels; j++)
	{
		label_proportion[j] = lab_prop;
	}

	for (j = 0; j < X; j++)
	{
		P_population[j] = (*demesP[j]).size();
		I_population[j] = 0;
		B_population[j] = 0;


		for (k = 0; k < (*demesB[j]).size(); k++)
		{
			if ((*demesB[j])[k]->infected == true && (*demesB[j])[k]->lysed == false)
			{
				I_population[j] += 1;
			}
			if ((*demesB[j])[k]->infected == false && (*demesB[j])[k]->lysed == false)
			{
				B_population[j] += 1;
			}
		}

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
	//calculate heterozygosity when label_portions still represent label quantities!
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
	std::cout.precision(2);
	std::cout << "Current simulation step: " << 0 << endl;
	





	/*Simulation steps*/

	//i: simulation timestep
	for (i = 0; i < simulation_steps; i++)
	{

		/*if at equilibrium, label phages*/
		if (i + 1 == labelling_step)
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


	

		/*die*/

			if (binomial == false)
			{
				death_number = std::round(qd* total_phage_size);
			}
			else
			{
				binomial_distribution<int> bdist1(total_phage_size, qd);
				death_number = bdist1(e);
			}

			for (k = 0; k < death_number; k++)
			{

				uniform_int_distribution<int> dist1{ 1, total_phage_size };
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
				{(*demesP[j]).erase((*demesP[j]).begin() + b); }
				total_phage_size = total_phage_size - 1;
			}


		
		

		/*infect uninfected and infected bacteria*/

		if (binomial == false)
		{
			infect_B_number = std::round(qiB * total_phage_size);
		}
		else
		{
			binomial_distribution<int> bdist2(total_phage_size, qiB);
			infect_B_number = bdist2(e);
		}
		
		for (k = 0; k < infect_B_number; k++)
		{

			uniform_int_distribution<int> dist2{ 1, total_phage_size };
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

				int size = (*demesB[j]).size() - 1;
				uniform_int_distribution<int> dist3{ 0, size };
				// get random numbers with:
				bacterium_index = dist3(e);

				//if infecting uninfected bacteria:
				if ((*((*demesB[j])[bacterium_index])).infected == false && (*((*demesB[j])[bacterium_index])).lysed == false)
				{
					(*((*demesB[j])[bacterium_index])).label = (*((*demesP[j])[b])).label;
					(*((*demesB[j])[bacterium_index])).infected = true;

					(*((*demesB[j])[bacterium_index])).infectionStep = i;

					//delete phage after infection
					delete (*demesP[j])[b];
					(*demesP[j]).erase((*demesP[j]).begin() + b);
					total_phage_size = total_phage_size - 1;
				}

				//if infecting infected bacteria:
				else if ( (*((*demesB[j])[bacterium_index])).lysed == false)
				{
					//delete phage after infection
					delete (*demesP[j])[b];
					(*demesP[j]).erase((*demesP[j]).begin() + b);
					total_phage_size = total_phage_size - 1;
				}
			}
		}




		/*migration*/
		
			if (binomial == false)
			{
				migration_number = std::round(pmigra * total_phage_size);
			}
			else
			{
				binomial_distribution<int> bdist4(total_phage_size, pmigra);
				migration_number = bdist4(e);
			}
			for (k = 0; k < migration_number; k++)
			{

				//randomly pick one phage

				uniform_int_distribution<int> dist4{ 1, total_phage_size };

				// get random numbers with:
				total_phage_index = dist4(e);

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
				//if in the first deme, only move to the right, but with half pmigra probs
				if (j == 0)
				{
					uniform_int_distribution<int> dist5{ 0, 1 };
					direction = dist5(e);
					if (direction == 0)
					{
						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);
					}
				}
				//if in the last deme, create new deme
				else if (j == X - 1)
				{
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
						//create new deme if moving to the right.
						demesP.push_back(new vector<Phage*>);
						demesB.push_back(new vector<Bacterium*>);
						for (k = 0; k < N; k++)
						{
							(*demesB[j + 1]).push_back(new Bacterium);	//N bacteria per deme initially
							(*demesB[j + 1])[k]->infected = false;
							(*demesB[j + 1])[k]->label = 0;
							(*demesB[j + 1])[k]->lysed = false;
							(*demesB[j + 1])[k]->infectionStep = -1;
						}



						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);

						
						//delete first deme (only at the end in order not to mess up with indexes).
						total_phage_size -= (*demesP[0]).size();

						for (k = 0; k < (*demesP[0]).size(); k++)
						{
							delete (*demesP[0])[k];
						}
						for (k = 0; k < (*demesB[0]).size(); k++)
						{
							delete (*demesB[0])[k];
						}
						delete demesP[0];
						delete demesB[0];
						demesP.erase(demesP.begin());
						demesB.erase(demesB.begin());
					}
					
					FramePos++;
					std::cout << "FramePos: " << FramePos << endl;
				}
				else
				{

					//randomly pick one phage
					uniform_int_distribution<int> dist7{ 0, 1 };

					// get random numbers with:
					direction = dist7(e);
					
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

		


		/*bacteria lysis and new phage creation*/
		for (j = 0; j < X; j++)
		{
			for (w = 0; w < (*demesB[j]).size(); w++)
			{
				if (((*((*demesB[j])[w])).infected == true) && (i - (*((*demesB[j])[w])).infectionStep == tao) && ((*((*demesB[j])[w])).lysed == false))
				{
					for (c = 0; c < burst_size; c++)
					{
						(*demesP[j]).push_back(new Phage);
						(*demesP[j])[(*demesP[j]).size() - 1]->label = (*((*demesB[j])[w])).label;
					}
					(*((*demesB[j])[w])).lysed = true;
				}
			}
		}




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
				I_population[j] = 0;
				B_population[j] = 0;
				for (k = 0; k < (*demesB[j]).size(); k++)
				{
					if ((*demesB[j])[k]->infected == true && (*demesB[j])[k]->lysed == false)
					{
						I_population[j] += 1;
					}
					if ((*demesB[j])[k]->infected == false && (*demesB[j])[k]->lysed == false)
					{
						B_population[j] += 1;
					}
				}
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

			//calculate heterozygosity when label_portions still represent label quantities!
			tot = 0;
			heterozygosity.push_back(0);
			for (k = 0; k < labels; k++)
			{
				label_frequency[k] = 0;	//initialization
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
			std::cout << "Current simulation step: " << i + 1 << endl;

			outfileP.open(filenameP, ios::app);
			
			for (j = 0; j < X; j++)
				outfileP << P_population[j] << " ";
			outfileP << endl;

			for (j = 0; j < X; j++)
				outfileP << B_population[j] << " ";
			outfileP << endl;

			for (j = 0; j < X; j++)
				outfileP << I_population[j] << " ";
			outfileP << endl;
			outfileP.close();

			if (i + 1 >= labelling_step)
			{
				outfileL.open(filenameL, ios::app);
				for (k = 0; k < labels; k++)
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

				//if fixation is reached before simulation ends (only able to detect at visualization steps, i.e. may miss the exact fixation step)
				if (heterozygosity.back() == 0)
				{
					//output the last data for outputfileF2 before breaking the loop which skips those lines.
					outfileF2.open(filenameF2, ios::app);
					outfileF2 << FramePos << " ";
					outfileF2.close();

					std::cout << "Fixation reached." << endl;
					break;
				}
			}

			outfileF2.open(filenameF2, ios::app);
			outfileF2 << FramePos << " ";
			outfileF2.close();

		}

	}

	//shouldn't be used on clusters
	//std::cin >> a;

	std::cout << "Simulation End." << endl;

}