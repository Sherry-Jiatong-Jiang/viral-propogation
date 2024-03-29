#define _USE_MATH_DEFINES	//for pi
#include <cmath>	//for rounding & calculating pmigra_eff
#include "withcoinfection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <random>	//for random device and mt19937
#include <string>
#include <numeric>	//for accumulate

using namespace std;

ifstream initfile;
ifstream loadcheckpoint;
ofstream outfileP;
ofstream outfileH;
ofstream outfileL;
ofstream outfileF2;
ofstream checkpoint;

//initialization file name
string initfilename = "init.txt";



int main()
{
	
	/*============================ List of parameters with default values, whose final values will be read from init file in a later section =================================================*/

	//files that keep track of P, B, I populations, heterozygosity, labelling proportions, and frame positions at each visualization step.
	string filenameP = "sim0P.dat";
	string filenameH = "sim0H.dat";
	string filenameL = "sim0L.dat";
	string filenameF2 = "sim0F2.dat";
	//random seed for the sequence of random generators
	unsigned int seed = 1;
	//whether adopting binomial distribution or not
	bool binomial = 1;
	//system parameters
	double dt = 1;   //1 unit simulation step time (unit: min) not used in code
	double dx = 31.62;	//31.62 (sqrt(1000) for matlab simulation) unit deme length (unit: um) not used in code
	int tao = 50;	//(15-25 for T7) lysis time (unit: simulation steps)
	int burst_size = 50;	//(10-400)
	int X = 100;	//number of demes shown in co-moving frame
	int N = 100;	//Number of bacteria in each deme
	int N0 = 100;	//initial phage numbers in the each deme 
	int Nx = 10;	//initial number of demes which have phages
	int simulation_steps = 500000;	//maximum simulation steps. Set to be large enough (~500000) so that simulations always end by reaching fixation or timeout instead of being terminated by loop index.
	int visualization_steps = 20;	//how often each output is shown on the screen & recorded in data files
	int labelling_step = 2000;	//after which step phages are given labels, approximately after equilibrium. Better to be specified as integer times of visualization_steps in order to record the very initial Ht value.
	int starting_step = 0;	/*which step the current simulation begins with. Set 0 as default if not restarting from a checkpoint.
	If restarting, set to be the second last checkpoint, or the last checkpoint if the job outfile shows a few more steps after the last checkpoint, to ensure that the last checkpoint is not corrupted by having timeout halfway through the last recorded step.
	And have to be integer times of Pausing_steps!) Then new output files are created to continue data after that step.*/
	int pausing_steps = 1000;	//how often the entire system status is recorded in order to continue later from a checkpoint file. Have to be integer times of visualization_steps!
	//phage probs parameters (per timestep)
	double qd = 0;	//(0) death probs
	double qiI = 0.00001;	//probs of infecting infected bacteria. This parameter is unused. Just set to be the same as qiB.
	double qiB = 0.00001;	// make sure qiB is less than 1 / N! Probs of infecting uninfected bacteria.
	double pmigra = 0.2;	//(0.2, 0.1-0.3) migration probability     (move to either side with pmigra/2, with exception of 1st deme which only can move to right with migra/2)
	int max_bacteria = 1000;	//theoretical number of bacteria per deme that gives full volume fraction under given dx. for use of calculating vol_frac in Pmigra with density dependence. 	
	int infection_mode = 0;	/*0: phage that infect infected bacteria will die (MESR);
	1:phage are not allowed to infect infected bacteria (in PDE paper) (SESR); 2: coinfection, i.e. number getting burst depends on how long between infection and lysis. (MEMR)*/
	int migration_mode = 0;	//0: constant pmigra; 1: density-dependent pmigra (depending on local vol_frac).

	int i, j, k, a = 0, b = 0, c = 0, w = 0; //variables to be used in for loops


	/*============================================== Reading parameter values from initialization file ====================================================================*/

	string paraName;
	initfile.open(initfilename, ios::in);
	for (j = 0; j < 22; j++)
	{
		try
		{
			initfile >> paraName;
			
			if (paraName == "seed:")
			{
				initfile >> seed;
				std::cout << "seed:" << endl << seed << endl;
			}
			else if (paraName == "binomial:")
			{
				initfile >> binomial;
				std::cout << "binomial:" << endl << binomial << endl;
			}
			else if (paraName == "dt:")
			{
				initfile >> dt;
				std::cout << "dt:" << endl << dt << endl;
			}
			else if (paraName == "dx:")
			{
				initfile >> dx;
				std::cout << "dx:" << endl << dx << endl;
			}
			else if (paraName == "tao:")
			{
				initfile >> tao;
				std::cout << "tao:" << endl << tao << endl;
			}
			else if (paraName == "burst_size:")
			{
				initfile >> burst_size;
				std::cout << "burst_size:" << endl << burst_size << endl;
			}
			else if (paraName == "X:")
			{
				initfile >> X;
				std::cout << "X:" << endl << X << endl;
			}
			else if (paraName == "N:")
			{
				initfile >> N;
				std::cout << "N:" << endl << N << endl;
			}
			else if (paraName == "N0:")
			{
				initfile >> N0;
				std::cout << "N0:" << endl << N0 << endl;
			}
			else if (paraName == "Nx:")
			{
				initfile >> Nx;
				std::cout << "Nx:" << endl << Nx << endl;
			}
			else if (paraName == "simulation_steps:")
			{
				initfile >> simulation_steps;
				std::cout << "simulation_steps:" << endl << simulation_steps << endl;
			}
			else if (paraName == "visualization_steps:")
			{
				initfile >> visualization_steps;
				std::cout << "visualization_steps:" << endl << visualization_steps << endl;
			}
			else if (paraName == "labelling_step:")
			{
				initfile >> labelling_step;
				std::cout << "labelling_step:" << endl << labelling_step << endl;
			}
			else if (paraName == "starting_step:")
			{
				initfile >> starting_step;
				std::cout << "starting_step:" << endl << starting_step << endl;
			}
			else if (paraName == "pausing_steps:")
			{
				initfile >> pausing_steps;
				std::cout << "pausing_steps:" << endl << pausing_steps << endl;
			}
			else if (paraName == "qd:")
			{
				initfile >> qd;
				std::cout << "qd:" << endl << qd << endl;
			}
			else if (paraName == "qiI:")
			{
				initfile >> qiI;
				std::cout << "qiI:" << endl << qiI << endl;
			}
			else if (paraName == "qiB:")
			{
				initfile >> qiB;
				std::cout << "qiB:" << endl << qiB << endl;
			}
			else if (paraName == "pmigra:")
			{
				initfile >> pmigra;
				std::cout << "pmigra:" << endl << pmigra << endl;
			}
			else if (paraName == "max_bacteria:")
			{
				initfile >> max_bacteria;
				std::cout << "max_bacteria:" << endl << max_bacteria << endl;
			}
			else if (paraName == "infection_mode:")
			{
				initfile >> infection_mode;
				std::cout << "infection_mode:" << endl << infection_mode << endl;
			}
			else if (paraName == "migration_mode:")
			{
			initfile >> migration_mode;
			std::cout << "migration_mode:" << endl << migration_mode << endl;
			}
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

	filenameP = "sim" + to_string(starting_step) + "P.dat";
	filenameH = "sim" + to_string(starting_step) + "H.dat";
	filenameL = "sim" + to_string(starting_step) + "L.dat";
	filenameF2 = "sim" + to_string(starting_step) + "F2.dat";

	initfile.close();


	/*================================================== Initializing intermediate parameters ===========================================================================*/

	int labels = X;	//number of initial different gene labels

	//parameters relating to output
	vector <int> P_population(X);	//output of phage population distribution
	vector <int> B_population(X);	//output of uninfected bacteria population distribution
	vector <int> I_population(X);	//output of infected bacteria population distribution
	vector <vector<double>> label_proportion(labels);//output of proportional distribution of each label within each deme, and initialize to zeroes ([0] corresponding to label 1 etc)
	int tot = 0;	//temporary storage of total phage population at each timestep 
	vector<double> label_frequency(labels);	//each element corresponds to the total frequency of a label withinin the whole population, to be used in the calculation of heterozygosity.
	vector<double> heterozygosity;	//array to characterise genetic diversity at the wave front
	int FramePos = 0;	//keeps track of how many demes the frame has moved forward by.
	
	//temporary parameters
	int total_phage_index = 0, total_phage_size = 0, bacterium_index = 0, phage_index = 0, left_phage_index = 0, right_phage_index = 0;
	int death_number = 0, infect_B_number = 0, infect_I_number = 0, migration_number = 0;
	int direction = 0;
	double pmigra_eff = 0;
	int deme_index = 0;
	vector<int> unlysed_bacteria_number(X);

	vector <vector <Bacterium*>* > demesB(X);
	vector <vector <int>* > demesP(X);

	//random_device rd;
	mt19937 e{ seed }; // or std::default_random_engine e{rd()};

	
					


	/*============================================================= Initialization of demes and agents =============================================================================*/

	/*demesB and demesP are two vectors of initial size X storing pointers which point to
	a group of vectors representing demes of bacteria (objects) and phages (integers) respectively.
	A vector of a deme of bacteria contains pointers to bacteria objects. A vector of a deme of phages contains integers.*/

	//if the current simulation freshly started instead of from previous checkpoints (pausing steps):
	if (starting_step == 0)
	{
		for (i = 0; i < X; i++)
		{
			demesB[i] = new vector<Bacterium*>;	//X demes of bacteria in total
			for (j = 0; j < N; j++)
			{
				(*demesB[i]).push_back(new Bacterium);	//N bacteria per deme initially
				(*demesB[i])[j]->infected = false;
				(*demesB[i])[j]->label = 0;
				(*demesB[i])[j]->lysed = false;
				(*demesB[i])[j]->infectionStep = 0;
				(*demesB[i])[j]->labels = {};
				(*demesB[i])[j]->steps = {};
			}
		}

		for (i = 0; i < X; i++)
		{
			demesP[i] = new vector<int>;	//X demes of phages in total

			if (i < Nx)
			{
				for (j = 0; j < N0; j++)
				{
					(*demesP[i]).push_back(0);
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
			//For front profiles of phage, infected bacteria and uninfected bacteria population
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
					if ((*demesP[j])[k] == i + 1)	//+1 because actual label is greater than index.(start from 0 and 1) 
					{
						label_proportion[i][j] += 1;
					}
				}
			}


		}
		//calculate heterozygosity when label_proportion still represent label quantities!
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

		//divide by total population to calculate real label_proportion
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
	}

	//if the current simulation is continued from previous checkpoint
	else
	{
		//read data from checkpoint*starting_steps*.dat
		loadcheckpoint.open("checkpoint" + to_string(starting_step) + ".dat", ios::in);
		
		if (loadcheckpoint.is_open() == 0)
		{
			std:cout << "Specified checkpoint file does not exist! Exiting program.";
			return 1;
		}

		loadcheckpoint >> FramePos;

		int num;
		int vec_attri_size;
		string str;
		int j;

		for (j = 0; j < X; j++)
		{
			getline(loadcheckpoint, str);
			demesP[j] = new vector<int>;
			istringstream ss(str);
			while (ss >> num)
			{
				(*demesP[j]).push_back(num);
			}
		}

		try
		{
			//each line is data for a deme
			for (j = 0; j < X; j++)
			{
				getline(loadcheckpoint, str);
				demesB[j] = new vector<Bacterium*>;
				istringstream ss(str);
				while (ss >> num)
				{
					(*demesB[j]).push_back(new Bacterium);
					(*demesB[j]).back()->label = num;
					ss >> num;
					(*demesB[j]).back()->infected = num;
					ss >> num;
					(*demesB[j]).back()->lysed = num;
					ss >> num;
					(*demesB[j]).back()->infectionStep = num;
					ss >> num;
					vec_attri_size = num;
					for (k = 0; k < vec_attri_size; k++)
					{
						ss >> num;
						((*demesB[j]).back()->labels).push_back(num);
					}
					for (k = 0; k < vec_attri_size; k++)
					{
						ss >> num;
						((*demesB[j]).back()->steps).push_back(num);
					}
					ss >> num;
					/*if two values before and after the two vectors (*demesB[j]).back()->labels and (*demesB[j]).back()->steps are different, 
					it means reading was messed up somewhere and thus inconsistent. */
					if (num != vec_attri_size)
						throw 1;
				}
			}
			loadcheckpoint.close();
		}
		catch (int e)
		{
			std::cout << "Inconsistent checkpoint data reading! Exiting program.";
			return 1;
		}

		//vector initialization (without output)
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
		}
	}
	
	//printing progress on screen
	std::cout.precision(2);
	std::cout << "Current simulation step: " << starting_step << endl;


	



	/*Simulation steps*/

	//i: simulation timestep (generation number, cycle number). having extracted infomation about the starting_step and begin with the (starting_step + 1)th step.
	for (i = starting_step; i < simulation_steps; i++)
	{

		/*if at equilibrium, label phages*/
		if (i + 1 == labelling_step)
		{
			for (k = 0; k < labels; k++)
			{
				for (j = 0; j < (*demesP[k]).size(); j++)
				{
					(*demesP[k])[j] = k + 1;
				}

			}
		}

		total_phage_size = 0;
		for (j = 0; j < X; j++)
		{
			total_phage_size += (*demesP[j]).size();
		}


	

		/*========================================================================  die  ================================================================================================*/

		/*option for phage to die naturally. Not currently used. Set qd = 0.
		Randomly choose qd * total_phage_size number of phagesand kill each one.*/
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
			//work out vector index of selected phage out of total_phage_index: (*demesP[j])[b]
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

			//kill the selected phage
			{(*demesP[j]).erase((*demesP[j]).begin() + b); }
			total_phage_size = total_phage_size - 1;
		}


		
		

		/*======================================================================== Co-infecting bacteria ========================================================================================*/

		/*Infection	probability of qiB * B / N is achieved by probability chain rule: first select a number of phage with probability qiB * N.
		For each selected phage, choose a random bacterium in the same deme with probability B / N. (idle with probability 1 - B / N, and idle if selected bacterium is lysed.)
		B here is the number of bacteria in a deme.*/
			
		//randomly pick a number of phage from total phage, with probability qiB * N
		if (binomial == false)
		{
			infect_B_number = std::round(qiB * N * total_phage_size);
		}
		else
		{
			binomial_distribution<int> bdist2(total_phage_size, qiB * N);
			infect_B_number = bdist2(e);
		}

		for (k = 0; k < infect_B_number; k++)
		{
			//randomly select a phage out of total phage size
			uniform_int_distribution<int> dist2{ 1, total_phage_size };
			// get random numbers with:
			total_phage_index = dist2(e);

			a = total_phage_index;
			//work out vector index of selected phage out of total_phage_index: (*demesP[j])[b]
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

			//randomly pick one bacterium from the same deme if bacteria exist in that deme, with probability *(demeB[j]).size() / N
			if ((*demesB[j]).size() > 0)
			{
				uniform_int_distribution<int> dist3{ 0, N - 1 };
				bacterium_index = dist3(e);
				int size = (*demesB[j]).size();
				if (bacterium_index < size)
				{
					//it's ok that size includes lysed bacteria, because if they are chosen, nothing happens, as if size hasn't included them. 
					//if infecting uninfected bacteria:
					if ((*((*demesB[j])[bacterium_index])).infected == false && (*((*demesB[j])[bacterium_index])).lysed == false)
					{
						(*((*demesB[j])[bacterium_index])).label = (*demesP[j])[b];
						(*((*demesB[j])[bacterium_index])).infected = true;

						(*((*demesB[j])[bacterium_index])).infectionStep = i;

						//delete phage after infection
						(*demesP[j]).erase((*demesP[j]).begin() + b);
						total_phage_size = total_phage_size - 1;
					}

					//if infecting infected bacteria:
					else if ((*((*demesB[j])[bacterium_index])).lysed == false)
					{
						if (infection_mode == 0)	//not used in this version
						{
							//delete phage after infection
							(*demesP[j]).erase((*demesP[j]).begin() + b);
							total_phage_size = total_phage_size - 1;
						}
						else if (infection_mode == 1)	//not used in this version
						{	
							//then phage don't infect and don't die, same as PDE paper
						}
						else
						{
							//coinfection, if infection_mode = 2
							((*((*demesB[j])[bacterium_index])).labels).push_back((*demesP[j])[b]);
							((*((*demesB[j])[bacterium_index])).steps).push_back(i);

							//delete phage after infection
							(*demesP[j]).erase((*demesP[j]).begin() + b);
							total_phage_size = total_phage_size - 1;
						}
					}

					//if lysed bacterium is selected
					else
					{
						// do nothing
					}
				}
			}
		}
		
		


		/*======================================================================= Migration / Dispersal ==========================================================================================*/

		/*if pmigra is density-independent. Randomly choose pmigra * total_phage_size number of phages and migrate each one.*/
		if (migration_mode == 0)
		{
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
				//work out vector index of selected phage out of total_phage_index: (*demesP[j])[b] 
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
				//if selected phage is in the first deme, only move to the right, but with half pmigra probs
				if (j == 0)
				{
					//randomly pick a direction
					uniform_int_distribution<int> dist5{ 0, 1 };
					direction = dist5(e);
					if (direction == 0)
					{
						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);
					}
				}
				//if selected phage is in the last deme, create new deme if moving to right
				else if (j == X - 1)
				{
					//randomly pick a direction
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
						demesP.push_back(new vector<int>);
						demesB.push_back(new vector<Bacterium*>);
						for (k = 0; k < N; k++)
						{
							(*demesB[j + 1]).push_back(new Bacterium);	//N bacteria per deme initially
							(*demesB[j + 1])[k]->infected = false;
							(*demesB[j + 1])[k]->label = 0;
							(*demesB[j + 1])[k]->lysed = false;
							(*demesB[j + 1])[k]->infectionStep = 0;
							(*demesB[j + 1])[k]->labels = {};
							(*demesB[j + 1])[k]->steps = {};
						}



						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);


						//delete first deme (only at the end in order not to mess up indexes).
						total_phage_size -= (*demesP[0]).size();

						for (k = 0; k < (*demesB[0]).size(); k++)
						{
							delete (*demesB[0])[k];
						}
						delete demesP[0];
						delete demesB[0];
						demesP.erase(demesP.begin());
						demesB.erase(demesB.begin());

						//print out frame position on the screen is frame has moved.
						FramePos++;
						std::cout << "FramePos: " << FramePos << endl;
					}

				}

				//if selected phage is in the bulk of the demes
				else
				{

					//randomly pick a direction
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
		}
		/*if pmigra is dependent on local bacteria density. In each inner iteration randomly choose one phage, migrate phage, global update*/

		/*The way to achieve different migration probs for each deme is via probability chain rule: First, randomly select pmigra * total_phage_size number of phage globally,
		then iterate over each selected phage and keep it with probability pmigra_eff (delete with probability 1 - pmigra_eff),
		where pmigra_eff is the ratio of real migration probs to intrinsic migration probs calculated for the deme where the selected phage occupies.*/

		else
		{

			//Calculate unlysed bacteria density in each deme
			for (j = 0; j < X; j++)
			{
				unlysed_bacteria_number[j] = 0;
				for (k = 0; k < (*demesB[j]).size(); k++)
				{
					if ((*demesB[j])[k]->lysed == false)
					{
						unlysed_bacteria_number[j] ++;
					}
				}
			}
			//randomly pick a number of phages from total phage size, with probability pmigra
			if (binomial == false)
			{
				migration_number = std::round(pmigra * total_phage_size);
			}
			else
			{
				binomial_distribution<int> bdist5(total_phage_size, pmigra);
				migration_number = bdist5(e);
			}
			for (k = 0; k < migration_number; k++)
			{

				//randomly pick one phage

				uniform_int_distribution<int> dist8{ 1, total_phage_size };

				// get random numbers with:
				total_phage_index = dist8(e);

				a = total_phage_index;
				//work out vector index of selected phage out of total_phage_index: (*demesP[j])[b] 
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

				//formula for ratio of real migration rate to intrinsic migration rate that depends on local bacteria density
				pmigra_eff = (1 - (M_PI - 1) * double(unlysed_bacteria_number[j]) / double(max_bacteria) / 0.5 - 0.85571 * pow((double(unlysed_bacteria_number[j]) /double(max_bacteria) / 0.5), 2));
				
				
				//Use Monte Carlo sampling to set up a probability of pmigra_eff

				//pick a random number from total phage size
				uniform_int_distribution<int> dist9{ 1, total_phage_size };
				int chance = dist9(e);

				//compare the random variable "chance" of uniform distribution between 1 and total_phage_size with pmigra_eff * total_phage_size:
				if (chance <= std::round(pmigra_eff * total_phage_size))
				{
					
					//if selected phage is in the first deme, only move to the right, but with half pmigra probs
					if (j == 0)
					{
						uniform_int_distribution<int> dist10{ 0, 1 };
						direction = dist10(e);
						if (direction == 0)
						{
							(*demesP[j + 1]).push_back((*demesP[j])[b]);
							(*demesP[j]).erase((*demesP[j]).begin() + b);
						}
					}
					//if selected phage is in the last deme, create new deme if moving to right
					else if (j == X - 1)
					{
						//randomly pick a direction

						uniform_int_distribution<int> dist11{ 0, 1 };
						// get random numbers with:
						direction = dist11(e);

						if (direction == 1)
						{
							(*demesP[j - 1]).push_back((*demesP[j])[b]);
							(*demesP[j]).erase((*demesP[j]).begin() + b);
						}
						else
						{
							//create new deme if moving to the right.
							demesP.push_back(new vector<int>);
							demesB.push_back(new vector<Bacterium*>);
							for (k = 0; k < N; k++)
							{
								(*demesB[j + 1]).push_back(new Bacterium);	//N bacteria per deme initially
								(*demesB[j + 1])[k]->infected = false;
								(*demesB[j + 1])[k]->label = 0;
								(*demesB[j + 1])[k]->lysed = false;
								(*demesB[j + 1])[k]->infectionStep = 0;
								(*demesB[j + 1])[k]->labels = {};
								(*demesB[j + 1])[k]->steps = {};
							}



							(*demesP[j + 1]).push_back((*demesP[j])[b]);
							(*demesP[j]).erase((*demesP[j]).begin() + b);


							//delete first deme (only at the end in order not to mess up indexes).
							total_phage_size -= (*demesP[0]).size();

							for (k = 0; k < (*demesB[0]).size(); k++)
							{
								delete (*demesB[0])[k];
							}
							delete demesP[0];
							delete demesB[0];
							demesP.erase(demesP.begin());
							demesB.erase(demesB.begin());

							//update unlysed bacteria number vector after frame movement.
							unlysed_bacteria_number.erase(unlysed_bacteria_number.begin());
							unlysed_bacteria_number.push_back(N);

							//print out frame position on the screen is frame has moved.
							FramePos++;
							std::cout << "FramePos: " << FramePos << endl;
						}

					}

					//if selected phage is in the bulk of the demes
					else
					{

						//randomly pick one phage
						uniform_int_distribution<int> dist12{ 0, 1 };

						// get random numbers with:
						direction = dist12(e);

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

				//if "chance" > pmigra_eff * total_phage_size:
				else
				{
					//Do nothing
				}
			}
				
		}



		/*============================================================= bacteria lysis and new phage creation ====================================================================================*/

		for (j = 0; j < X; j++)
		{
			for (w = 0; w < (*demesB[j]).size(); w++)
			{
				if (((*((*demesB[j])[w])).infected == true) && (i - (*((*demesB[j])[w])).infectionStep == tao) && ((*((*demesB[j])[w])).lysed == false))
				{
					//if coinfection is not allowed (not used in this version, use PhageSim.cpp and PhageSim.h instead.)
					if (infection_mode < 2)
					{
						(*demesP[j]).insert((*demesP[j]).end(), burst_size, (*((*demesB[j])[w])).label);
						(*((*demesB[j])[w])).lysed = true;
					}

					//if coinfection is allowed
					else
					{
						int accum_phages = ((*((*demesB[j])[w])).labels).size();	//accum_phages equals the number of all infected phages
						int accum_time = 0;
						if (accum_phages != 0)
						{
							accum_time = accumulate(((*((*demesB[j])[w])).steps).begin(), ((*((*demesB[j])[w])).steps).end(), 0);
						}
						accum_time = accum_phages * i - accum_time + tao;	//accum_time equals to the sum of infection time of all infected phages
						
						int size = 0;

						if (binomial == false)
						{
							//burst of first infected phage (division of integers has already rounded quotient to integer!)
							size = std::round(double(tao) / double(accum_time) * double(burst_size));
							(*demesP[j]).insert((*demesP[j]).end(), size, (*((*demesB[j])[w])).label);

							//burst of other phages
							for (k = 0; k < accum_phages; k++)
							{
								//calculate number taken by each label
								size = std::round((double(i) - double((*((*demesB[j])[w])).steps[k])) / double(accum_time) * double(burst_size));
								(*demesP[j]).insert((*demesP[j]).end(), size, (*((*demesB[j])[w])).labels[k]);
							}
						}
						else
						{
							//burst of offsprings of first infected phage
							double quot = double(tao) / double(accum_time);
							binomial_distribution<int> bdist6(burst_size, quot);
							size = bdist6(e);
							(*demesP[j]).insert((*demesP[j]).end(), size, (*((*demesB[j])[w])).label);

							//burst of offsprings of other phages
							for (k = 0; k < accum_phages; k++)
							{
								//calculate fraction taken by each label
								quot = (double(i) - double((*((*demesB[j])[w])).steps[k])) / double(accum_time);
								binomial_distribution<int> bdist7(burst_size, quot);
								size = bdist7(e);
								(*demesP[j]).insert((*demesP[j]).end(), size, (*((*demesB[j])[w])).labels[k]);
							}
						}

						//set bacterium to be lysed
						(*((*demesB[j])[w])).lysed = true;
					}
				}
			}
		}

		/*============================================================== checkpoint output at pausing_steps =====================================================================================*/

		if ((i + 1) % pausing_steps == 0)
		{
			//output to checkpoint(i+1).dat 
			checkpoint.open("checkpoint" + to_string(i + 1) + ".dat", ios::out);

			checkpoint << FramePos << endl;
			
			for (j = 0; j < X; j++)
			{
				//note: if (*demesP[j]).size() is zero, an empty line will be written.
				for (k = 0; k < (*demesP[j]).size(); k++)
					checkpoint << (*demesP[j])[k] << " ";
				checkpoint << endl;
			}
			
			for (j = 0; j < X; j++)
			{
				//note: if (*demesB[j]).size() is zero, an empty line will be written.
				for (k = 0; k < (*demesB[j]).size(); k++)
				{
					checkpoint << (*demesB[j])[k]->label << " " << (*demesB[j])[k]->infected << " " << (*demesB[j])[k]->lysed << " " << (*demesB[j])[k]->infectionStep << " " << ((*demesB[j])[k]->labels).size() << " ";
					for (w = 0; w < ((*demesB[j])[k]->labels).size(); w++)
					{
						checkpoint << (*demesB[j])[k]->labels[w] << " ";
					}
					for (w = 0; w < ((*demesB[j])[k]->labels).size(); w++)
					{
						checkpoint << (*demesB[j])[k]->steps[w] << " ";
					}
					//write vector length both before and after vectors, acting as a safeguard to be able to check whether reading is at the correct position.
					checkpoint << ((*demesB[j])[k]->labels).size() << " ";
				}
				checkpoint << endl;
			}

			checkpoint.close();
		}

		/*=============================================================== data output at visualization_steps ====================================================================================*/

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
				//For front profiles of phage, infected bacteria and uninfected bacteria population
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
				//calculate label quantities
				for (k = 0; k < (*demesP[j]).size(); k++)
				{
					for (w = 0; w < labels; w++)
					{
						if ((*demesP[j])[k] == w + 1)	//+1 because actual label is greater than index.(start from 0 and 1) 
						{
							label_proportion[w][j] += 1;
							break;
						}
					}
				}
			}

			//calculate heterozygosity when label_proportion still represent label quantities!
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

			//divide by total population to calcalate real label_proportion
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

			//print out current simulation step
			std::cout << "Current simulation step: " << i + 1 << endl;


			//save front profiles to output files
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


			//after labelling_step, start to record heterozygosity and label proportions and save to output files
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

					//end simulation early.
					std::cout << "Fixation reached." << endl;
					break;
				}
			}

			outfileF2.open(filenameF2, ios::app);
			outfileF2 << FramePos << " ";
			outfileF2.close();

		}

	}

	/*====================================================================== Simulation steps end ==============================================================================================*/
	//Either by the end of simulation_steps or by reaching fixation.

	std::cout << "Simulation End." << endl;

}