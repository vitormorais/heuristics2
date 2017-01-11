#include "StdAfx.h"
#include "heuristic_class.h"

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


/*
// ROS Configuration Setup
void heuristic_class::setupConfigurationFromParameterServer(ros::NodeHandlePtr& node_handle) {

    // NodeHandle
    node_handle_ = node_handle;

    // ROS Services
    client_ = node_handle_->serviceClient<teastar_msgs::GetTEAstarTime>("get_teastar_time");

}*/
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

    l_robots.push_back(r0);
    l_robots.push_back(r1);
    l_robots.push_back(r2);
    l_robots.push_back(r3);
    l_robots.push_back(r4);

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
    m2.vertex = 693;

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

    l_missions.push_back(m0);
    l_missions.push_back(m1);
    l_missions.push_back(m2);
	l_missions.push_back(m3);
	l_missions.push_back(m4);
	l_missions.push_back(m5);
    l_missions.push_back(m6);
    l_missions.push_back(m7);
    l_missions.push_back(m8);

}

/////
bool heuristic_class::missionIsSelectable(int mission){
	return !initial_solution.selectedMissions[mission];
}
bool heuristic_class::missionIsSelected(int mission){
	return initial_solution.selectedMissions[mission];
}
bool heuristic_class::robotIsSelectable(int robot){
	return !initial_solution.selectedRobots[robot];
}
bool heuristic_class::robotIsSelected(int robot){
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

           // float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);
			 float sum_time = getTEAstarOffline(r, vertex_origin, m);

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
/*
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
     //   ROS_ERROR_STREAM("[TEA* Heuristic] [AGV " << robot <<"] Failed to call service get_teastar_time");

        return -1;
    }


}
*/
void heuristic_class::printSolutionTable(void) {

	// std::cout<<"printing solution"<<std::endl;

	//printing table header
	std::cout<<"      | ";

	for(int m=0; m < l_missions.size(); m++) {
		std::cout<<"    M" << m << "     | ";
	}

	std::cout<<std::endl;


	for(int r=0; r < (l_robots.size()+currIteration); r++) {

		std::cout<< "R" << r << " (" << initial_solution.matrixOfElements[0][r].initial_time << ")| ";

        for(int m=0; m < l_missions.size(); m++) {

			std::cout << "    " << ceil(initial_solution.matrixOfElements[m][r].mission_time) << "    |";

		}

        std::cout<<std::endl;

	}

    std::cout<<std::endl;

}

int heuristic_class::getRemainingMissions(void) {
	int remainingMissions = l_missions.size() - initial_solution.selectElements.size();
	return remainingMissions;
}

float heuristic_class::getMaximumTime(void) {
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

float heuristic_class::getMinimumTime(void) {
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
            int vertex_origin = selectedElement.mission;
            int vertex_end = l_missions[m].vertex;

           // float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);
			float sum_time = getTEAstarOffline(end_position, vertex_origin, m);  //note: end_position is id_robot in offline ( TAKE ATTENTION FOR ONLINE)

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
		std::cout <<"\n   Iteration("<< i <<") M("<<it->mission<<") -  R("<<
			it->robot<<") --> t_ini = "<<it->initial_time<<"  |  t_end = "<<it->initial_time + it->mission_time<<"  |  t_duration = "<<it->mission_time;
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

//##########################################################

void heuristic_class::runHeuristic1(void) {

	solutionInitialSetup();  //incluir aqui o TEA*
	printSolutionTable();



	while(getRemainingMissions() >= 1)
	{
		
		std::cout <<"\n###########   Iteration "<<currIteration<<"   ###########\n";
		updateMinimumTime();

		//std::cout <<"\nMinimum time:"<< getMinimumTime(); //for H1: obtem primeiro o minimo do conjunto dos m�nimos
		std::cout <<"\nMinimum time:"<< getMaximumTime(); //for H2: obtem primeiro o m�ximo do conjunto dos m�nimos

		std::cout << "\nSelected R" << selectedElement.robot << " M" << selectedElement.mission<<std::endl;
		printMinimumArray();

		selectTime();		//incluir aqui o TEA*

		currIteration += 1;
		printSolutionTable();

		std::cout <<"\nRemaining Missions:"<< getRemainingMissions();
	}

	printResults();

}
