#include<ros/ros.h>
#include "teastar_msgs/GetTEAstarTime.h"

// TODO: This cannot be declared as such. ////
#define NUM_ROBOTS 5
#define NUM_MISSIONS 13

#define SELECTABLE false
#define SELECTED true

float const MATRIX_TIMES_OFFLINE[NUM_MISSIONS][NUM_ROBOTS+NUM_MISSIONS] = {
	{112,   122,   191,   198,   122,   191,   191,   198,   122,   198,   122,   191,   198,    208},       //0
	{97,   108,   177,   184,   108,   177,   177,   184,   108,   184,   108,   177,   184,    193},        //1
	{96,   107,   168,   175,   107,   168,   168,   175,   107,   175,   107,   168,   175,    184},        //2
	{108,   121,   164,   172,   121,   164,   164,   172,   121,   172,   121,   164,   172,    181},       //3
	{116,   123,   175,   183,   123,   175,   175,   183,   123,   183,   123,   175,   183,    194},       //4
	{123,   109,   186,   194,   109,   186,   186,   194,   109,   194,   109,   186,   194,    204},       //5
	{135,   121,   198,   206,   121,   198,   198,   206,   121,   206,   121,   198,   206,    217},       //6
	{145,   131,   207,   216,   131,   207,   207,   216,   131,   216,   131,   207,   216,    226},       //7
	{157,   143,   220,   228,   143,   220,   220,   228,   143,   228,   143,   220,   228,    239},       //8

};

//R0 (0)|     112    |    97       |    96       |    108     |    116     |    123     |    135     |    145     |    157     |
//R1 (0)|     122    |    108     |    107     |    121     |    123     |    109     |    121     |    131     |    143     |
//R2 (0)|     191    |    177     |    168     |    164     |    175     |    186     |    198     |    207     |    220     |
//R3 (0)|     198    |    184     |    175     |    172     |    183     |    194     |    206     |    216     |    228     |
//R4 (0)|     208    |    193     |    184     |    181     |    194     |    204     |    217     |    226     |    239     |
//int const NUM_ROBOTS = 3;
//int const NUM_MISSIONS = 5;

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
    int robot_id;
	int robot_vertex;
	int mission_id;
    int mission_vertex;
}planning;

typedef struct{
    element matrixOfElements[NUM_MISSIONS][NUM_ROBOTS+NUM_MISSIONS];
	std::vector<element> selectElements;

	bool selectedMissions[NUM_MISSIONS];
	bool selectedRobots[NUM_MISSIONS+NUM_ROBOTS];

	float l_min_time_miss_value[NUM_MISSIONS];	//array com o tempo mínimo
	int l_min_time_miss_robot[NUM_MISSIONS];			//array com o agv correspondente ao tempo mínimo

	float l_max_time_miss_value[NUM_MISSIONS];	//array com o tempo mínimo
	int l_max_time_miss_robot[NUM_MISSIONS];			//array com o agv correspondente ao tempo mínimo

	std::vector<element> l_minimumTime;
	std::vector<element> l_maximumTime;

}solution;


class heuristic_class
{
private:

    // int NUM_ROBOTS = 3;
    // int NUM_MISSIONS = 5;

    ros::NodeHandlePtr node_handle_;
    ros::ServiceClient client_;

    std::vector<robot> l_robots;
    std::vector<mission> l_missions;
    solution initial_solution;

	float offlineTime;
	element selectedElement;

	int currIteration;


public:

	heuristic_class(void);
	~heuristic_class(void);

    void setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle);

	float getTEAstarOnline(int robot, int vertex_origin, int vertex_end);
	float getTEAstarOffline(int robot, int vertex_origin, int vertex_end);
    void initializeListOfRobots(void);
    void initializeListOfMissions(void);
    void solutionInitialSetup(void);
    void printSolutionTable(void);
	int getNextTime(void);
	void addElementAtEnd(int end_position, float mission_time);

	//####
	bool missionIsSelectable(int mission);
	bool missionIsSelected(int mission);
	bool robotIsSelectable(int robot);
	bool robotIsSelected(int robot);
	//####

	void updateMaximumTime(void);
	void updateMinimumTime(void);
	void printMaximumArray(void);
	void printMinimumArray(void);

	float getMinimumOfMinimum(void);
	float getMinimumOfMaximum(void);
	float getMaximumOfMinimum(void);
	float getMaximumOfMaximum(void);
	//####

	int getRemainingMissions(void);


	int getMaxResult(void);

	int selectTime(void);

	void printResults(void);


	//####
	std::vector<planning> runHeuristic1(void);
};

