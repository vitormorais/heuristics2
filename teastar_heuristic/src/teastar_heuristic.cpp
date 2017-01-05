#include "ros/ros.h"
#include "teastar_msgs/GetTEAstarTime.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "teastar_heuristic");

    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<teastar_msgs::GetTEAstarTime>("get_teastar_time");

    teastar_msgs::GetTEAstarTime srv;

    int agv = 0;
    int vertex_origin = 7;
    int vertex_end = 71;
    float sum_time;

    srv.request.agv = agv;
    srv.request.vertex_origin = vertex_origin;
    srv.request.vertex_end = vertex_end;

    if (client.call(srv)) {
        sum_time = srv.response.sum_time;

        ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << agv <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);
    }
    else {
        ROS_ERROR_STREAM("[TEA* Heuristic] [AGV " << agv <<"] Failed to call service get_teastar_time");
        return 1;
    }

  return 0;
}
