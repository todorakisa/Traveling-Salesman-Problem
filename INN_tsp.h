#ifndef INN_TSP_H
#define INN_TSP_H

#include "tsp_solution.h"
#include "point.h"
#include <vector>

class INN_tsp : virtual public tsp_solution{
public:
	point* find_best_start(std::vector<point*> &points);
	double run(std::vector<point*> &points);
};

#endif