// Constructor
heuristic_class::heuristic_class(void) {

    // Create List of Robots
    initializeListOfRobots();

    // Create List of Missions
    initializeListOfMissions();

	offlineTime=2;
	selectedElement.robot=0;
	selectedElement.mission=0;

	currIteration = 0;

}

// Destructor
heuristic_class::~heuristic_class(void) {}

// ROS Configuration Setup
void heuristic_class::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle) {

    // NodeHandle
    node_handle_ = node_handle;

    // ROS Services
    client_ = node_handle_->serviceClient<teastar_msgs::GetTEAstarTime>("get_teastar_time");

}

void heuristic_class::initializeListOfRobots(void) {

    robot r0;
    r0.id = 0;
    r0.vertex = 7;

    robot r1;
    r1.id = 1;
    r1.vertex = 795;

    robot r2;
    r2.id = 2;
    r2.vertex = 104;

    robot r3;
    r3.id = 3;
    r3.vertex = 792;

    robot r4;
    r4.id = 4;
    r4.vertex = 119;

	robot r5;
    r5.id = 5;
    r5.vertex = 251;

	robot r6;
	r6.id = 6;
	r6.vertex = 263;

    l_robots.push_back(r0);
    l_robots.push_back(r1);
    l_robots.push_back(r2);
    l_robots.push_back(r3);
    l_robots.push_back(r4);
	// l_robots.push_back(r5);
	// l_robots.push_back(r6);

}

void heuristic_class::initializeListOfMissions(void) {

    mission m0;
    m0.id = 0;
    m0.vertex = 74;

    mission m1;
    m1.id = 1;
    m1.vertex = 71;

    mission m2;
    m2.id = 2;
    m2.vertex = 687;

	mission m3;
    m3.id = 3;
    m3.vertex = 699;

	mission m4;
    m4.id = 4;
    m4.vertex = 530;

    mission m5;
    m5.id = 5;
    m5.vertex = 536;

    mission m6;
    m6.id = 6;
    m6.vertex = 545;

    mission m7;
    m7.id = 7;
    m7.vertex = 554;

    mission m8;
    m8.id = 8;
    m8.vertex = 747;

	mission m9;
	m9.id = 9;
	m9.vertex = 293;

	mission m10;
	m10.id = 10;
	m10.vertex = 305;

	mission m11;
	m11.id = 11;
	m11.vertex = 846;

	mission m12;
	m12.id = 12;
	m12.vertex = 663;

    l_missions.push_back(m0);
    l_missions.push_back(m1);
    l_missions.push_back(m2);
	l_missions.push_back(m3);
	l_missions.push_back(m4);
	l_missions.push_back(m5);
    l_missions.push_back(m6);
    l_missions.push_back(m7);
    l_missions.push_back(m8);
	l_missions.push_back(m9);
	l_missions.push_back(m10);
	l_missions.push_back(m11);
	l_missions.push_back(m12);


}

/////
bool heuristic_class::missionIsSelectable(int mission) {
	return !initial_solution.selectedMissions[mission];
}
bool heuristic_class::missionIsSelected(int mission) {
	return initial_solution.selectedMissions[mission];
}
bool heuristic_class::robotIsSelectable(int robot) {
	return !initial_solution.selectedRobots[robot];
}
bool heuristic_class::robotIsSelected(int robot) {
	return initial_solution.selectedRobots[robot];
}
////

