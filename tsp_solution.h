#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H

#include <list>
#include <vector>
#include "point.h"
#include <chrono>

class tsp_solution{

protected:
	std::list<point*> the_best_path;
	double the_best_lenght;
	point* start;
	std::chrono::microseconds algorithm_duration;

public:
	tsp_solution();
	virtual double run(std::vector<point*> &points) = 0;
	double calc_weight(point* start, point* end) const;
	void print_path() const;
	void print_details() const;
	virtual ~tsp_solution();
};

#endif