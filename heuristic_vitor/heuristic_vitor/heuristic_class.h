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
		std::vector<timetable_element> time;
	}BASE_timetable;

	BASE_timetable *newTT;


public:
	heuristic_class(void);
	~heuristic_class(void);

	void printHelloWorld(std::ofstream &file);
	void generateBaseTT(std::ofstream &file);
};

