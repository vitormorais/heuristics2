#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#define NUM_ROBOTS 5
#define NUM_MISSIONS 9

#define SELECTABLE false
#define SELECTED true

#define NUM_OF_PATHS 2
#define MIN false  //TODO:could be dangerous
#define MAX true

bool const MATRIX_OF_PATHS[NUM_OF_PATHS][NUM_MISSIONS] = {
	   {MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN,   MIN},       //0
	   {MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX,   MAX},       //1

};


float const MATRIX_TIMES_OFFLINE[NUM_MISSIONS][NUM_ROBOTS+NUM_MISSIONS] = {
	{112,   122,   191,   198,   122,   191,   191,   198,   122,   198,   122,   191,   198,    208},       //0
	{97,   108,   177,   184,   108,   177,   177,   184,   108,   184,   108,   177,   184,    193},        //1
	{96,   107,   168,   175,   107,   168,   168,   175,   107,   175,   107,   168,   175,    184},        //2
	{108,   121,   164,   172,   121,   164,   164,   172,   121,   172,   121,   164,   172,    181},       //3
	{116,   123,   175,   183,   123,   175,   175,   183,   123,   183,   123,   175,   183,    194},       //4
	{123,   109,   186,   194,   109,   186,   186,   194,   109,   194,   109,   186,   194,    204},       //5
	{135,   121,   198,   206,   121,   198,   198,   206,   121,   206,   121,   198,   206,    217},       //6
	{145,   131,   207,   216,   131,   207,   207,   216,   131,   216,   131,   207,   216,    226},       //7
	{157,   143,   220,   228,   143,   220,   220,   228,   143,   228,   143,   220,   228,    239},       //8

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

	float l_min_time_miss_value[NUM_MISSIONS];	//array com o tempo m�nimo
	int l_min_time_miss_robot[NUM_MISSIONS];			//array com o agv correspondente ao tempo m�nimo

	float l_max_time_miss_value[NUM_MISSIONS];	//array com o tempo m�nimo
	int l_max_time_miss_robot[NUM_MISSIONS];			//array com o agv correspondente ao tempo m�nimo

	std::vector<element> l_minimumTime;
	std::vector<element> l_maximumTime;

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
	
	//####
	bool missionIsSelectable(int mission);
	bool missionIsSelected(int mission);
	bool robotIsSelectable(int robot);
	bool robotIsSelected(int robot);
	//####

	void updateMaximumTime(void);
	void updateMinimumTime(void);
	void printMaximumArray(void);
	void printMinimumArray(void);

	float getMinimumOfMinimum(void);
	float getMinimumOfMaximum(void);
	float getMaximumOfMinimum(void);
	float getMaximumOfMaximum(void);
	//####

	int getRemainingMissions(void);
	int getMaxResult(void);
	
	int selectTime(void);

	void printResults(void);


	//####
	void runHeuristic1(int path);

};