void heuristic_class::solutionInitialSetup(void) {

	for(int r=0; r < l_robots.size(); r++)
	{
		for(int m=0; m < l_missions.size(); m++)
		{

            int robot_id = l_robots[r].id;
            int vertex_origin = l_robots[r].vertex;
            int vertex_end = l_missions[m].vertex;

            float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);
			// float sum_time = getTEAstarOffline(robot_id, vertex_origin, vertex_end);

            element e;
            e.robot = l_robots[r].id;;
            e.mission = l_missions[m].id;
            e.initial_time = 0;
            e.mission_time = sum_time;

            initial_solution.matrixOfElements[m][r] = e;

          //  ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << robot_id <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

		}
	}

	for(int r=0; r < (l_robots.size() + l_missions.size()); r++)
	{
		initial_solution.selectedRobots[r] = SELECTED;//= true;
	}
	for(int r=0; r < l_robots.size(); r++)
	{
		initial_solution.selectedRobots[r] = SELECTABLE;//= false;
	}
	for(int m=0; m < l_missions.size(); m++)
	{
		initial_solution.selectedMissions[m] = SELECTABLE;//= false;
	}

}

float heuristic_class::getTEAstarOffline(int robot, int vertex_origin, int vertex_end) {

		return MATRIX_TIMES_OFFLINE[vertex_end][robot];
}

