#include <iostream>
#include <fstream>
#include <sstream>	
#include <array>
#include <vector>
#include <string>

using namespace std;

int main()
{

	int i, j; //to be used in the for loops
	string DirName = "C:/Users/Public/jobarray5/jobs/sim_";
	string initfilename = "/init.txt";
	string paraName;

	ofstream initfile;

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

	for (j = 1; j < 21; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	
	for (j = 21; j < 41; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 20 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.001 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 41; j < 61; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 40<< endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.1 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.1 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 61; j < 81; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 60<< endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.3 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.3 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 81; j < 101; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 80 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.5 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.5 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 101; j < 121; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 100<< endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 10 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 121; j < 141; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j -120<< endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 50 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 141; j < 161; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 140 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 100 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 161; j < 181; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 160 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 300 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 181; j < 201; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j -180 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 5 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 201; j < 221; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 200 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 10 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 221; j < 241; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 220 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 20 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
	for (j = 241; j < 261; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << 20000 << endl;
		initfile << "visualization_steps:" << endl;
		initfile << 20 << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 240 << endl;
		initfile << "binomial:" << endl;
		initfile << 1 << endl;
		initfile << "dt:" << endl;
		initfile << 1 << endl;
		initfile << "dx:" << endl;
		initfile << 31.62 << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 100 << endl;
		initfile << "X:" << endl;
		initfile << 100 << endl;
		initfile << "N:" << endl;
		initfile << 200 << endl;
		initfile << "N0:" << endl;
		initfile << 100 << endl;
		initfile << "Nx:" << endl;
		initfile << 10 << endl;
		initfile << "qd:" << endl;
		initfile << 0 << endl;
		initfile << "qiI:" << endl;
		initfile << 0.01 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.01 << endl;
		initfile << "pmigra:" << endl;
		initfile << 0.2 << endl;

		initfile.close();
	}
}