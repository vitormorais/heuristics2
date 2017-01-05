#include "ros/ros.h"
#include "teastar_heuristic/heuristic_class.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "teastar_heuristic");

    // ros::NodeHandle n;
    // ros::ServiceClient client = n.serviceClient<teastar_msgs::GetTEAstarTime>("get_teastar_time");

    heuristic_class teastar_heuristic;

    teastar_heuristic.solutionInitialSetup();

    teastar_heuristic.printSolutionTable();


    // ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << agv <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

  return 0;
}
