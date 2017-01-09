#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#define NUM_ROBOTS 3
#define NUM_MISSIONS 5
//int const NUM_ROBOTS = 3;
//int const NUM_MISSIONS = 5;

//////////////////////////////////////////////

typedef struct{
    int id;
    int vertex;
}robot;

typedef struct{
    int id;
    int vertex;
}mission;

typedef struct{
    int robot;
    int mission;
    float initial_time;
    float mission_time;
}element;

typedef struct{
    element matrixOfElements[NUM_MISSIONS][NUM_ROBOTS+NUM_MISSIONS];
	std::vector<element> selectElements;
	
	bool selectedMissions[NUM_MISSIONS];
	float minimumTimeMissions[NUM_MISSIONS];	//array com o tempo mínimo 
	int minimumTimeAGV[NUM_MISSIONS];			//array com o agv correspondente ao tempo mínimo
	int timeOfAGVs[NUM_MISSIONS+NUM_ROBOTS];
	bool selectedAGVs[NUM_MISSIONS+NUM_ROBOTS];
	
}solution;


class heuristic_class
{
private:

    // int NUM_ROBOTS = 3;
    // int NUM_MISSIONS = 5;

    std::vector<robot> l_robots;
    std::vector<mission> l_missions;
    solution initial_solution;

	float offlineTime;
	element selectedElement;

	int currIteration;


public:
	heuristic_class(void);
	~heuristic_class(void);

	

	//float getTEAstarOnline(int robot, int vertex_origin, int vertex_end);
	float getTEAstarOffline(int robot, int vertex_origin, int vertex_end);
    void initializeListOfRobots(void);
    void initializeListOfMissions(void);
    void solutionInitialSetup(void);
    void printSolutionTable(void);
	int getNextTime(void);
	void addElementAtEnd(int end_position, float mission_time);






	int getRemainingMissions(void);
	float getMinimumTime(void);
	float getMaximumTime(void);
	void updateMinimumTime(void);
	int selectTime(void);

	void printResults(void);
	void printMinimumArray(void);

	//####
	void runHeuristic1(void);
};
