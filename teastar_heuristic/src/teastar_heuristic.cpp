#include "ros/ros.h"
#include "teastar_heuristic/heuristic_class.h"



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


    teastar_heuristic.runHeuristic1();

    // ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << agv <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

  return 0;
}
