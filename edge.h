#ifndef EDGE_H
#define EDGE_H

struct edge{
	double weight;
	double pheromones;

	edge(double w_,double p_);
};

#endif