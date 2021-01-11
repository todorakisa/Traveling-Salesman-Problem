#ifndef ANT_H
#define ANT_H

#include <vector>
#include "edge.h"

class ant{
	bool *visited;
	int* path;
	double path_lenght;
	int index_of_path;
	int size_of_arrays;
public:
	ant();
	void setup(int size,int start_pos);
	void make_step(std::vector<edge*> &adj_matrix,double alpha,double beta,double random_chance, double thao);
	double random_double();
	double get_path_lenght();
	int* get_path();
	~ant();
};

#endif