#include "StdAfx.h"
#include "heuristic_class.h"


heuristic_class::heuristic_class(void)
{
}


heuristic_class::~heuristic_class(void)
{
}


void heuristic_class::printHelloWorld(std::ofstream &file)
{
	std::cout<<"HELLO WORLD!!"<<std::endl;
	file << "HELLO WORLD!!";
	return;
}