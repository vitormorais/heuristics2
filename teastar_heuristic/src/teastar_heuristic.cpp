#include "ros/ros.h"
#include "teastar_heuristic/heuristic_class.h"
#include "teastar_heuristic/metaheuristic_class.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "teastar_heuristic");

    ros::NodeHandlePtr node_handle(new ros::NodeHandle());
    // ros::NodeHandlePtr private_node_handle(new ros::NodeHandle("~"));

    // ros::NodeHandle n;
    // ros::ServiceClient client = n.serviceClient<teastar_msgs::GetTEAstarTime>("get_teastar_time");

    heuristic_class teastar_heuristic;

    teastar_heuristic.setupConfigurationFromParameterServer(node_handle);

    // teastar_heuristic.solutionInitialSetup();
    //
    // teastar_heuristic.printSolutionTable();

    std::vector<planning> starting_plan;

    starting_plan = teastar_heuristic.runHeuristic1();

    for (size_t i = 0; i < starting_plan.size(); i++) {

        ROS_INFO_STREAM("R" << starting_plan[i].robot_id << " M" << +starting_plan[i].mission_id << " (Vertex " << starting_plan[i].mission_vertex <<")");
    }

    metaheuristic_class teastar_metaheuristic(starting_plan);

    teastar_metaheuristic.bestImprovement();



    // ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << agv <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

  return 0;
}
