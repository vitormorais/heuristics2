#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

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
    void bestImprovement(void);


private:

    std::vector<planning> starting_plan_;
    std::vector<neighbor> list_of_neighbors_;

    void loadStartingPlan(std::vector<planning> starting_plan);
    std::vector<planning> swap1to1(std::vector<planning>, int first_position, int second_position);
    void printPlan(std::vector<planning> input_plan);


};