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

	addTimeElement(0,0,0,8);
	addTimeElement(0,1,0,9);
	addTimeElement(0,2,0,6);
	addTimeElement(0,3,0,6);
	addTimeElement(0,4,0,5);
	
	addTimeElement(1,0,0,4);
	addTimeElement(1,1,0,8);
	addTimeElement(1,2,0,9);
	addTimeElement(1,3,0,5);
	addTimeElement(1,4,0,11);

	addTimeElement(2,0,0,3);
	addTimeElement(2,1,0,6);
	addTimeElement(2,2,0,14);
	addTimeElement(2,3,0,7);
	addTimeElement(2,4,0,9);

	

	//agora tmepos entre Mx's
	//esta parte será feita para a função TEA* "aceder"

	addTimeElement(3,0,0,4);
	addTimeElement(3,1,0,8);
	addTimeElement(3,2,0,9);
	addTimeElement(3,3,0,5);
	addTimeElement(3,4,0,11);

	addTimeElement(4,0,0,4);
	addTimeElement(4,1,0,8);
	addTimeElement(4,2,0,9);
	addTimeElement(4,3,0,5);
	addTimeElement(4,4,0,11);

	addTimeElement(5,0,0,4);
	addTimeElement(5,1,0,8);
	addTimeElement(5,2,0,9);
	addTimeElement(5,3,0,5);
	addTimeElement(5,4,0,11);

	addTimeElement(6,0,0,4);
	addTimeElement(6,1,0,8);
	addTimeElement(6,2,0,9);
	addTimeElement(6,3,0,5);
	addTimeElement(6,4,0,11);

	addTimeElement(7,0,0,4);
	addTimeElement(7,1,0,8);
	addTimeElement(7,2,0,9);
	addTimeElement(7,3,0,5);
	addTimeElement(7,4,0,11);
	
	
	newTT->numberOfAGVs = 3;
	newTT->numberOfMissions = 5;
	
}

void heuristic_class::addTimeElement(int robot, int mission, int initialTime, int totalTime)
{
	timetable_element time_elem;

	newTT->matrixOfTimes[mission][robot].totalTime = totalTime;
	newTT->matrixOfTimes[mission][robot].agv.id_agv = robot;
	newTT->matrixOfTimes[mission][robot].agv.initial_time = initialTime;
	newTT->matrixOfTimes[mission][robot].mission = mission;

	return;
}

void heuristic_class::printTimeTable(std::ofstream &file)
{
	std::cout<<"printing table"<<std::endl;

	//printing table header
	std::cout<<"     | ";
	for(int mission=0; mission < newTT->numberOfMissions; mission++)
		{
			std::cout<<"M("<<mission<<") | ";
		}
	std::cout<<std::endl;
	for(int agv=0; agv < (newTT->numberOfAGVs + 5); agv++)
	{
		std::cout<< "R(" << agv << ") | ";
		for(int mission=0; mission < newTT->numberOfMissions; mission++)
		{
			std::cout<<" "<< newTT->matrixOfTimes[mission][agv].totalTime<<"   | ";
		}
		std::cout<<std::endl;
	}

	//file << "HELLO WORLD!!";
	return;
}

//##########################################################

