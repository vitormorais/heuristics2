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

	neighbor  current_plan;
	current_plan.plan = this->starting_plan_;
	current_plan.plan_time =9;

   // std::vector<planning> plan_swapped;
	std::vector<neighbor> list_of_neighbors;

	for(int i=0; i<1; i++){

		list_of_neighbors = generateListOfNeighbors(current_plan);
		//printNeighborhood(list_of_neighbors);
		list_of_neighbors = updateTimeOfNeighbors(list_of_neighbors);  	//note: pass the list of neighbours by reference or create a listOfNeighbours as an atribute
		//printNeighborhood(list_of_neighbors);

		int min_time_neighbor = getMinPlanningTime(list_of_neighbors);

		std::cout<< "# "<<i<<" minTime" <<min_time_neighbor<<std::endl;

		current_plan = list_of_neighbors[min_time_neighbor];  //jumps to best neighbor
	}

	printPlan(current_plan.plan);


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

void metaheuristic_class::printNeighborhood(std::vector<neighbor> input_list_of_neighbors){
	
	for (size_t i = 0; i < input_list_of_neighbors.size(); i++) {

        //ROS_INFO_STREAM("[TEA*] [MetaHeuristic Class] R" << input_plan[i].robot_id << " M" << input_plan[i].mission_id << " (Vertex " << input_plan[i].mission_vertex << ")");
		std::cout << "[TEA*] [MetaHeuristic Class] #" << i << " time " << input_list_of_neighbors[i].plan_time << std::endl;

    }
}

std::vector<neighbor> metaheuristic_class::generateListOfNeighbors( neighbor inputNeighbor){

	std::vector<neighbor> list_of_neighbors;
	
	for(int first_plan=0; first_plan < NUM_MISSIONS; first_plan++){
		for(int second_plan = first_plan+1; second_plan < NUM_MISSIONS; second_plan++){
			    std::cout << "swapping "<<first_plan<<" with "<<second_plan<<"\n";
				neighbor n;
				n.plan = swap1to1(inputNeighbor.plan, first_plan, second_plan);
				n.plan_time = 11; //TODO: verify value
				//printPlan(n2.plan);
				list_of_neighbors.push_back(n);
		}
	}
	//list_of_neighbors.push_back(n2);
	return list_of_neighbors;
}

std::vector<neighbor> metaheuristic_class::updateTimeOfNeighbors(std::vector<neighbor> input_list){
	
	//TODO: pass the list of neighbours by reference
	//TODO: add incumbent pan time;
	//TODO: add flag for first improvement

	std::vector<neighbor> return_list;
	return_list = input_list;

	for (size_t i = 0; i < return_list.size(); i++) {
		//get time of a plan
		return_list[i].plan_time  =  getOfflinePlanningTime(return_list[i].plan);
		
		//for first improvement, if plan time is lower that a memory variable, then preak and jumps to that neighbour
    }
	
	return return_list;
}

int metaheuristic_class::getMinPlanningTime(std::vector<neighbor> input_list){

	
	//TODO: check if input list have plans  (?)
	float min_time = input_list[0].plan_time;
	int min_time_position = 0;

	for (size_t i = 0; i < input_list.size(); i++) {
		//get time of a plan
		if (input_list[i].plan_time < min_time ){
			min_time = input_list[i].plan_time;
			min_time_position = i;
		}
		
		//for first improvement, if plan time is lower that a memory variable, then preak and jumps to that neighbour
    }
	
	return min_time_position;
}

float metaheuristic_class::getOfflinePlanningTime(std::vector<planning> input_plan){
	

	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //value between 0 and 1
	
	return (r * static_cast <float> (100));
}