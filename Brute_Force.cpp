#ifndef BRUTE_FORCE_CPP
#define BRUTE_FORCE_CPP

#include "Brute_Force.h"
#include "point.h"
#include <vector>
#include <chrono>
#include <algorithm>

double Brute_force_tsp::run(std::vector<point*> &points){
		auto start_time = std::chrono::high_resolution_clock::now();
		int num_of_points = points.size();
		int* initial_path = new int[num_of_points];
		for (int i = 0; i < num_of_points; ++i)
		{
			initial_path[i] = i;
		}

		int* best_path = new int[num_of_points];
		for (int i = 0; i < num_of_points; ++i)
		{
			best_path[i] = i;
		}
		double best_lenght = calc_path(initial_path,points);

		while(std::next_permutation(initial_path,initial_path + num_of_points)){
			double calculated_lenght = calc_path(initial_path,points);
			if(calculated_lenght < best_lenght){
				best_lenght = calculated_lenght;
				for (int i = 0; i < num_of_points; ++i)
				{
					best_path[i] = initial_path[i];
				}
			}
		}

		for (int i = 0; i < num_of_points; ++i)
		{
			the_best_path.push_back(points[best_path[i]]);
		}

		delete[] best_path;
		delete[] initial_path;
		auto stop_time = std::chrono::high_resolution_clock::now();
		algorithm_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
		the_best_lenght = best_lenght;
		return best_lenght;
	}

	double Brute_force_tsp::calc_path(int* path, std::vector<point*> &points){
		double sum = 0;
		for (int i = 0; i < points.size()-1; ++i)
		{
			sum += calc_weight(points[path[i]], points[path[i+1]]);
		}
		return sum;
	}

#endif