void heuristic_class::solutionInitialSetup(std::ofstream &file)
{
	
	for(int agv=0; agv < (newTT->numberOfAGVs); agv++)
	{
		for(int mission=0; mission < newTT->numberOfMissions; mission++)
		{
			solutionTT->matrixOfTimes[mission][agv].totalTime = newTT->matrixOfTimes[mission][agv].totalTime;
			solutionTT->matrixOfTimes[mission][agv].agv.id_agv =  newTT->matrixOfTimes[mission][agv].agv.id_agv;
			solutionTT->matrixOfTimes[mission][agv].agv.initial_time =  newTT->matrixOfTimes[mission][agv].agv.initial_time;
			solutionTT->matrixOfTimes[mission][agv].mission =  newTT->matrixOfTimes[mission][agv].mission;
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
	solutionTT->matrixOfTimes[mission][robot].totalTime = totalTime;
	solutionTT->matrixOfTimes[mission][robot].agv.id_agv = robot;
	solutionTT->matrixOfTimes[mission][robot].agv.initial_time = initialTime;
	solutionTT->matrixOfTimes[mission][robot].mission = mission;

	return;
}
void heuristic_class::addTimeElementSolution2(int robot, int initialTime)
{
	//	std::cout <<"\ninitialTime:"<< initialTime;

	for(int mission=0; mission < newTT->numberOfMissions; mission++)
		{
			solutionTT->matrixOfTimes[mission][robot].totalTime = newTT->matrixOfTimes[mission][robot].totalTime + initialTime;
			solutionTT->matrixOfTimes[mission][robot].agv.id_agv =  newTT->matrixOfTimes[mission][robot].agv.id_agv;
			solutionTT->matrixOfTimes[mission][robot].agv.initial_time =  initialTime;
			solutionTT->matrixOfTimes[mission][robot].mission =  newTT->matrixOfTimes[mission][robot].mission;
		}
	
	return;
}
void heuristic_class::printSolutionTable(std::ofstream &file)
{
	std::cout<<"printing solution"<<std::endl;

	//printing table header
	std::cout<<"      | ";
	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
		{
			std::cout<<"M("<<mission<<") | ";
		}
	std::cout<<" AVL? |"<<std::endl;
	//printing table body
	for(int agv=0; agv < (solutionTT->numberOfAGVs+currIteration); agv++)
	{
		std::cout<< "R(" << agv << ") "<<solutionTT->matrixOfTimes[0][agv].agv.initial_time<<"| ";
		for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
		{
			std::cout<<" "<< solutionTT->matrixOfTimes[mission][agv].totalTime<<"   | ";
		}
		std::cout<<" "<<solutionTT->selectedAGVs[agv]<<std::endl;
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
	//	solutionTT->selectedAGVs[solutionTT->numberOfAGVs+currIteration-1]=true;
	for(int agv=0; agv < (solutionTT->numberOfAGVs+currIteration); agv++)
	{
		for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
		{
			std::cout <<"*";
			if(solutionTT->matrixOfTimes[mission][agv].totalTime < minimumTime && solutionTT->selectedAGVs[agv] && !solutionTT->selectedMissions[mission])
			{
				minimumTimeTT->AGV=agv;
				minimumTimeTT->mission=mission;
				minimumTime = solutionTT->matrixOfTimes[mission][agv].totalTime;
			}
		}
	}

	return minimumTime;
}
int heuristic_class::selectTime(void)
{
	
	currIteration +=1;
	solutionTT->selectedMissions[minimumTimeTT->mission]=true;
	solutionTT->selectedAGVs[minimumTimeTT->AGV]=false;
	solutionTT->selectedAGVs[solutionTT->numberOfAGVs+currIteration]=true;

	solutionTT->selectElements.push_back(solutionTT->matrixOfTimes[minimumTimeTT->mission][minimumTimeTT->AGV]);
	
	int timeOfExecution = solutionTT->matrixOfTimes[minimumTimeTT->mission][minimumTimeTT->AGV].totalTime;
	//std::cout <<"\nMinimum time AGV:"<< minimumTimeTT->AGV;
	//std::cout <<"\nMinimum time mission:"<< minimumTimeTT->mission;
	addTimeElementSolution2(solutionTT->numberOfAGVs+currIteration-1, timeOfExecution); //igual ao TEA*

	return -1;
}

//##########################################################
void heuristic_class::runHeuristic1(std::ofstream &file)
{
	printHelloWorld(file);
	generateBaseTT(file);
	printTimeTable(file);

	
	solutionInitialSetup(file);
	printSolutionTable(file);

	std::cout <<"\n###########   Iteration 1   ###########\n";

	std::cout <<"\nNext time:"<< getNextTime(file);

	std::cout <<"\nMinimum time:"<< getMinimumTime();

	selectTime();


	printSolutionTable(file);

	std::cout <<"\n###########   Iteration 2   ###########\n";

	std::cout <<"\nNext time:"<< getNextTime(file);

	std::cout <<"\nMinimum time:"<< getMinimumTime();

	selectTime();


	printSolutionTable(file);

	std::cout <<"\n###########   Iteration 3   ###########\n";

	std::cout <<"\nNext time:"<< getNextTime(file);
	std::cout <<"\nMinimum time:"<< getMinimumTime();
	selectTime();
	printSolutionTable(file);

	std::cout <<"\n###########   Iteration 4   ###########\n";

	std::cout <<"\nNext time:"<< getNextTime(file);
	std::cout <<"\nMinimum time:"<< getMinimumTime();
	selectTime();
	printSolutionTable(file);

	std::cout <<"\n###########   Iteration 5   ###########\n";

	std::cout <<"\nNext time:"<< getNextTime(file);
	std::cout <<"\nMinimum time:"<< getMinimumTime();
	selectTime();
	printSolutionTable(file);

}