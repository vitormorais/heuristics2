#include "StdAfx.h"
#include "heuristic_class.h"


heuristic_class::heuristic_class(void)
{
	newTT = new BASE_timetable;
}


heuristic_class::~heuristic_class(void)
{
}

void heuristic_class::generateBaseTT(std::ofstream &file)
{
	std::cout<<"starting TT"<<std::endl;
	
}

void heuristic_class::printHelloWorld(std::ofstream &file)
{
	std::cout<<"HELLO WORLD!!"<<std::endl;
	file << "HELLO WORLD!!";
	return;
}