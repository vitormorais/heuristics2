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

	mission m3;
    m2.id = 3;
    m2.vertex = 71;

	mission m4;
    m2.id = 4;
    m2.vertex = 71;

    l_missions.push_back(m0);
    l_missions.push_back(m1);
    l_missions.push_back(m2);
	l_missions.push_back(m3);
	l_missions.push_back(m4);

}

void heuristic_class::solutionInitialSetup(void) {

	for(int r=0; r < l_robots.size(); r++)
	{
		for(int m=0; m < l_missions.size(); m++)
		{

            int robot_id = l_robots[r].id;
            int vertex_origin = l_robots[r].vertex;
            int vertex_end = l_missions[m].vertex;

           // float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);
			 float sum_time = getTEAstarOffline(robot_id, vertex_origin, vertex_end);

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
		initial_solution.timeOfAGVs[r] = 0;
		initial_solution.selectedAGVs[r] = false;
	}
	for(int r=0; r < l_robots.size(); r++)
	{
		initial_solution.selectedAGVs[r] = true;
	}
	for(int m=0; m < l_missions.size(); m++)
	{
		initial_solution.selectedMissions[m] = false;
	}

}

float heuristic_class::getTEAstarOffline(int robot, int vertex_origin, int vertex_end) {
	
	offlineTime +=1;
	return offlineTime;
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

			std::cout<<" "<< initial_solution.matrixOfElements[m][r].mission_time <<"   | ";

		}

        std::cout<<std::endl;

	}

    std::cout<<std::endl;

}

int heuristic_class::getRemainingMissions(void)
{
	int remainingMissions = l_missions.size();
	remainingMissions -= initial_solution.selectElements.size();
	return remainingMissions;
}

float heuristic_class::getMinimumTime(void)
{
	float minimumTime = 100000;
	

	for(int m=0; m < l_missions.size()  + 1; m++)
	{
		if(initial_solution.minimumTimeMissions[m] < minimumTime && !initial_solution.selectedMissions[m])
		{
			selectedElement.robot = initial_solution.minimumTimeAGV[m];
			selectedElement.mission=m;
			minimumTime = initial_solution.minimumTimeMissions[m];
		}
	}

	return minimumTime;
}

void heuristic_class::updateMinimumTime(void)
{
	for(int m=0; m < l_missions.size()  + 1; m++)
	{
		initial_solution.minimumTimeMissions[m] = initial_solution.matrixOfElements[m][0].mission_time + 1;
		initial_solution.minimumTimeAGV[m] = 0;
	}

	for(int r=0; r < (l_robots.size()+currIteration  + 1); r++)
	{
		for(int m=0; m < l_missions.size()  + 1; m++)
		{
			if(initial_solution.selectedAGVs[r] && initial_solution.matrixOfElements[m][r].mission_time < initial_solution.minimumTimeMissions[m])
			{
				initial_solution.minimumTimeMissions[m] = initial_solution.matrixOfElements[m][r].mission_time;
				initial_solution.minimumTimeAGV[m] = r;
			}
		}
	}
}
int heuristic_class::selectTime(void)
{

	initial_solution.selectedMissions[selectedElement.mission]=true;
	initial_solution.selectedAGVs[selectedElement.robot]=false;
	initial_solution.selectedAGVs[l_robots.size()+currIteration-1]=true;

	initial_solution.selectElements.push_back(initial_solution.matrixOfElements[selectedElement.mission][selectedElement.robot]);

	float timeOfExecution = initial_solution.matrixOfElements[selectedElement.mission][selectedElement.robot].mission_time;
	
	addElementAtEnd(l_robots.size()+currIteration-1, timeOfExecution); //igual ao TEA*

	return -1;
}

void heuristic_class::addElementAtEnd(int end_position, float mission_time) {
	for(int m=0; m < l_missions.size(); m++)
		{

            int robot_id = selectedElement.robot;
            int vertex_origin = selectedElement.mission;
            int vertex_end = l_missions[m].vertex;

           // float sum_time = getTEAstarOnline(robot_id, vertex_origin, vertex_end);
			float sum_time = getTEAstarOffline(robot_id, vertex_origin, vertex_end);

            element e;
            e.robot = selectedElement.robot;
            e.mission = m;
            e.initial_time = mission_time;
            e.mission_time = mission_time + sum_time;

            initial_solution.matrixOfElements[m][end_position+1] = e;

          //  ROS_INFO_STREAM("[TEA* Heuristic] [AGV " << robot_id <<"] Time between Vertex " << vertex_origin << " and Vertex " << vertex_end << ": " << sum_time);

		}
}

void heuristic_class::printResults(void)
{
	std::vector<element>::iterator it;
	int i=0;

	for(it=initial_solution.selectElements.begin() ; it < initial_solution.selectElements.end(); it++,i++ )
	{
		std::cout <<"\n   Iteration("<< i <<") M("<<it->mission<<") -  R("<<
			it->robot<<") --> t_ini = "<<it->initial_time<<"  |  t_end = "<<it->mission_time;
    }


	return;
}
//##########################################################
void heuristic_class::runHeuristic1(void)
{
	
	solutionInitialSetup();  //incluir aqui o TEA*
	printSolutionTable();



	while(getRemainingMissions() >= 1)
	{
		
		std::cout <<"\n###########   Iteration "<<currIteration<<"   ###########\n";
		updateMinimumTime();

		std::cout <<"\nMinimum time:"<< getMinimumTime(); //for H1: obtem primeiro o minimo do conjunto dos m�nimos
		//std::cout <<"\nMinimum time:"<< getMaximumTime(); //for H2: obtem primeiro o m�ximo do conjunto dos m�nimos

		selectTime();		//incluir aqui o TEA*

		currIteration += 1;
		printSolutionTable();

		std::cout <<"\nRemaining Missions:"<< getRemainingMissions();
	}

	printResults();

}
