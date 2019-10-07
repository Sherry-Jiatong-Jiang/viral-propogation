#include <iostream>
#include <fstream>
#include <sstream>	
#include <array>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string paraName;
	ofstream initfile; 
	int i, j;
	
	
	
	//Change section of path before "/jobs/sim_"
	//string DirName = "C:/Users/Public/jobarray50/jobs/sim_";
	string DirName = "D:/sim resources/jobarray50/jobs/sim_";
	string initfilename = "/init.txt";
	

	//Change common parameters collectively:	
	int N = 200;
	int max_bacteria = 1000;
	int infection_mode = 0;
	int migration_mode = 0;
	int simulation_steps = 500000;
	
	//The following parameters can usually be left unchanged
	int visualization_steps = 20;
	bool binomial = 1;
	double dt = 1;
	double dx = 31.62;
	int X = 100;
	int N0 = 100;
	int Nx = 10;
	int qd = 0;
	double pmigra = 0.2;

	

	//Change variable parameters individually:

	for (j = 1; j < 21; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	
	for (j = 21; j < 41; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 20 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.000001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.000001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 41; j < 61; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 40<< endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.0001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.0001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 61; j < 81; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 60<< endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.0003 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.0003 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 81; j < 101; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 80 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.0005 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.0005 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 101; j < 121; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 100<< endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 10 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 121; j < 141; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j -120<< endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 50 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 141; j < 161; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 140 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 100 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 161; j < 181; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 160 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 300 << endl;
		initfile << "burst_size:" << endl;
		initfile << 50 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 181; j < 201; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j -180 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 5 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 201; j < 221; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 200 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 10 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 221; j < 241; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 2000 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 220 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 20 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
	for (j = 241; j < 261; j++)
	{
		initfile.open(DirName + to_string(j) + initfilename, ios::out);

		initfile << "starting_step:" << endl;
		initfile << 0 << endl;
		initfile << "simulation_steps:" << endl;
		initfile << simulation_steps << endl;
		initfile << "visualization_steps:" << endl;
		initfile << visualization_steps << endl;
		initfile << "pausing_steps:" << endl;
		initfile << 500 << endl;
		initfile << "labelling_step:" << endl;
		initfile << 2000 << endl;
		initfile << "seed:" << endl;
		initfile << j - 240 << endl;
		initfile << "binomial:" << endl;
		initfile << binomial << endl;
		initfile << "dt:" << endl;
		initfile << dt << endl;
		initfile << "dx:" << endl;
		initfile << dx << endl;
		initfile << "tao:" << endl;
		initfile << 20 << endl;
		initfile << "burst_size:" << endl;
		initfile << 100 << endl;
		initfile << "X:" << endl;
		initfile << X << endl;
		initfile << "N:" << endl;
		initfile << N << endl;
		initfile << "N0:" << endl;
		initfile << N0 << endl;
		initfile << "Nx:" << endl;
		initfile << Nx << endl;
		initfile << "qd:" << endl;
		initfile << qd << endl;
		initfile << "qiI:" << endl;
		initfile << 0.00001 << endl;
		initfile << "qiB:" << endl;
		initfile << 0.00001 << endl;
		initfile << "pmigra:" << endl;
		initfile << pmigra << endl;
		initfile << "max_bacteria:" << endl;
		initfile << max_bacteria << endl;
		initfile << "infection_mode:" << endl;
		initfile << infection_mode << endl;
		initfile << "migration_mode:" << endl;
		initfile << migration_mode << endl;

		initfile.close();
	}
}