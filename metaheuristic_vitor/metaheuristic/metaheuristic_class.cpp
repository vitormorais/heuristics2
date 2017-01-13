#include "StdAfx.h"
#include "metaheuristic_class.h"

///////////////////
// CLASS METHODS //
///////////////////


// Constructor
metaheuristic_class::metaheuristic_class(std::vector<planning> starting_plan) { loadStartingPlan(starting_plan); }
// Destructor
metaheuristic_class::~metaheuristic_class(void) {}

void metaheuristic_class::loadStartingPlan(std::vector<planning> starting_plan) { this->starting_plan_ = starting_plan; }

void metaheuristic_class::bestImprovement(void) {

    //ROS_WARN_STREAM("STARTING PLAN");
    std::cout << "STARTING PLAN\n";

	printPlan(this->starting_plan_);

    std::vector<planning> plan_swapped;

    plan_swapped = swap1to1(this->starting_plan_, 0, 1);

    //ROS_WARN_STREAM("SWAPPED PLAN");
	
    std::cout << "SWAPPED PLAN\n";
    printPlan(plan_swapped);

}

std::vector<planning> metaheuristic_class::swap1to1(std::vector<planning> input_plan, int fp, int sp) {

    std::vector<planning> plan_swapped = input_plan;

    // No Changes Needed
    if (fp == sp) { return plan_swapped; }

    if (fp >= input_plan.size() || sp >= input_plan.size()) {
        //ROS_ERROR_STREAM("[TEA*] [MetaHeuristic Class] Impossible to Swap! First or Second Position higher than " << (input_plan.size() - 1) );
		std::cout << "[TEA*] [MetaHeuristic Class] Impossible to Swap! First or Second Position higher than " << (input_plan.size() - 1) << std::endl;

        return plan_swapped;
    }

    planning first_plan = input_plan[fp];
    planning second_plan = input_plan[sp];

    plan_swapped[fp].mission_id = second_plan.mission_id;
    plan_swapped[fp].mission_vertex = second_plan.mission_vertex;

    plan_swapped[sp].mission_id = first_plan.mission_id;
    plan_swapped[sp].mission_vertex = first_plan.mission_vertex;
	return plan_swapped;

}

void metaheuristic_class::printPlan(std::vector<planning> input_plan) {

    for (size_t i = 0; i < input_plan.size(); i++) {

        //ROS_INFO_STREAM("[TEA*] [MetaHeuristic Class] R" << input_plan[i].robot_id << " M" << input_plan[i].mission_id << " (Vertex " << input_plan[i].mission_vertex << ")");
		std::cout << "[TEA*] [MetaHeuristic Class] R" << input_plan[i].robot_id << " M" << input_plan[i].mission_id << " (Vertex " << input_plan[i].mission_vertex << ")" << std::endl;

    }

}
