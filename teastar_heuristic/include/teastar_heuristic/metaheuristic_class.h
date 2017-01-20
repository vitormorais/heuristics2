#include<ros/ros.h>
#include "teastar_msgs/GetTEAstarPlanTime.h"
#include "teastar_msgs/Mission.h"
#include <algorithm>
#include <math.h>
#include <fstream>

#define BI_FLAG true
#define FI_FLAG false

#define HAS_NEW_MIN true
#define NOT_NEW_MIN false

typedef struct{
    std::vector<planning> plan;
    float plan_time;
}neighbor;

// typedef struct{
//      int robot_id;
// 	    int mission_id;
//      int mission_vertex;
// }planning;

///////////
// CLASS //
///////////

class metaheuristic_class
{
public:

	metaheuristic_class(std::vector<planning> starting_plan);
	~metaheuristic_class(void);
    void setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle);
    void bestImprovement(bool improvement_flag);
    void simulatedAnnealing(void);

private:

    ros::NodeHandlePtr node_handle_;
    ros::ServiceClient client_;

    std::vector<planning> starting_plan_;
    std::vector<neighbor> list_of_neighbors_;

    void loadStartingPlan(std::vector<planning> starting_plan);
    std::vector<planning> swap1to1(std::vector<planning>, int first_position, int second_position);
    void printPlan(std::vector<planning> input_plan);

    std::vector<neighbor> generateListOfNeighbors( neighbor inputNeighbor);
    std::vector<neighbor> updateTimeOfNeighbors(std::vector<neighbor> input_list, bool improvement_flag,  neighbor inputNeighbor, int current_iteration);
    int getMinPlanningTime(std::vector<neighbor> input_list, neighbor incumbent_solution);

    float getOnlinePlanningTime(std::vector<planning> input_plan);

    int simulated_iteration, simulated_temperature;
    bool new_minimum_;

    float auxGetExpon(int iter);

};

///////////////////
// CLASS METHODS //
///////////////////

// Constructor
metaheuristic_class::metaheuristic_class(std::vector<planning> starting_plan) { loadStartingPlan(starting_plan); }

// Destructor
metaheuristic_class::~metaheuristic_class(void) {}

// ROS Configuration Setup
void metaheuristic_class::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle) {

    // NodeHandle
    node_handle_ = node_handle;

    // ROS Services
    client_ = node_handle_->serviceClient<teastar_msgs::GetTEAstarPlanTime>("get_teastar_plan_time");

}

void metaheuristic_class::loadStartingPlan(std::vector<planning> starting_plan) { this->starting_plan_ = starting_plan; }

void metaheuristic_class::bestImprovement(bool improvement_flag) {

    ROS_WARN_STREAM("[TEA* MetaHeuristic] [BI/FI] STARTING PLAN");
    // std::cout << "STARTING PLAN\n";

	// printPlan(this->starting_plan_);

	neighbor current_plan;
	current_plan.plan = this->starting_plan_;
	current_plan.plan_time = getOnlinePlanningTime(this->starting_plan_);

    ROS_WARN_STREAM("[TEA* MetaHeuristic] [BI/FI] Starting Plan Time: " << current_plan.plan_time);

   // std::vector<planning> plan_swapped;
	std::vector<neighbor> list_of_neighbors;

	for(int i=0; i<10; i++){ //maximum iterations ("halting criterion")

		list_of_neighbors = generateListOfNeighbors(current_plan);
		//printNeighborhood(list_of_neighbors);
		list_of_neighbors = updateTimeOfNeighbors(list_of_neighbors, improvement_flag, current_plan, i);
		//printNeighborhood(list_of_neighbors);

		int min_time_neighbor = getMinPlanningTime(list_of_neighbors, current_plan);

		if(this->new_minimum_ == NOT_NEW_MIN)
		{
			ROS_ERROR_STREAM("[TEA* MetaHeuristic] [BI/FI] # REACHED LOCAL MINIMA # ");
			break;
		}

		current_plan = list_of_neighbors[min_time_neighbor];  //jumps to best neighbor

        ROS_WARN_STREAM("[TEA* MetaHeuristic] [BI/FI] Iteration # " << i << " Minimum Time " << current_plan.plan_time << " at Position " << min_time_neighbor);
	}

	printPlan(current_plan.plan);
}


