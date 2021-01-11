#ifndef TSP_SOLVER_CPP
#define TSP_SOLVER_CPP

#include "tsp_solver.h"
#include "Brute_Force.h"
#include "NN_tsp.h"
#include "INN_tsp.h"
#include "ACS_system.h"
#include <iostream>
#include <fstream>
#include <string>
#include "point.h"
#include <vector>

void tsp_solver::reset_points(){
	for(point* p : points){
		p->flag = false;
	}
}

tsp_solver::tsp_solver(){}

void tsp_solver::read_file(std::string file_name){
	std::ifstream original_file(file_name);
	if(original_file.is_open()){
		double num1;
		double num2;
		while(original_file >> num1){
			original_file >> num2;
			point* p = new point(num1,num2);
			points.push_back(p);
		}
	}else{
        std::cout << "The file cannot be opened" << std::endl;
        original_file.close();
	}
}

void tsp_solver::run(){
	std::string file_name;
	int choise;
	double Lnn = 0;
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "                Welcome to TSP solver                " << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "Input a file for data:" << std::endl;
	std::cin >> file_name;
	std::cout << "Using data from: " << file_name << std::endl;
	read_file(file_name);
	std::cout << std::endl;
	std::cout << "You can use some of the algorithms below:" << std::endl;
	std::cout << "1. Brute Force" << std::endl;
	std::cout << "2. Nearest neighbor" << std::endl;
	std::cout << "3. Improved nearest neighbor" << std::endl;
	std::cout << "4. ACS(ant colony system) tsp algorithm" << std::endl;
	std::cout << "--->In order to run 4 you must first run 2<---" << std::endl;
	std::cout << std::endl;
	while(true){
		std::cin >> choise;
		if(choise == 1){
			std::cout << "---------------------Brute Force---------------------" << std::endl;
			Brute_force_tsp bf;
			bf.run(points);
			bf.print_details();
			std::cout << "-----------------------------------------------------" << std::endl;
		}else if(choise == 2){
			std::cout << "-------------------Nearest neighbor------------------" << std::endl;
			NN_tsp nn;
			Lnn = nn.run(points);
			nn.print_details();
			reset_points();
			std::cout << "-----------------------------------------------------" << std::endl;
		}else if(choise == 3){
			std::cout << "--------------Improved nearest neighbor--------------" << std::endl;
			INN_tsp inn;
			inn.run(points);
			inn.print_details();
			reset_points();
			std::cout << "-----------------------------------------------------" << std::endl;
		}else if(choise == 4){
			if(Lnn == 0){
				std::cout << "!!!!!You must run 2 first!!!!!" << std::endl;
			}else{
				std::cout << "----------------ACS(ant colony system)---------------" << std::endl;
				double thao = 1/(points.size()*Lnn);
				int ants = 0;
				std::cout << "Enter how many ants to spawn in one generation" << std::endl;
				std::cout << "(More ants = shorter path)" << std::endl;
				std::cin >> ants;
				ACS_System a(points,25,ants,0.1,2,0.9,thao);
				a.run(points);
				a.print_more_details();
				std::cout << "-----------------------------------------------------" << std::endl;
			}		
		}else if(choise == 5){
			break;
		}
	}
	
}

void tsp_solver::print_all_points(){
	for(point* p : points){
		p->print_point();
		std::cout << std::endl;
	}
}

tsp_solver::~tsp_solver(){
	for(point* p : points){
		delete p;
	}
}

#endif