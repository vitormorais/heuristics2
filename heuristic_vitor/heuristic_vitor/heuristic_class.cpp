#include "StdAfx.h"
#include "heuristic_class.h"


heuristic_class::heuristic_class(void)
{
	newTT = new BASE_timetable;
	solutionTT = new solutionTimeT;
	minimumTimeTT = new minimumTime;
	minimumTimeTT->AGV=0;
	minimumTimeTT->mission=0;
	
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

void heuristic_class::generateBaseTT(std::ofstream &file)
{
	std::cout<<"povoar timetable"<<std::endl;

	addTimeElement(1,1,0,4);
	addTimeElement(1,2,0,8);
	addTimeElement(1,3,0,9);
	addTimeElement(1,4,0,5);
	addTimeElement(1,5,0,11);

	addTimeElement(2,1,0,3);
	addTimeElement(2,2,0,6);
	addTimeElement(2,3,0,14);
	addTimeElement(2,4,0,7);
	addTimeElement(2,5,0,9);

	addTimeElement(3,1,0,8);
	addTimeElement(3,2,0,9);
	addTimeElement(3,3,0,6);
	addTimeElement(3,4,0,6);
	addTimeElement(3,5,0,5);

	//agora tmepos entre Mx's
	//esta parte será feita para a função TEA* "aceder"

	addTimeElement(4,1,0,4);
	addTimeElement(4,2,0,8);
	addTimeElement(4,3,0,9);
	addTimeElement(4,4,0,5);
	addTimeElement(4,5,0,11);

	addTimeElement(5,1,0,4);
	addTimeElement(5,2,0,8);
	addTimeElement(5,3,0,9);
	addTimeElement(5,4,0,5);
	addTimeElement(5,5,0,11);

	addTimeElement(6,1,0,4);
	addTimeElement(6,2,0,8);
	addTimeElement(6,3,0,9);
	addTimeElement(6,4,0,5);
	addTimeElement(6,5,0,11);

	addTimeElement(7,1,0,4);
	addTimeElement(7,2,0,8);
	addTimeElement(7,3,0,9);
	addTimeElement(7,4,0,5);
	addTimeElement(7,5,0,11);

	addTimeElement(8,1,0,4);
	addTimeElement(8,2,0,8);
	addTimeElement(8,3,0,9);
	addTimeElement(8,4,0,5);
	addTimeElement(8,5,0,11);
	
	
	newTT->numberOfAGVs = 3;
	newTT->numberOfMissions = 5;
	
}

void heuristic_class::addTimeElement(int robot, int mission, int initialTime, int totalTime)
{
	timetable_element time_elem;

	newTT->matrixOfTimes[mission-1][robot-1].totalTime = totalTime;
	newTT->matrixOfTimes[mission-1][robot-1].agv.id_agv = robot;
	newTT->matrixOfTimes[mission-1][robot-1].agv.initial_time = initialTime;
	newTT->matrixOfTimes[mission-1][robot-1].mission = mission;

	return;
}

void heuristic_class::printTimeTable(std::ofstream &file)
{
	std::cout<<"printing table"<<std::endl;

	//printing table header
	std::cout<<"     | ";
	for(int mission=1; mission <= newTT->numberOfMissions; mission++)
		{
			std::cout<<"M("<<mission<<") | ";
		}
	std::cout<<std::endl;
	for(int agv=1; agv <= (newTT->numberOfAGVs + 5); agv++)
	{
		std::cout<< "R(" << agv << ") | ";
		for(int mission=1; mission <= newTT->numberOfMissions; mission++)
		{
			std::cout<<" "<< newTT->matrixOfTimes[mission-1][agv-1].totalTime<<"   | ";
		}
		std::cout<<std::endl;
	}

	//file << "HELLO WORLD!!";
	return;
}

//##########################################################

void heuristic_class::solutionInitialSetup(std::ofstream &file)
{
	
	for(int agv=1; agv <= (newTT->numberOfAGVs); agv++)
	{
		for(int mission=1; mission <= newTT->numberOfMissions; mission++)
		{
			solutionTT->matrixOfTimes[mission-1][agv-1].totalTime = newTT->matrixOfTimes[mission-1][agv-1].totalTime;
			solutionTT->matrixOfTimes[mission-1][agv-1].agv.id_agv =  newTT->matrixOfTimes[mission-1][agv-1].agv.id_agv;
			solutionTT->matrixOfTimes[mission-1][agv-1].agv.initial_time =  newTT->matrixOfTimes[mission-1][agv-1].agv.initial_time;
			solutionTT->matrixOfTimes[mission-1][agv-1].mission =  newTT->matrixOfTimes[mission-1][agv-1].mission;
		}
	}

	solutionTT->numberOfAGVs = 3;
	solutionTT->numberOfMissions = 5;

	for(int agv=0; agv < (solutionTT->numberOfAGVs + solutionTT->numberOfMissions); agv++)
	{
		solutionTT->timeOfAGVs[agv] = 0;
		solutionTT->selectedAGVs[agv] = false;
	}
	for(int agv=0; agv < solutionTT->numberOfAGVs; agv++)
	{
		solutionTT->selectedAGVs[agv] = true;
	}
	for(int mission=0; mission<(solutionTT->numberOfMissions); mission++)
	{
		solutionTT->selectedMissions[mission] = false;
	}
	currTime = 0;
	currIteration = 0;

	return;
}
void heuristic_class::addTimeElementSolution(int robot, int mission, int initialTime, int totalTime)
{
	solutionTT->matrixOfTimes[mission-1][robot-1].totalTime = totalTime;
	solutionTT->matrixOfTimes[mission-1][robot-1].agv.id_agv = robot;
	solutionTT->matrixOfTimes[mission-1][robot-1].agv.initial_time = initialTime;
	solutionTT->matrixOfTimes[mission-1][robot-1].mission = mission;

	return;
}
void heuristic_class::printSolutionTable(std::ofstream &file)
{
	std::cout<<"printing solution"<<std::endl;

	//printing table header
	std::cout<<"     | ";
	for(int mission=1; mission <= solutionTT->numberOfMissions; mission++)
		{
			std::cout<<"M("<<mission<<") | ";
		}
	std::cout<<std::endl;
	//printing table body
	for(int agv=1; agv <= (solutionTT->numberOfAGVs); agv++)
	{
		std::cout<< "R(" << agv << ") | ";
		for(int mission=1; mission <= solutionTT->numberOfMissions; mission++)
		{
			std::cout<<" "<< solutionTT->matrixOfTimes[mission-1][agv-1].totalTime<<"   | ";
		}
		std::cout<<std::endl;
	}

	return;
}

//##########################################################

int heuristic_class::getNextTime(std::ofstream &file)
{
	int remainingMissions = this->getRemainingMissions();
	int nextTime = 10000000;

	
	//verifica de 0 até remaining missions se agv está livre
	
	for(int agv=0; agv<(solutionTT->numberOfAGVs + solutionTT->numberOfMissions - remainingMissions); agv++)
	{
		if(solutionTT->selectedAGVs[agv]==true)
		{
			//verifica mínimo de AGV.initialTime
			if(solutionTT->timeOfAGVs[agv] < nextTime)
			 nextTime = solutionTT->timeOfAGVs[agv];
		}
	}


	//updates currTime
	currTime=nextTime;
	return nextTime;
}
int heuristic_class::getRemainingMissions(void)
{
	int remainingMissions = solutionTT->numberOfMissions;
	//conta o número de missões restantes
	for(int mission=0; mission<solutionTT->numberOfMissions; mission++)
	{
		if(solutionTT->selectedMissions[mission] == true)
		{
			remainingMissions--;
		}
	}
	return remainingMissions;
}
int heuristic_class::getMinimumTime(void)
{
	int minimumTime = 100000;
	for(int agv=1; agv <= (solutionTT->numberOfAGVs); agv++)
	{
		for(int mission=1; mission <= solutionTT->numberOfMissions; mission++)
		{
			if(solutionTT->matrixOfTimes[mission-1][agv-1].totalTime < minimumTime)
			{
				minimumTimeTT->AGV=agv;
				minimumTimeTT->mission=mission;
				minimumTime = solutionTT->matrixOfTimes[mission-1][agv-1].totalTime;
			}
		}
	}

	return minimumTime;
}

//##########################################################
void heuristic_class::runHeuristic1(std::ofstream &file)
{
	printHelloWorld(file);
	generateBaseTT(file);
	printTimeTable(file);

	
	solutionInitialSetup(file);
	printSolutionTable(file);
	std::cout <<"\nNext time:"<< getNextTime(file);

	std::cout <<"\nMinimum time:"<< getMinimumTime();


}