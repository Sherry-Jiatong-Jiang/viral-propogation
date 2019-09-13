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
	string Dir1 = "D:/jobarray14 retrieved/jobs/sim_";
	string Dir2 = "D:/jobarray14 retrieved/jobs/";


	for (int N = 1; N < 21; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim1-20/sim0H_" + to_string(N) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim1-20/sim0F2_" + to_string(N) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim1-20/sim0P_" + to_string(N) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim1-20/sim0L_" + to_string(N) + ".dat");
	}
	for (int N = 21; N < 41; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim21-40/sim0H_" + to_string(N - 20) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim21-40/sim0F2_" + to_string(N - 20) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim21-40/sim0P_" + to_string(N - 20) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim21-40/sim0L_" + to_string(N - 20) + ".dat");
	}
	for (int N = 41; N < 61; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim41-60/sim0H_" + to_string(N - 40) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim41-60/sim0F2_" + to_string(N - 40) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim41-60/sim0P_" + to_string(N - 40) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim41-60/sim0L_" + to_string(N - 40) + ".dat");
	}
	for (int N = 61; N < 81; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim61-80/sim0H_" + to_string(N - 60) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim61-80/sim0F2_" + to_string(N - 60) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim61-80/sim0P_" + to_string(N - 60) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim61-80/sim0L_" + to_string(N - 60) + ".dat");
	}

	for (int N = 81; N < 101; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim81-100/sim0H_" + to_string(N - 80) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim81-100/sim0F2_" + to_string(N - 80) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim81-100/sim0P_" + to_string(N - 80) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim81-100/sim0L_" + to_string(N - 80) + ".dat");
	}

	for (int N = 101; N < 121; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim101-120/sim0H_" + to_string(N - 100) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim101-120/sim0F2_" + to_string(N - 100) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim101-120/sim0P_" + to_string(N - 100) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim101-120/sim0L_" + to_string(N - 100) + ".dat");
	}

	for (int N = 121; N < 141; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim121-140/sim0H_" + to_string(N - 120) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim121-140/sim0F2_" + to_string(N - 120) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim121-140/sim0P_" + to_string(N - 120) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim121-140/sim0L_" + to_string(N - 120) + ".dat");
	}

	for (int N = 141; N < 161; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim141-160/sim0H_" + to_string(N - 140) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim141-160/sim0F2_" + to_string(N - 140) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim141-160/sim0P_" + to_string(N - 140) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim141-160/sim0L_" + to_string(N - 140) + ".dat");
	}

	for (int N = 161; N < 181; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim161-180/sim0H_" + to_string(N - 160) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim161-180/sim0F2_" + to_string(N - 160) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim161-180/sim0P_" + to_string(N - 160) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim161-180/sim0L_" + to_string(N - 160) + ".dat");
	}

	for (int N = 181; N < 201; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim181-200/sim0H_" + to_string(N - 180) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim181-200/sim0F2_" + to_string(N - 180) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim181-200/sim0P_" + to_string(N - 180) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim181-200/sim0L_" + to_string(N - 180) + ".dat");
	}
	for (int N = 201; N < 221; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim201-220/sim0H_" + to_string(N - 200) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim201-220/sim0F2_" + to_string(N - 200) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim201-220/sim0P_" + to_string(N - 200) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim201-220/sim0L_" + to_string(N - 200) + ".dat");
	}

	for (int N = 221; N < 241; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim221-240/sim0H_" + to_string(N - 220) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim221-240/sim0F2_" + to_string(N - 220) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim221-240/sim0P_" + to_string(N - 220) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim221-240/sim0L_" + to_string(N - 220) + ".dat");
	}

	for (int N = 241; N < 261; N++)
	{
		filesystem::copy(Dir1 + to_string(N) + "/sim0H.dat", Dir2 + "sim241-260/sim0H_" + to_string(N - 240) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0F2.dat", Dir2 + "sim241-260/sim0F2_" + to_string(N - 240) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0P.dat", Dir2 + "sim241-260/sim0P_" + to_string(N - 240) + ".dat");
		filesystem::copy(Dir1 + to_string(N) + "/sim0L.dat", Dir2 + "sim241-260/sim0L_" + to_string(N - 240) + ".dat");
	}


	
}