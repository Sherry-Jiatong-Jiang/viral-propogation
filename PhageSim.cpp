#include "PhageSim.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>	//for rounding
#include <array>
#include <vector>
#include <random>	//for random device and mt19937
#include <string>

using namespace std;

ifstream initfile;
ifstream loadcheckpoint;
ofstream outfileP;
ofstream outfileH;
ofstream outfileL;
ofstream outfileF2;
ofstream checkpoint;

string initfilename = "init.txt";



int main()
{
	
	/*parameters whose final values will be read from init file */

	//files that keep P, B, I populations, heterozygosity, labelling proportions, and framemoving steps and frame positions at each step.
	string filenameP = "sim0P.dat";	//must be different everytime! otherwise will always append to previous file.
	string filenameH = "sim0H.dat";
	string filenameL = "sim0L.dat";
	string filenameF2 = "sim0F2.dat";
	//random seed for sequence of random generators
	unsigned int seed = 1;
	bool binomial = 1;
	//system parameters
	double dt = 1;   //1 unit simulation step time (min) only for record
	double dx = 31.62;	//31.62 (sqrt(1000) for matlab simulation) unit deme length (um) only for record
	int tao = 50;	//(15-25 for T7) lysis time (steps)
	int burst_size = 50;	//(50, 10-400)
	int X = 100;	//max demes in frame
	int N = 100, Np = N * burst_size;//max bacteria, and max phages
	int N0 = 100;		//initial phage numbers in the each deme 
	int Nx = 10;	//initial number of demes which have phages
	int simulation_steps = 20000;	//total simulation steps (total time/dt)
	int visualization_steps = 20;	//every how many steps before each output on the screen
	int labelling_step = 2000;	//how many steps to reach equilibrium before labelling phages, better to specify as integer times of visualization_steps to be able to record the very initial Ht value.
	int starting_step = 0;	//which step does the current simulation begin with (set to be the second last recorded pausing step. (Check checkpoint file index)) (Or at least have to be integer times of Pausing_steps!) Then new output files are created to continue data after that step.
	int pausing_steps = 1000;	//every how many steps to record all the info about the whole system in order to continue simulation later from the pausing step (make use of longer cluster simulation time)
	//phage probs parameters (per timestep)
	double qd = 0;	//(0) death probs
	double qiI = 0.01;	//(try different orders of mag) infecting infected bacteria probs
	double qiB = 0.01;	//(try different orders of mag) infecting uninfected bacteria probs
	double pmigra = 0.2;	//(0.2, 0.1-0.3) migration probability     (move to either side with pmigra/2, with exception of 1st deme which only can move to right with migra/2)


	int i, j, k, a = 0, b = 0, c = 0, w = 0; //to be used in the for loops
	string paraName;

	initfile.open(initfilename, ios::in);
	for (j = 0; j < 19; j++)
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
				std::cout << "starting_step:" << endl << labelling_step << endl;
			}
			else if (paraName == "pausing_steps:")
			{
				initfile >> pausing_steps;
				std::cout << "pausing_steps:" << endl << labelling_step << endl;
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


	


	int labels = X;	//number of initial different gene labels

	//parameters relating to output
	vector <int> P_population(X);	//output of phage population distribution
	//vector <int> IB_population(X);	//output of total bacteria population distribution
	vector <int> B_population(X);	//output of uninfected bacteria population distribution
	vector <int> I_population(X);	//output of infected bacteria population distribution
	vector <vector<double>> label_proportion(labels);//output of proportional distribution of each label within each deme, and initialize to zeroes ([0] corresponding to label 1 etc)
	int tot = 0;	//temporary storage of total phage population at each timestep 
	vector<double> label_frequency(labels);	//each element corresponds to the total frequency of a label withinin the whole population, to be used in the calculation of heterozygosity.
	vector<double> heterozygosity;	//of size (simulation_steps / visualization_steps + 1), array to characterise genetic diversity at the wave front
	int FramePos = 0;	//keeps track of how many demes the frame has moved forward by.
	
	//intermediate parameters
	int total_phage_index = 0, total_phage_size = 0, bacterium_index = 0, phage_index = 0, left_phage_index = 0, right_phage_index = 0;
	int death_number = 0, infect_B_number = 0, infect_I_number = 0, migration_number = 0;
	int direction = 0;
	

	vector <vector <Bacterium*>* > demesB(X);
	vector <vector <int>* > demesP(X);


	//random_device rd;
	mt19937 e{ seed }; // or std::default_random_engine e{rd()};

	
					


    /*Initialization of demes and agents*/

	/*demesB and demesP are two vectors of initial size X storing pointers which point to
	a group of vectors which represent demes of bacteria (objects) and phages (integers) respectively.
	A vector of a deme of bacteria., contains pointers of bacteria objects.*/

	//if the current simulation is a freshly started one instead of from previous pausing steps
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
	}

	//if the current simulation is continued from previous pausing steps
	else
	{
		//read data from checkpointstarting_steps.dat
		loadcheckpoint.open("checkpoint" + to_string(starting_step) + ".dat", ios::in);

		loadcheckpoint >> FramePos;

		int num;	
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
			}
		}
		loadcheckpoint.close();

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
		
	std::cout.precision(2);
	std::cout << "Current simulation step: " << starting_step << endl;


	



	/*Simulation steps*/

	//i: simulation timestep (generation number, cycle number). extracting infomation about the starting_step and begin with the (starting_step + 1)th step.
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


	

		/*die*/ //not currently used

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
					(*((*demesB[j])[bacterium_index])).label = (*demesP[j])[b];
					(*((*demesB[j])[bacterium_index])).infected = true;

					(*((*demesB[j])[bacterium_index])).infectionStep = i;

					//delete phage after infection
					(*demesP[j]).erase((*demesP[j]).begin() + b);
					total_phage_size = total_phage_size - 1;
				}

				//if infecting infected bacteria:
				else if ( (*((*demesB[j])[bacterium_index])).lysed == false)
				{
					//delete phage after infection
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
						demesP.push_back(new vector<int>);
						demesB.push_back(new vector<Bacterium*>);
						for (k = 0; k < N; k++)
						{
							(*demesB[j + 1]).push_back(new Bacterium);	//N bacteria per deme initially
							(*demesB[j + 1])[k]->infected = false;
							(*demesB[j + 1])[k]->label = 0;
							(*demesB[j + 1])[k]->lysed = false;
							(*demesB[j + 1])[k]->infectionStep = 0;
						}



						(*demesP[j + 1]).push_back((*demesP[j])[b]);
						(*demesP[j]).erase((*demesP[j]).begin() + b);

						
						//delete first deme (only at the end in order not to mess up with indexes).
						total_phage_size -= (*demesP[0]).size();

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
					(*demesP[j]).insert((*demesP[j]).end(), burst_size, (*((*demesB[j])[w])).label);
					(*((*demesB[j])[w])).lysed = true;
				}
			}
		}

		/*checkpoint output at pausing_steps*/

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
					checkpoint << (*demesB[j])[k]->label << " " << (*demesB[j])[k]->infected << " " << (*demesB[j])[k]->lysed << " " << (*demesB[j])[k]->infectionStep << " ";
				checkpoint << endl;
			}

			checkpoint.close();
		}

		/*data output at visualization_steps*/

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
						if ((*demesP[j])[k] == w + 1)	//+1 because actual label is greater than index.(start from 0 and 1) 
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