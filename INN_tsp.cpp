#ifndef INN_TSP_CPP
#define INN_TSP_CPP

#include "INN_tsp.h"
#include "point.h"
#include <vector>
#include <chrono>
#include <limits>

point* INN_tsp::find_best_start(std::vector<point*> &points){
	point* result;
	double min_lenght = std::numeric_limits<double>::min();;
	for(point* p1 : points){
		double lenght = 0;
		for(point* p2 : points){
			lenght += calc_weight(p1,p2);
		}
		if(lenght > min_lenght){
			min_lenght = lenght;
			result = p1;
		}
	}
	return result;
}

double INN_tsp::run(std::vector<point*> &points){
	auto start_time = std::chrono::high_resolution_clock::now();
	int size = points.size();
	double result = 0;
	double min_edge_weight;
	point* min_edge_point;
	point* curr;

	start = find_best_start(points);
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