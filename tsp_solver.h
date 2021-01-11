#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <string>
#include "point.h"
#include <vector>

class tsp_solver{
	std::vector<point*> points;

	void reset_points();
public:

	tsp_solver();
	void read_file(std::string file_name);
	void run();
	void print_all_points();
	~tsp_solver();
};

#endif