float heuristic_class::getTEAstarOnline(int robot, int vertex_origin, int vertex_end) {

    float sum_time;

    teastar_msgs::GetTEAstarTime srv;

    srv.request.agv = robot;
    srv.request.vertex_origin = vertex_origin;
    srv.request.vertex_end = vertex_end;

    if (client_.call(srv)) {
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


	for(int r=0; r < (l_robots.size()+currIteration); r++) {

		std::cout<< "R" << initial_solution.matrixOfElements[0][r].robot << " (" << initial_solution.matrixOfElements[0][r].initial_time << ")| ";

        for(int m=0; m < l_missions.size(); m++) {

			std::cout << "    " << ceil(initial_solution.matrixOfElements[m][r].mission_time + initial_solution.matrixOfElements[m][r].initial_time) << "    |";

		}

        std::cout<<std::endl;

	}

    std::cout<<std::endl;

}

int heuristic_class::getRemainingMissions(void) {
	int remainingMissions = l_missions.size() - initial_solution.selectElements.size();
	return remainingMissions;
}


////
void heuristic_class::updateMaximumTime(void) {

	initial_solution.l_maximumTime.clear();
	for(int m=0; m < l_missions.size(); m++)
	{
		initial_solution.l_max_time_miss_value[m] = 0;
		initial_solution.l_max_time_miss_robot[m] = 0;  // TODO: This can be dangerous...
	}

	for(int r=0; r < (l_robots.size()+currIteration  + 1); r++)
	{
		if(robotIsSelectable(r)){
			for(int m=0; m < l_missions.size(); m++)
			{
				if(missionIsSelectable(m) && (initial_solution.matrixOfElements[m][r].mission_time + initial_solution.matrixOfElements[m][r].initial_time) > initial_solution.l_max_time_miss_value[m]) // TODO: SelectedRobot should be true if the robot is selected, and false if the robot is selectable.
				{
					initial_solution.l_max_time_miss_value[m] = initial_solution.matrixOfElements[m][r].mission_time + initial_solution.matrixOfElements[m][r].initial_time;
					initial_solution.l_max_time_miss_robot[m] = r;
				}
			}
		}
	}

	for(int m=0; m < l_missions.size(); m++)
	{
		initial_solution.l_maximumTime.push_back(initial_solution.matrixOfElements[m][initial_solution.l_max_time_miss_robot[m]]);
	}
}
void heuristic_class::updateMinimumTime(void) {

	initial_solution.l_minimumTime.clear();
	for(int m=0; m < l_missions.size(); m++)
	{
		initial_solution.l_min_time_miss_value[m] = 10000;
		initial_solution.l_min_time_miss_robot[m] = 0;  // TODO: This can be dangerous...
	}

	for(int r=0; r < (l_robots.size()+currIteration  + 1); r++)
	{
		if(robotIsSelectable(r)){
			for(int m=0; m < l_missions.size(); m++)
			{
				if(missionIsSelectable(m) && (initial_solution.matrixOfElements[m][r].mission_time + initial_solution.matrixOfElements[m][r].initial_time) < initial_solution.l_min_time_miss_value[m]) // TODO: SelectedRobot should be true if the robot is selected, and false if the robot is selectable.
				{
					initial_solution.l_min_time_miss_value[m] = initial_solution.matrixOfElements[m][r].mission_time + initial_solution.matrixOfElements[m][r].initial_time;
					initial_solution.l_min_time_miss_robot[m] = r;
				}
			}
		}
	}

	for(int m=0; m < l_missions.size(); m++)
	{
		initial_solution.l_minimumTime.push_back(initial_solution.matrixOfElements[m][initial_solution.l_min_time_miss_robot[m]]);
	}
}

void heuristic_class::printMaximumArray(void) {

	std::cout << "\n   Max time" << std::endl;
	for(int m=0; m < l_missions.size(); m++)
	{
		std::cout <<"M" << m << ": " << initial_solution.l_min_time_miss_value[m] << "st:" <<initial_solution.selectedMissions[m] <<"  | ";
    }


	return;
}
void heuristic_class::printMinimumArray(void) {

	std::cout << "\n   Min time" << std::endl;
	for(int m=0; m < l_missions.size(); m++)
	{
		std::cout <<"M" << m << ": " << initial_solution.l_min_time_miss_value[m] << "st:" <<initial_solution.selectedMissions[m] <<"  | ";
    }


	return;
}

float heuristic_class::getMinimumOfMinimum(void) {
	float minimumTime = 100000;
	float minimumTime2 = 100000;
	int minimum_mission = 0;

	for(int m=0; m < l_missions.size(); m++){
		if(missionIsSelectable(m) && minimumTime2 > (initial_solution.l_minimumTime[m].initial_time+initial_solution.l_minimumTime[m].mission_time))
		{
			minimumTime2 = (initial_solution.l_minimumTime[m].initial_time+initial_solution.l_minimumTime[m].mission_time);
			minimum_mission = m;
		}
	}

	selectedElement = initial_solution.l_minimumTime[minimum_mission];


	return minimumTime2;
}
float heuristic_class::getMinimumOfMaximum(void) {
	float minimumTime = 100000;
	float minimumTime2 = 100000;
	int minimum_mission = 0;

	for(int m=0; m < l_missions.size(); m++){
		if(missionIsSelectable(m) && minimumTime2 > (initial_solution.l_maximumTime[m].initial_time+initial_solution.l_maximumTime[m].mission_time))
		{
			minimumTime2 = (initial_solution.l_maximumTime[m].initial_time+initial_solution.l_maximumTime[m].mission_time);
			minimum_mission = m;
		}
	}

	selectedElement = initial_solution.l_maximumTime[minimum_mission];


	return minimumTime2;
}
float heuristic_class::getMaximumOfMinimum(void) {
	float maximumTime = 0;
	//float maximumTime2 = 100000;
	int maximum_mission = 0;

	for(int m=0; m < l_missions.size(); m++){
		if(missionIsSelectable(m) && maximumTime < (initial_solution.l_minimumTime[m].initial_time+initial_solution.l_minimumTime[m].mission_time))
		{
			maximumTime = (initial_solution.l_minimumTime[m].initial_time+initial_solution.l_minimumTime[m].mission_time);
			maximum_mission = m;
		}
	}

	selectedElement = initial_solution.l_minimumTime[maximum_mission];


	return maximumTime;
}
float heuristic_class::getMaximumOfMaximum(void) {
	float maximumTime = 0;
	float maximumTime2 = 0;
	int maximum_mission = 0;

	for(int m=0; m < l_missions.size(); m++){
		if(missionIsSelectable(m) && maximumTime2 < (initial_solution.l_maximumTime[m].initial_time+initial_solution.l_maximumTime[m].mission_time))
		{
			maximumTime2 = (initial_solution.l_maximumTime[m].initial_time+initial_solution.l_maximumTime[m].mission_time);
			maximum_mission = m;
		}
	}

	selectedElement = initial_solution.l_maximumTime[maximum_mission];


	return maximumTime2;
}

////

int heuristic_class::getMaxResult(void) {
	std::vector<element>::iterator it;
	int i=0;
	float maximum = 0;

	for(it=initial_solution.selectElements.begin() ; it < initial_solution.selectElements.end(); it++,i++ )
	{
		if ((it->initial_time + it->mission_time) > maximum) {
			maximum = it->initial_time + it->mission_time;
		}
    }


	return maximum;
}

int heuristic_class::selectTime(void) {

	int aux = initial_solution.l_min_time_miss_robot[selectedElement.mission];

	initial_solution.selectedMissions[selectedElement.mission]			= SELECTED;		//=true;					// put currently selected mission as "selected"
	initial_solution.selectedRobots[aux]								= SELECTED;		//=true;					// put currently selected robot as "selected"
	initial_solution.selectedRobots[l_robots.size()+currIteration]		= SELECTABLE;	//=false;		// put new line inserted select robot array as "selectable"

	initial_solution.selectElements.push_back(selectedElement);

	float timeOfExecution = initial_solution.matrixOfElements[selectedElement.mission][selectedElement.robot].mission_time;

	addElementAtEnd(l_robots.size()+currIteration, timeOfExecution); //igual ao TEA*

	return -1;
}

void heuristic_class::addElementAtEnd(int end_position, float mission_time) {
	for(int m=0; m < l_missions.size(); m++)
		{

            int robot_id = selectedElement.robot;
            int vertex_origin = l_missions[selectedElement.mission].vertex;
            int vertex_end = l_missions[m].vertex;

           	float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);
			// float sum_time = getTEAstarOffline(end_position-NUM_ROBOTS, selectedElement.mission, m);  //note: end_position is id_robot in offline ( TAKE ATTENTION FOR ONLINE)

            element e;
            e.robot = selectedElement.robot;
            e.mission = m;
			e.initial_time = selectedElement.mission_time + selectedElement.initial_time; // FIXED: Initial time = initital time (do anterior) + mission time (do anterior)
            e.mission_time = sum_time;// + mission_time;

            initial_solution.matrixOfElements[m][end_position] = e;

          //  ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << robot_id <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

		}
}

