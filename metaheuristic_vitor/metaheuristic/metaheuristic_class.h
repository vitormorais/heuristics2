#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>

#define NUM_ROBOTS 5
#define NUM_MISSIONS 9

typedef struct{
      int robot_id;
 	    int mission_id;
      int mission_vertex;
 }planning;

typedef struct{
    std::vector<planning> plan;
    float plan_time;
}neighbor;



///////////
// CLASS //
///////////



class metaheuristic_class
{
public:

	metaheuristic_class(std::vector<planning> starting_plan);
	~metaheuristic_class(void);
    void bestImprovement(bool improvement_flag);
	void simulatedAnnealing(void);


private:

    std::vector<planning> starting_plan_;
    std::vector<neighbor> list_of_neighbors_;

    void loadStartingPlan(std::vector<planning> starting_plan);
    std::vector<planning> swap1to1(std::vector<planning>, int first_position, int second_position);
	std::vector<neighbor> generateListOfNeighbors( neighbor inputNeighbor);
	std::vector<neighbor> updateTimeOfNeighbors(std::vector<neighbor> input_list, bool improvement_flag,  neighbor inputNeighbor, int current_iteration);

	float getOfflinePlanningTime(std::vector<planning> input_plan, int current_iteration);
	int getMinPlanningTime(std::vector<neighbor> input_list);

    void printPlan(std::vector<planning> input_plan);
	void printNeighborhood(std::vector<neighbor> input_list_of_neighbors);

	int auxGetExpon(int iter);

	int simulated_iteration, simulated_temperature;

};