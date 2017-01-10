#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#define NUM_ROBOTS 5
#define NUM_MISSIONS 9

float const MATRIX_TIMES_OFFLINE[NUM_MISSIONS][NUM_ROBOTS] = {
	{112, 122, 191, 198, 208},  //0
	{97,  108, 177, 184, 193},  //1
	{96,  107, 168, 175, 184},  //2
	{108, 121, 164, 172, 181},  //3
	{116, 123, 175, 183, 194},  //4
	{123, 109, 186, 194, 204},  //5
	{135, 121, 198, 206, 217},  //6
	{145, 131, 207, 216, 226},  //7
	{157, 143, 220, 228, 239},  //8
};

//R0 (0)|     112    |    97       |    96       |    108     |    116     |    123     |    135     |    145     |    157     |
//R1 (0)|     122    |    108     |    107     |    121     |    123     |    109     |    121     |    131     |    143     |
//R2 (0)|     191    |    177     |    168     |    164     |    175     |    186     |    198     |    207     |    220     |
//R3 (0)|     198    |    184     |    175     |    172     |    183     |    194     |    206     |    216     |    228     |
//R4 (0)|     208    |    193     |    184     |    181     |    194     |    204     |    217     |    226     |    239     |
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
	bool selectedRobots[NUM_MISSIONS+NUM_ROBOTS];

	float minimumTimeMissions[NUM_MISSIONS];	//array com o tempo mínimo
	int minimumTimeAGV[NUM_MISSIONS];			//array com o agv correspondente ao tempo mínimo
	int timeOfAGVs[NUM_MISSIONS+NUM_ROBOTS];    // TODO: Erase this variable!!!

}solution;


class heuristic_class
{
private:

    // int NUM_ROBOTS = 3;
    // int NUM_MISSIONS = 5;

  //  ros::NodeHandlePtr node_handle_;
  //  ros::ServiceClient client_;

    std::vector<robot> l_robots;
    std::vector<mission> l_missions;
    solution initial_solution;

	float offlineTime;
	element selectedElement;

	int currIteration;


public:

	heuristic_class(void);
	~heuristic_class(void);

  //  void setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle);

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