void heuristic_class::printResults(void) {
	std::vector<element>::iterator it;
	int i=0;

	for(it=initial_solution.selectElements.begin() ; it < initial_solution.selectElements.end(); it++,i++ )
	{
		std::cout <<"\n   Iteration #"<< i <<" M"<<it->mission<<" -  R"<< it->robot<<" --> t_ini = "<<it->initial_time<<"  |  t_end = "<< (it->initial_time + it->mission_time) <<"  |  t_duration = "<<it->mission_time;;
    }


	return;
}

//##########################################################

std::vector<planning> heuristic_class::runHeuristic1(void) {

	std::vector<planning> planning_vector;

	solutionInitialSetup();  //incluir aqui o TEA*
	printSolutionTable();

	while(getRemainingMissions() >= 1)
	{

		std::cout <<"\n###########   Iteration "<<currIteration<<"   ###########\n";

		updateMinimumTime();
		updateMaximumTime();

		// std::cout <<"\nMinimum time:"<< getMinimumOfMinimum(); //for H1: obtem primeiro o minimo do conjunto dos m�nimos
		std::cout <<"\nMaximum time:"<< getMaximumOfMinimum(); //for H2: obtem primeiro o m�ximo do conjunto dos m�nimos

		//std::cout <<"\nMinimum of maximum time:"<< getMinimumOfMaximum(); //for H2: obtem primeiro o m�ximo do conjunto dos m�nimos
		//std::cout <<"\nMaximum of maximum time:"<< getMaximumOfMaximum();


		std::cout << "\nSelected R" << selectedElement.robot << " M" << selectedElement.mission<<std::endl;
		// printMinimumArray();

		selectTime();		//incluir aqui o TEA*

		currIteration += 1;
		printSolutionTable();

		std::cout <<"\nRemaining Missions:"<< getRemainingMissions();
	}

	printResults();


	std::vector<element>::iterator it;

	for(it=initial_solution.selectElements.begin() ; it < initial_solution.selectElements.end(); it++)
	{
		planning p;
		p.robot_id = it->robot;
		p.robot_vertex = l_robots[it->robot].vertex;
		p.mission_id = it->mission;
		p.mission_vertex = l_missions[it->mission].vertex;

		planning_vector.push_back(p);
	}


	return planning_vector;

}
