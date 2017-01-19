#include<ros/ros.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>

#define NUM_ROBOTS 5
#define NUM_MISSIONS 9

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

///////////////////
// CLASS METHODS //
///////////////////


// Constructor
metaheuristic_class::metaheuristic_class(std::vector<planning> starting_plan) { loadStartingPlan(starting_plan); }
// Destructor
metaheuristic_class::~metaheuristic_class(void) {}

void metaheuristic_class::loadStartingPlan(std::vector<planning> starting_plan) { this->starting_plan_ = starting_plan; }

void metaheuristic_class::bestImprovement(bool improvement_flag) {

    ROS_WARN_STREAM("STARTING PLAN");
    printPlan(this->starting_plan_);

	neighbor  current_plan;
	current_plan.plan = this->starting_plan_;
	current_plan.plan_time =9;

   // std::vector<planning> plan_swapped;
	std::vector<neighbor> list_of_neighbors;

	for(int i=0; i<10; i++){

		list_of_neighbors = generateListOfNeighbors(current_plan);
		//printNeighborhood(list_of_neighbors);
		list_of_neighbors = updateTimeOfNeighbors(list_of_neighbors, improvement_flag, current_plan, i);
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
        ROS_ERROR_STREAM("[TEA*] [MetaHeuristic Class] Impossible to Swap! First or Second Position higher than " << (input_plan.size() - 1) );
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

        ROS_INFO_STREAM("[TEA*] [MetaHeuristic Class] R" << input_plan[i].robot_id << " M" << input_plan[i].mission_id << " (Vertex " << input_plan[i].mission_vertex << ")");

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
		return_list[i].plan_time  =  getOfflinePlanningTime(return_list[i].plan, current_iteration);
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

float metaheuristic_class::getOfflinePlanningTime(std::vector<planning> input_plan, int current_iteration){
	

	float t = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //value between 0 and 1


	//return (r * static_cast <float> (10000));

	//int heuristics::generateRandomNumber(int iterations)
//{
	float auxExpon = current_iteration*0.1;
	auxExpon /= 25;  //var
	auxExpon *= -1; //fixo

				
	double minValue;
	minValue = std::expf(auxExpon);
	minValue *= (105);
	minValue += -2;
	float r = minValue + static_cast <float> (rand() / static_cast <float> (RAND_MAX/0.5-minValue)); //value between 0 and 1
//	std::cout << r*(1.5-t) << std::endl;
	return r*7 + (r*0,01)*700*t;
		//
//}
}

int metaheuristic_class::auxGetExpon(int iter) {

	
	float auxExpon = iter*0.1;
	auxExpon /= 55;  //var
	auxExpon *= -1; //fixo

				
	double minValue;
	minValue = std::expf(auxExpon);
	minValue *= (105);
	minValue += -2;

	minValue *= 3;
	return minValue;
}

void metaheuristic_class::simulatedAnnealing(void){


	std::ofstream filetowrite;
	filetowrite.open("..\\SIMUL_ANEALL4.txt", std::ios_base::app);
	filetowrite << " ; #tests ; Tested time; Selected time; threshold" << std::endl;
	simulated_iteration = 0;				//t <-- 0
	simulated_temperature = 700;//700;			//initialize T
	int eval_threshold;// = 700;
											//select a current point Vc at random
	printPlan(this->starting_plan_);
	neighbor  current_plan;
	current_plan.plan = this->starting_plan_;
	std::vector<neighbor> list_of_neighbors;
											//evaluate Vc
	current_plan.plan_time =900;

	while(simulated_iteration < 2000) {		//repeat


		//for(int i=0; i<50; i++){				//repeat

													//select a new point Vn
														//in the neighborhood of Vc
			list_of_neighbors = generateListOfNeighbors(current_plan);

														//if (eval(Vc) < eval(Vn)
														//then Vc <-- Vn
														//else if random[0,1] < e^{(eval(n)-eval(c))/T}
															//then Vc <-- Vn
			//list_of_neighbors = updateTimeOfNeighbors(list_of_neighbors, improvement_flag, current_plan, i);
			for (size_t j = 0; j < list_of_neighbors.size(); j++) {
				//get time of a plan
				list_of_neighbors[j].plan_time  =  getOfflinePlanningTime(list_of_neighbors[j].plan, simulated_iteration);  //está correto o 'i'
				float aux=(current_plan.plan_time > list_of_neighbors[j].plan_time) ? list_of_neighbors[j].plan_time : current_plan.plan_time;
				filetowrite << simulated_iteration <<";"<<j<<";"<< list_of_neighbors[j].plan_time << ";" << aux << ";"<<auxGetExpon(simulated_iteration)<<std::endl;
				if (current_plan.plan_time + auxGetExpon(simulated_iteration) > list_of_neighbors[j].plan_time ) {//&& FI_FLAG == FI_FLAG) {
					//swop
					//falta ir ao getminplanningtime....
					current_plan = list_of_neighbors[j];
					break;
				}
				else if (j >= list_of_neighbors.size()-1) {  //não encontrou nenhum mínimo
					//random[0,1] < e^{(eval(n)-eval(c))/T}	
					eval_threshold  = simulated_temperature;
					for (size_t l = 0; l < list_of_neighbors.size(); l++){
							
							if (current_plan.plan_time + eval_threshold > list_of_neighbors[j].plan_time) {
								//swop
								//falta ir ao getminplanningtime....
								current_plan = list_of_neighbors[j];
								break;
							}
						}
						break;
				}
			}
		//for first improvement, if plan time is lower that a memory variable, then preak and jumps to that neighbour
    
			//printNeighborhood(list_of_neighbors);

													

	//	}									//until (termination-condition)
	std::cout<<current_plan.plan_time<<std::endl;
	simulated_temperature *= 0,98;				//T <-- g(T, t)
	simulated_iteration += 1;					//t <-- t+1


	}										//until (halting criterion)
											
	//print, etc...							//end
	printPlan(current_plan.plan);		
	
}