#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "tsp_solution.h"
#include "point.h"
#include <vector>

class Brute_force_tsp : virtual public tsp_solution{
public:

	double run(std::vector<point*> &points);
	double calc_path(int* path, std::vector<point*> &points);
};

#endif