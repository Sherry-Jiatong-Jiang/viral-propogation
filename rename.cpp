#include <iostream>
#include <fstream>
#include <sstream>	
#include <array>
#include <vector>
#include <string>
#include <filesystem>
#include <stdio.h>

using namespace std;


int main()
{

	string DirName = "C:/Users/Public/jobarray17/jobs/sim_";
	string initfilename = "/init.txt";
	string paraName;

	ofstream initfile;

	for (int N = 41; N < 61; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim41-60/sim0H_" + to_string(N - 40) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim41-60/sim0F2_" + to_string(N - 40) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim41-60/sim0P_" + to_string(N - 40) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim41-60/sim0L_" + to_string(N - 40) + ".dat");
	}
	for (int N = 61; N < 81; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim61-80/sim0H_" + to_string(N - 60) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim61-80/sim0F2_" + to_string(N - 60) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim61-80/sim0P_" + to_string(N - 60) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim61-80/sim0L_" + to_string(N - 60) + ".dat");
	}

	for (int N = 81; N < 101; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim81-100/sim0H_" + to_string(N - 80) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim81-100/sim0F2_" + to_string(N - 80) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim81-100/sim0P_" + to_string(N - 80) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim81-100/sim0L_" + to_string(N - 80) + ".dat");
	}

	for (int N = 101; N < 121; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim101-120/sim0H_" + to_string(N - 100) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim101-120/sim0F2_" + to_string(N - 100) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim101-120/sim0P_" + to_string(N - 100) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim101-120/sim0L_" + to_string(N - 100) + ".dat");
	}

	for (int N = 121; N < 141; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim121-140/sim0H_" + to_string(N - 120) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim121-140/sim0F2_" + to_string(N - 120) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim121-140/sim0P_" + to_string(N - 120) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim121-140/sim0L_" + to_string(N - 120) + ".dat");
	}

	for (int N = 141; N < 161; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim141-160/sim0H_" + to_string(N - 140) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim141-160/sim0F2_" + to_string(N - 140) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim141-160/sim0P_" + to_string(N - 140) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim141-160/sim0L_" + to_string(N - 140) + ".dat");
	}

	for (int N = 161; N < 181; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim161-180/sim0H_" + to_string(N - 160) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim161-180/sim0F2_" + to_string(N - 160) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim161-180/sim0P_" + to_string(N - 160) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim161-180/sim0L_" + to_string(N - 160) + ".dat");
	}

	for (int N = 181; N < 201; N++)
	{
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0H.dat", "D:/jobarray10 retrieved/jobs/sim181-200/sim0H_" + to_string(N - 180) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0F2.dat", "D:/jobarray10 retrieved/jobs/sim181-200/sim0F2_" + to_string(N - 180) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0P.dat", "D:/jobarray10 retrieved/jobs/sim181-200/sim0P_" + to_string(N - 180) + ".dat");
		filesystem::copy("D:/jobarray10 retrieved/jobs/sim_" + to_string(N) + "/sim0L.dat", "D:/jobarray10 retrieved/jobs/sim181-200/sim0L_" + to_string(N - 180) + ".dat");
	}


	
}