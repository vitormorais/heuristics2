// heuristic_vitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "heuristic_class.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Windows.h"
#include <fstream>
#include <vector>


int _tmain(int argc, _TCHAR* argv[])
{
	
	std::ofstream filetowrite;

	
	filetowrite.open("..\\HEURISTIC.txt", std::ios_base::app);
	filetowrite << "########  V1  #######\n";

	heuristic_class *heuristic;

	heuristic = new heuristic_class();

	heuristic->printHelloWorld(filetowrite);
	heuristic->generateBaseTT(filetowrite);


	
	delete heuristic;
	filetowrite.close();

	std::cout<<"\n\nend\npress any key to exit"<<std::endl;
	getchar();


	return 0;
}

