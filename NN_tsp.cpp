#ifndef NN_TSP_CPP
#define NN_TSP_CPP

#include "NN_tsp.h"
#include <vector>
#include "point.h"
#include <chrono>
#include <limits>

double NN_tsp::run(std::vector<point*> &points){
	auto start_time = std::chrono::high_resolution_clock::now();
	int size = points.size();
	double result = 0;
	double min_edge_weight;
	point* min_edge_point;
	point* curr;

	start = points.front();
	start->flag = true;
	the_best_path.push_back(start);
	curr = start;
	
	for (int i = 0; i < size; ++i)
	{
		min_edge_weight = std::numeric_limits<double>::max();
		bool met_all_points = true;
		for(point* p : points){
			if(p->flag == false){
				met_all_points = false;
				double edge_weight = calc_weight(curr, p);
				if(edge_weight < min_edge_weight){
					min_edge_weight = edge_weight;
					min_edge_point = p;
				}
			}	
		}
		if(!met_all_points){
			the_best_path.push_back(min_edge_point);
			result += min_edge_weight;
			curr = min_edge_point;
			curr->flag = true;
		}	
	}
	auto stop_time = std::chrono::high_resolution_clock::now();
	algorithm_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
	the_best_lenght = result;
	return result;	
}

#endif