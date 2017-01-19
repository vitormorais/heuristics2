#include<ros/ros.h>
#include "teastar_msgs/GetTEAstarPlanTime.h"
#include "teastar_msgs/Mission.h"

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
    void bestImprovement(void);
    float getOnlinePlanningTime(std::vector<planning> input_plan);


private:

    ros::NodeHandlePtr node_handle_;
    ros::ServiceClient client_;

    std::vector<planning> starting_plan_;
    std::vector<neighbor> list_of_neighbors_;

    void loadStartingPlan(std::vector<planning> starting_plan);
    std::vector<planning> swap1to1(std::vector<planning>, int first_position, int second_position);
    void printPlan(std::vector<planning> input_plan);


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

void metaheuristic_class::bestImprovement(void) {

    ROS_WARN_STREAM("STARTING PLAN");
    printPlan(this->starting_plan_);

    std::vector<planning> plan_swapped;

    plan_swapped = swap1to1(this->starting_plan_, 8, 9);

    ROS_WARN_STREAM("SWAPPED PLAN");
    printPlan(plan_swapped);

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
