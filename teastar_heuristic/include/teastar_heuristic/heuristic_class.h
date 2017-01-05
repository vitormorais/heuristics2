#include<ros/ros.h>
#include "teastar_msgs/GetTEAstarTime.h"

// TODO: This cannot be declared as such. ////
int const NUM_ROBOTS = 3;
int const NUM_MISSIONS = 5;
//////////////////////////////////////////////

typedef struct{
    int id;
    int vertex;
}robot;

typedef struct{
    int id;
    int vertex;
}mission;

typedef struct{
    int robot;
    int mission;
    float initial_time;
    float mission_time;
}element;

typedef struct{
    element matrixOfElements[NUM_MISSIONS][NUM_ROBOTS];
}solution;


class heuristic_class
{
private:

    // int NUM_ROBOTS = 3;
    // int NUM_MISSIONS = 5;

    std::vector<robot> l_robots;
    std::vector<mission> l_missions;
    solution initial_solution;


public:

    // TODO: THIS CANNOT BE DONE HERE. //////////////////////////////////////////////
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<teastar_msgs::GetTEAstarTime>("get_teastar_time");
    /////////////////////////////////////////////////////////////////////////////////

	heuristic_class(void);
	~heuristic_class(void);

    float getTEAstarOnline(int robot, int vertex_origin, int vertex_end);
    void initializeListOfRobots(void);
    void initializeListOfMissions(void);
    void solutionInitialSetup(void);
    void printSolutionTable(void);


};

// Constructor
heuristic_class::heuristic_class(void) {

    // Create List of Robots
    initializeListOfRobots();

    // Create List of Missions
    initializeListOfMissions();

}

// Destructor
heuristic_class::~heuristic_class(void) {}

void heuristic_class::initializeListOfRobots(void) {

    robot r0;
    r0.id = 0;
    r0.vertex = 7;

    robot r1;
    r1.id = 1;
    r1.vertex = 7;

    robot r2;
    r2.id = 2;
    r2.vertex = 7;

    l_robots.push_back(r0);
    l_robots.push_back(r1);
    l_robots.push_back(r2);

}

void heuristic_class::initializeListOfMissions(void) {

    mission m0;
    m0.id = 0;
    m0.vertex = 71;

    mission m1;
    m1.id = 1;
    m1.vertex = 71;

    mission m2;
    m2.id = 2;
    m2.vertex = 71;

    l_missions.push_back(m0);
    l_missions.push_back(m1);
    l_missions.push_back(m2);

}

void heuristic_class::solutionInitialSetup(void) {

	for(int r=0; r < l_robots.size(); r++)
	{
		for(int m=0; m < l_missions.size(); m++)
		{

            int robot_id = l_robots[r].id;
            int vertex_origin = l_robots[r].vertex;
            int vertex_end = l_missions[m].vertex;

            float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);

            element e;
            e.robot = l_robots[r].id;;
            e.mission = l_missions[m].id;
            e.initial_time = 0;
            e.mission_time = sum_time;

            initial_solution.matrixOfElements[m][r] = e;

            ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << robot_id <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

		}
	}

}

float heuristic_class::getTEAstarOnline(int robot, int vertex_origin, int vertex_end) {

    float sum_time;

    teastar_msgs::GetTEAstarTime srv;

    srv.request.agv = robot;
    srv.request.vertex_origin = vertex_origin;
    srv.request.vertex_end = vertex_end;

    if (client.call(srv)) {
        sum_time = srv.response.sum_time;

        return sum_time;
    }
    else {
        ROS_ERROR_STREAM("[TEA* Heuristic] [AGV " << robot <<"] Failed to call service get_teastar_time");

        return -1;
    }


}

void heuristic_class::printSolutionTable(void) {

	// std::cout<<"printing solution"<<std::endl;

	//printing table header
	std::cout<<"      | ";

	for(int m=0; m < l_missions.size(); m++) {
		std::cout<<"    M" << m << "     | ";
	}

	std::cout<<std::endl;


	for(int r=0; r < l_robots.size(); r++) {

		std::cout<< "R" << r << " (" << initial_solution.matrixOfElements[r][0].initial_time << ")| ";

        for(int m=0; m < l_missions.size(); m++) {

			std::cout<<" "<< initial_solution.matrixOfElements[r][m].mission_time <<"   | ";

		}

        std::cout<<std::endl;

	}

    std::cout<<std::endl;

}
