#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>


class heuristic_class
{
private:
	typedef struct{
	int id_mission;
	//int x_position;
	//int y_position;
	//int theta;
	int m_vertex;
	} Mission;

	typedef struct{
	int id_robot;
	//int x_position;
	//int y_position;
	//int theta;
	int r_vertex;
	} Robot;

	typedef struct{
	int id_agv;
	//Robot robot;   //comentado, o robot aqpenas � identifacdo com um n�mero
	int initial_time;
	} AGV;

	typedef struct{
		//Mission Mx;  // a miss�o apenas � identificada com um n�mero nesta fase
		//AGV AGVx;
		int mission;
		AGV agv;
		int totalTime;    //este n�mero ser� gerado pelo TEA*, que analiza a (Mission Mx, AGV AGVx)
	}timetable_element;

	typedef struct{
		timetable_element matrixOfTimes[5][8];
		int numberOfMissions;
		int numberOfAGVs;
	}BASE_timetable;

	BASE_timetable *newTT;

	/*typedef struct{
		timetable_element 
	}selectedSubset;
	*/

	typedef struct{
		timetable_element matrixOfTimes[5][8];
		std::vector<timetable_element> selectElements;
		bool selectedMissions[5];
		int minimumTimeMissions[5];
		int minimumTimeAGV[5];
		int timeOfAGVs[8];
		bool selectedAGVs[8];
		int numberOfMissions;
		int numberOfAGVs;
	}solutionTimeT;

	solutionTimeT *solutionTT;

	//variables
	int currTime;
	int currIteration;

	typedef struct{
		int AGV;
		int mission;
	}minimumTime;
	minimumTime *minimumTimeTT;

public:
	heuristic_class(void);
	~heuristic_class(void);

	void printHelloWorld(std::ofstream &file);
	void generateBaseTT(void);
	void addTimeElement(int robot, int mission, int initialTime, int totalTime);
	void printTimeTable(void);
	//####
	int teastarOffline(int id_robot, int vertex_origem, int vertex_destino);
	void solutionInitialSetup(void);
	void addTimeElementSolution(int robot, int mission, int initialTime, int totalTime);  //equal to timeElement but for solution
	void addTimeElementSolution2(int robot, int initialTime);  //for upcoming
	void printSolutionTable(void);
	//void printSolutionTable2(void);
	//####
	int getNextTime(void);
	int getRemainingMissions(void);
	int getMinimumTime(void);
	int getMaximumTime(void);
	void updateMinimumTime(void);
	int selectTime(void);

	void printResults(void);

	//####
	void runHeuristic1(void);
};