std::vector<neighbor> metaheuristic_class::generateListOfNeighbors( neighbor inputNeighbor){

	std::vector<neighbor> list_of_neighbors;

	for(int first_plan=0; first_plan < NUM_MISSIONS; first_plan++){
		for(int second_plan = first_plan+1; second_plan < NUM_MISSIONS; second_plan++){
			    //std::cout << "swapping "<<first_plan<<" with "<<second_plan<<"\n";
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

std::vector<neighbor> metaheuristic_class::updateTimeOfNeighbors(std::vector<neighbor> input_list, bool improvement_flag,  neighbor inputNeighbor, int current_iteration){

	//TODO: pass the list of neighbours by reference
	//TODO: add incumbent pan time;
	//TODO: add flag for first improvement

	std::vector<neighbor> return_list;
	return_list = input_list;

	for (size_t i = 0; i < return_list.size(); i++) {
		//get time of a plan
		return_list[i].plan_time  =  getOnlinePlanningTime(return_list[i].plan);
		if (inputNeighbor.plan_time > return_list[i].plan_time && improvement_flag == FI_FLAG) {
			//swop
			for (size_t j = i+1; j < return_list.size(); j++){		//TODO: check if this is the best approach: identify the "smallest" and then put all times with the time of the current neighbor to avoid saving the time of the current neighbor outside the "BEST IMPROVEMENT method"
				return_list[j].plan_time=inputNeighbor.plan_time;
			}
			break;
		}
		//for first improvement, if plan time is lower that a memory variable, then preak and jumps to that neighbour
    }

	return return_list;
}

int metaheuristic_class::getMinPlanningTime(std::vector<neighbor> input_list, neighbor incumbent_solution){

	//TODO: check if input list have plans  (?)
	float min_time = incumbent_solution.plan_time;
	int min_time_position = 0;
	this->new_minimum_ = NOT_NEW_MIN;

	for (size_t i = 0; i < input_list.size(); i++) {

        ROS_WARN_STREAM(i);

		//get time of a plan
		if (input_list[i].plan_time < min_time ){

            ROS_ERROR_STREAM(i);

			min_time = input_list[i].plan_time;
			min_time_position = i;
			this->new_minimum_ = HAS_NEW_MIN;
		}

		//for first improvement, if plan time is lower that a memory variable, then preak and jumps to that neighbour
    }

	return min_time_position;
}

std::vector<planning> metaheuristic_class::swap1to1(std::vector<planning> input_plan, int fp, int sp) {

    std::vector<planning> plan_swapped = input_plan;

    // No Changes Needed
    if (fp == sp) { return plan_swapped; }

    if (fp >= input_plan.size() || sp >= input_plan.size()) {
        ROS_ERROR_STREAM("[TEA*] [MetaHeuristic Class] Impossible to Swap! First or Second Position higher than " << (input_plan.size() - 1) );
        return plan_swapped;
    }

    planning first_plan = input_plan[fp];
    planning second_plan = input_plan[sp];

    plan_swapped[fp].mission_id = second_plan.mission_id;
    plan_swapped[fp].mission_vertex = second_plan.mission_vertex;

    plan_swapped[sp].mission_id = first_plan.mission_id;
    plan_swapped[sp].mission_vertex = first_plan.mission_vertex;

}

void metaheuristic_class::printPlan(std::vector<planning> input_plan) {

    for (size_t i = 0; i < input_plan.size(); i++) {

        ROS_INFO_STREAM("[TEA* MetaHeuristic] R" << input_plan[i].robot_id << " (Vertex: " << input_plan[i].robot_vertex << ")" << " M" << input_plan[i].mission_id << " (Vertex " << input_plan[i].mission_vertex << ")");

    }

}

float metaheuristic_class::getOnlinePlanningTime(std::vector<planning> input_plan){

    float plan_time;

    teastar_msgs::GetTEAstarPlanTime srv;

    std::vector<teastar_msgs::Mission> plan;

    for (size_t i = 0; i < input_plan.size(); i++) {

        teastar_msgs::Mission mission;

        mission.robot_id = input_plan[i].robot_id;
        mission.robot_vertex = input_plan[i].robot_vertex;
        mission.mission_id = input_plan[i].mission_id;
        mission.mission_vertex = input_plan[i].mission_vertex;

        plan.push_back(mission);

    }

    srv.request.plan = plan;

    if (client_.call(srv)) {
        plan_time = srv.response.plan_time;

        ROS_INFO_STREAM("[TEA* MetaHeuristic] Plan Time: " << plan_time);

        return plan_time;
    }
    else {
        ROS_ERROR_STREAM("[TEA* MetaHeuristic] Failed to call service get_teastar_plan_time");
        return -1;
    }

}

float metaheuristic_class::auxGetExpon(int iter) {


	float auxExpon = iter*0.1;
	auxExpon /= 0.5;  //var
	auxExpon *= -1; //fixo


	double minValue;
	minValue = expf(auxExpon);
	minValue *= (105);
	minValue += -1;

	minValue *= 1.5;

    if (minValue < 0) {
        return 0.0;
    }
    else {
        return minValue;
    }
}

void metaheuristic_class::simulatedAnnealing(void) {


    ROS_WARN_STREAM("[]");

	std::ofstream filetowrite;
	filetowrite.open("SIMUL_ANEALL4.csv", std::ios_base::app);
	filetowrite << " ; #tests ; Tested time; Selected time; threshold" << std::endl;

	simulated_iteration = 0;				//t <-- 0
	// simulated_temperature = 700;            //initialize T
	int eval_threshold;                     // = 700;

	//select a current point Vc at random
	printPlan(this->starting_plan_);

    neighbor current_plan;
	current_plan.plan = this->starting_plan_;
    current_plan.plan_time = getOnlinePlanningTime(this->starting_plan_); //evaluate Vc

    std::vector<neighbor> list_of_neighbors;


	while(simulated_iteration < 70) {

			list_of_neighbors = generateListOfNeighbors(current_plan);

			for (size_t j = 0; j < list_of_neighbors.size(); j++) {

                // Get time of a Neighborhood
				list_of_neighbors[j].plan_time = getOnlinePlanningTime(list_of_neighbors[j].plan);

                // float aux=(current_plan.plan_time > list_of_neighbors[j].plan_time) ? list_of_neighbors[j].plan_time : current_plan.plan_time;
                filetowrite << simulated_iteration <<";"<<j<<";"<< list_of_neighbors[j].plan_time << ";" << current_plan.plan_time << ";"<<auxGetExpon(simulated_iteration)<<std::endl;

                // If a "minimum" is found
				if (current_plan.plan_time > list_of_neighbors[j].plan_time ) {

                    current_plan = list_of_neighbors[j];
					break;
				}

                // Did not found any "minimum"
    			else if (j >= list_of_neighbors.size() - 1) {

					// eval_threshold = simulated_temperature; // TODO: This should be an exponential function


                    std::vector<int> list_of_neighbors_shuffled;

                    // set some values:
                    for (int i=0; i<list_of_neighbors.size()-1; i++) list_of_neighbors_shuffled.push_back(i);

                    // using built-in random generator:
                    std::random_shuffle ( list_of_neighbors_shuffled.begin(), list_of_neighbors_shuffled.end() );

                    for (std::vector<int>::iterator it=list_of_neighbors_shuffled.begin(); it!=list_of_neighbors_shuffled.end(); ++it) {
                    // for (size_t l = 0; l < list_of_neighbors.size(); l++){

                        int l = *it;

						if (current_plan.plan_time + auxGetExpon(simulated_iteration) > list_of_neighbors[l].plan_time) {

							current_plan = list_of_neighbors[l];
							break;
						}

                        // TODO: Else... ?
                        else if ( std::distance( it, list_of_neighbors_shuffled.end() ) == 1 ) {
                            ROS_ERROR_STREAM("ERROR!!!!");
                            simulated_iteration = 100000;
                            break;
                        }

					}

                    break;
				}
			} //until (termination-condition)

        ROS_INFO_STREAM("[TEA* MetaHeuristic] [Simulated Annealing] Iteration #" << simulated_iteration << " Current Plan Time: " << current_plan.plan_time << " Current Temperature: " << auxGetExpon(simulated_iteration));

    	// simulated_temperature *= 0,98;	//T <-- g(T, t)
    	simulated_iteration += 1;		//t <-- t+1


	} //until (halting criterion)

}
