#ifndef TSP_SOLUTION_CPP
#define TSP_SOLUTION_CPP

#include "tsp_solution.h"
#include <list>
#include <vector>
#include "point.h"
#include <chrono>
#include <iostream>
#include <cmath>

tsp_solution::tsp_solution(){}

double tsp_solution::calc_weight(point* start, point* end) const{
	double x = end->x - start->x;
	double y = end->y - start->y;
	double result = sqrt(x*x + y*y);
	return result;
}

void tsp_solution::print_path() const{
	for(std::list<point*>::const_iterator it = the_best_path.begin(); it != the_best_path.end(); it++){
		(*it)->print_point();
		std::list<point*>::const_iterator z = it;
		if(++z == the_best_path.end()){
			std::cout << std::endl;
		}else{
			std::cout << "->";
		}	
	}
}

void tsp_solution::print_details() const{
	std::cout << "Best lenght of path: " << the_best_lenght << std::endl;
	std::cout << "Time for the algorithm: "<< (double)algorithm_duration.count()/1000000 << "/" << algorithm_duration.count() << " seconds/microseconds "<< std::endl;
	std::cout << "Do you want to see the path? y/n" << std::endl;
	char answer;
	std::cin >> answer;
	if(answer == 'y'){
		print_path();
	}
}

tsp_solution::~tsp_solution(){}

#endif