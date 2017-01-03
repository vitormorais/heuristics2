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
	int x_position;
	int y_position;
	int theta;
	} Mission;

	typedef struct{
	int id_robot;
	int x_position;
	int y_position;
	int theta;
	} Robot;

	typedef struct{
	int id_agv;
	//Robot robot;   //comentado, o robot aqpenas é identifacdo com um número
	int initial_time;
	} AGV;

	typedef struct{
		//Mission Mx;  // a missão apenas é identificada com um número nesta fase
		//AGV AGVx;
		int mission;
		AGV agv;
		int totalTime;    //este número será gerado pelo TEA*, que analiza a (Mission Mx, AGV AGVx)
	}timetable_element;

	typedef struct{
		timetable_element matrixOfTimes[5][8];
		int numberOfMissions;
		int numberOfAGVs;
	}BASE_timetable;

	BASE_timetable *newTT;


public:
	heuristic_class(void);
	~heuristic_class(void);

	void printHelloWorld(std::ofstream &file);
	void generateBaseTT(std::ofstream &file);
	void addTimeElement(int robot, int mission, int initialTime, int totalTime);
	void printTimeTable(std::ofstream &file);
};