#include "StdAfx.h"
#include "heuristic_class.h"

// Constructor
heuristic_class::heuristic_class(void)
{
	newTT = new BASE_timetable;
	solutionTT = new solutionTimeT;
	minimumTimeTT = new minimumTime;
	minimumTimeTT->AGV=0;
	minimumTimeTT->mission=0;

}

// Destructor
heuristic_class::~heuristic_class(void)
{
}

// ############### FAKE TIME TABLE #########################

void heuristic_class::printHelloWorld(std::ofstream &file)
{
	std::cout<<"HELLO WORLD!!"<<std::endl;
	file << "HELLO WORLD!!";
	return;
}
void heuristic_class::generateBaseTT(void)
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
	//esta parte ser� feita para a fun��o TEA* "aceder"

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
void heuristic_class::printTimeTable(void)
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

int heuristic_class::teastarOffline(int id_robot, int vertex_origem, int vertex_destino)
{
	int mission = vertex_destino;

	int robot_vertex = vertex_origem;

	//for(int agv=0; agv < (newTT->numberOfAGVs); agv++) //check which agv
	//{

	//}
	return newTT->matrixOfTimes[mission][id_robot].totalTime;
}
void heuristic_class::solutionInitialSetup(void)
{

	for(int agv=0; agv < (newTT->numberOfAGVs); agv++)
	{
		for(int mission=0; mission < newTT->numberOfMissions; mission++)
		{
			solutionTT->matrixOfTimes[mission][agv].totalTime = teastarOffline(agv, 0, mission);
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
	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
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
			solutionTT->matrixOfTimes[mission][robot].totalTime = teastarOffline(robot, 0, mission) + initialTime;
			solutionTT->matrixOfTimes[mission][robot].agv.id_agv =  newTT->matrixOfTimes[mission][robot].agv.id_agv;
			solutionTT->matrixOfTimes[mission][robot].agv.initial_time =  initialTime;
			solutionTT->matrixOfTimes[mission][robot].mission =  newTT->matrixOfTimes[mission][robot].mission;
		}

	return;
}
void heuristic_class::printSolutionTable(void)
{
	std::cout<<"printing solution"<<std::endl;

	//printing table header
	std::cout<<"      | ";
	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
		{
			std::cout<<"M("<<mission<<") | ";
		}
	std::cout<<" AVL? |"<<std::endl;
	std::cout<<" MIN  | ";
	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
		{
			std::cout<<" "<<solutionTT->minimumTimeMissions[mission]<<"   | ";
		}
	std::cout<<std::endl;
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

int heuristic_class::getNextTime(void)
{
	int remainingMissions = this->getRemainingMissions();
	int nextTime = 10000000;


	//verifica de 0 at� remaining missions se agv est� livre

	for(int agv=0; agv < (solutionTT->numberOfAGVs + solutionTT->numberOfMissions - remainingMissions); agv++)
	{
		if(solutionTT->selectedAGVs[agv]==true)
		{
			//verifica m�nimo de AGV.initialTime
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
	//conta o n�mero de miss�es restantes
	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
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
	/*for(int agv=0; agv < (solutionTT->numberOfAGVs+currIteration); agv++)
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
	}*/

	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
	{
		if(solutionTT->minimumTimeMissions[mission] < minimumTime && !solutionTT->selectedMissions[mission])
		{
			minimumTimeTT->AGV = solutionTT->minimumTimeAGV[mission];
			minimumTimeTT->mission=mission;
			minimumTime = solutionTT->minimumTimeMissions[mission];
		}
	}


	return minimumTime;
}
int heuristic_class::getMaximumTime(void)
{
	int maximumTime = 0;
	//	solutionTT->selectedAGVs[solutionTT->numberOfAGVs+currIteration-1]=true;
	/*for(int agv=0; agv < (solutionTT->numberOfAGVs+currIteration); agv++)
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
	}*/

	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
	{
		if(solutionTT->minimumTimeMissions[mission] > maximumTime && !solutionTT->selectedMissions[mission])
		{
			minimumTimeTT->AGV = solutionTT->minimumTimeAGV[mission];
			minimumTimeTT->mission=mission;
			maximumTime = solutionTT->minimumTimeMissions[mission];
		}
	}


	return maximumTime;
}
void heuristic_class::updateMinimumTime(void)
{
	for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
	{
		solutionTT->minimumTimeMissions[mission]=100000;
	}

	for(int agv=0; agv < (solutionTT->numberOfAGVs+currIteration); agv++)
	{
		for(int mission=0; mission < solutionTT->numberOfMissions; mission++)
		{
			if(solutionTT->selectedAGVs[agv] && solutionTT->matrixOfTimes[mission][agv].totalTime < solutionTT->minimumTimeMissions[mission])
			{
				solutionTT->minimumTimeMissions[mission] = solutionTT->matrixOfTimes[mission][agv].totalTime;
				solutionTT->minimumTimeAGV[mission] = agv;
			}
		}
	}
}
int heuristic_class::selectTime(void)
{

	currIteration +=1;
	solutionTT->selectedMissions[minimumTimeTT->mission]=true;
	solutionTT->selectedAGVs[minimumTimeTT->AGV]=false;
	solutionTT->selectedAGVs[solutionTT->numberOfAGVs+currIteration-1]=true;

	solutionTT->selectElements.push_back(solutionTT->matrixOfTimes[minimumTimeTT->mission][minimumTimeTT->AGV]);

	int timeOfExecution = solutionTT->matrixOfTimes[minimumTimeTT->mission][minimumTimeTT->AGV].totalTime;
	//std::cout <<"\nMinimum time AGV:"<< minimumTimeTT->AGV;
	//std::cout <<"\nMinimum time mission:"<< minimumTimeTT->mission;
	addTimeElementSolution2(solutionTT->numberOfAGVs+currIteration-1, timeOfExecution); //igual ao TEA*

	return -1;
}

void heuristic_class::printResults(void)
{
	std::vector<timetable_element>::iterator it;
	int i=0;

	for(it=solutionTT->selectElements.begin() ; it < solutionTT->selectElements.end(); it++,i++ )
	{
		std::cout <<"\n   Iteration("<< i <<") M("<<it->mission<<") -  R("<<
			it->agv.id_agv<<") --> t_ini = "<<it->agv.initial_time<<"  |  t_end = "<<it->totalTime;
    }


	return;
}
//##########################################################
void heuristic_class::runHeuristic1(void)
{
	generateBaseTT();
	printTimeTable();



	solutionInitialSetup();  //incluir aqui o TEA*
	printSolutionTable();



	while(getRemainingMissions() >= 1)
	{
		std::cout <<"\n###########   Iteration "<<currIteration<<"   ###########\n";
		updateMinimumTime();

		//std::cout <<"\nMinimum time:"<< getMinimumTime(); //for H1: obtem primeiro o minimo do conjunto dos m�nimos
		std::cout <<"\nMinimum time:"<< getMaximumTime(); //for H2: obtem primeiro o m�ximo do conjunto dos m�nimos

		selectTime();		//incluir aqui o TEA*


		printSolutionTable();

		std::cout <<"\nRemaining Missions:"<< getRemainingMissions();
	}

	printResults();

}
