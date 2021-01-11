#ifndef NN_TSP_H
#define NN_TSP_H

#include "tsp_solution.h"
#include <vector>
#include "point.h"

class NN_tsp : virtual public tsp_solution{
public:
	double run(std::vector<point*> &points);
};

#endif