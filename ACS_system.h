#ifndef ACS_SYSTEM_H
#define ACS_SYSTEM_H

#include "tsp_solution.h"
#include <vector>
#include "edge.h"
#include <chrono>
#include "point.h"

class ACS_System : virtual public tsp_solution{
	int n;
	int generations;
	int generated_ants;
	double alpha;
	double beta;
	double random_chance;
	double thao;
	std::vector<edge*> adj_matrix;	
	std::chrono::microseconds matrix_creation_duration;

	void clear_matrix();

public:

	ACS_System(std::vector<point*> &points,int _generations,int _generated_ants,double _alpha, double _beta, double _random_chance,double _thao);
	void make_adj_matrix(std::vector<point*> &points,double thao);
	void print_adj_matrix();
	int generate_start_pos(int min,int max);
	double run(std::vector<point*> &points);
	void print_more_details() const;
	~ACS_System();
};

#endif