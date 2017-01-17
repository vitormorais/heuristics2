// metaheuristic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "metaheuristic_class.h"
#include <iostream>
#include <string>
#include <algorithm>
//#include "Windows.h"
#include <fstream>
#include <vector>

#define BI_FLAG true
#define FI_FLAG false


std::vector<planning> generateOfflineStartingPlan(void);

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	std::vector<planning> starting_plan;
	
	starting_plan = generateOfflineStartingPlan();
	//starting_plan = teastar_heuristic.runHeuristic1();

	for (size_t i = 0; i < starting_plan.size(); i++) {

        //ROS_INFO_STREAM("R" << starting_plan[i].robot_id << " M" << +starting_plan[i].mission_id << " (Vertex " << starting_plan[i].mission_vertex <<")");
		std::cout << "R" << starting_plan[i].robot_id << " M" << +starting_plan[i].mission_id << " (Vertex " << starting_plan[i].mission_vertex <<")" << std::endl;
    }

    metaheuristic_class teastar_metaheuristic(starting_plan);

   // teastar_metaheuristic.bestImprovement(BI_FLAG);
	teastar_metaheuristic.simulatedAnnealing();


	getchar();

	return 0;
}


//FUNCTIONS
std::vector<planning> generateOfflineStartingPlan(void){
	    std::vector<planning> starting_plan;

		
		//R1 M8 (Vertex 747)
		planning p1;
		p1.mission_id = 8;
		p1.mission_vertex = 747;
		p1.robot_id=1;
		starting_plan.push_back(p1);

		//R0 M7 (Vertex 554)
		planning p2;
		p2.mission_id = 7;
		p2.mission_vertex = 554;
		p2.robot_id=0;
		starting_plan.push_back(p2);

		//R2 M6 (Vertex 545)
		planning p3;
		p3.mission_id = 6;
		p3.mission_vertex = 545;
		p3.robot_id=2;
		starting_plan.push_back(p3);
		
		//R3 M0 (Vertex 74)
		planning p4;
		p4.mission_id = 0;
		p4.mission_vertex = 74;
		p4.robot_id=3;
		starting_plan.push_back(p4);

		//R0 M5 (Vertex 536)
		planning p5;
		p5.mission_id = 5;
		p5.mission_vertex = 536;
		p5.robot_id = 0;
		starting_plan.push_back(p5);

		//R4 M4 (Vertex 530)
		planning p6;
		p6.mission_id = 4;
		p6.mission_vertex = 530;
		p6.robot_id = 4;
		starting_plan.push_back(p6);
		
		//R3 M3 (Vertex 699)
		planning p7;
		p7.mission_id = 3;
		p7.mission_vertex = 699;
		p7.robot_id = 3;
		starting_plan.push_back(p7);
		
		//R1 M1 (Vertex 71)
		planning p8;
		p8.mission_id = 1;
		p8.mission_vertex = 71;
		p8.robot_id = 1;
		starting_plan.push_back(p8);

		//R4 M2 (Vertex 687)
		planning p9;
		p9.mission_id = 2;
		p9.mission_vertex = 687;
		p9.robot_id = 4;
		starting_plan.push_back(p9);

		return starting_plan;
}