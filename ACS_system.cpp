#ifndef ACS_SYSTEM_CPP
#define ACS_SYSTEM_CPP

#include "ACS_system.h"
#include <vector>
#include "edge.h"
#include <chrono>
#include "point.h"
#include "ant.h"
#include <iostream>
#include <limits>
#include <cmath>

void ACS_System::clear_matrix(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i < j){
				delete adj_matrix[i*n + j];
			}		
		}
	}
}

ACS_System::ACS_System(std::vector<point*> &points,int _generations,int _generated_ants,double _alpha, double _beta, double _random_chance,double _thao){
	generations = _generations;
	generated_ants = _generated_ants;
	alpha = _alpha;
	beta = _beta;
	random_chance = _random_chance;
	thao = _thao;
	n = points.size();
	make_adj_matrix(points,thao);
}

void ACS_System::make_adj_matrix(std::vector<point*> &points,double thao){
	auto start_time = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j){
				adj_matrix.push_back(nullptr);
			}else if(i > j){
				adj_matrix.push_back(adj_matrix[j*n + i]);
			}else{
				edge* e = new edge(calc_weight(points[i],points[j]),thao);
				adj_matrix.push_back(e);
			}			
		}
	}
	auto stop_time = std::chrono::high_resolution_clock::now();
	matrix_creation_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
}

void ACS_System::print_adj_matrix(){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(adj_matrix[i*n + j]!=nullptr){
				std::cout <<" "<< adj_matrix[i*n + j]->weight << "_" << adj_matrix[i*n + j]->pheromones << " |";
			}else {
				std::cout << "  null    |";
			}
		}
		std::cout << "\n";
	}
}

int ACS_System::generate_start_pos(int min,int max){
	int n = rand() % (max - min) + min;
}

double ACS_System::run(std::vector<point*> &points){
	auto start_time = std::chrono::high_resolution_clock::now();
	double the_best_tour = std::numeric_limits<double>::max();
	for (int j = 0; j < generations; ++j)
	{
		ant* ants = new ant[generated_ants];
		for (int i = 0; i < generated_ants; ++i)
		{
			ants[i].setup(n,generate_start_pos(0,n));
		}
		for (int q = 0; q < n-1; ++q)
		{
			for (int i = 0; i < generated_ants; ++i)
			{	
				ants[i].make_step(adj_matrix,alpha,beta,random_chance,thao);
			}
		}

		//cout <<"SIZE OF MATRIX: "<< adj_matrix.size() << endl;
		// cout << "----------------Generation_"<< j+1 <<"------------------" << endl;
		// cout << "All paths on ants" << endl;
		// for (int i = 0; i < generated_ants; ++i)
		// {
		// 	cout << "ant: " << i << "lenght: " << ants[i].get_path_lenght() << endl;
		// }
		// cout << "----------------Generation_"<< j+1 <<"_Matrix------------------" << endl;
		//print_adj_matrix();
		//cout << "----------------------------------" << endl;

		
		//global updating rule
		//---------------------------------------------------------
		double best_tour = ants[0].get_path_lenght();
		int best_ant = 0;
		for (int i = 0; i < generated_ants; ++i)
		{
			if(ants[i].get_path_lenght() < best_tour){
				best_tour = ants[i].get_path_lenght();
				best_ant = i;
			}
		}

		//cout << "Best ant: " << best_ant << " Best lenght: " << best_tour << endl;

		int* path = ants[best_ant].get_path();
		if(the_best_tour > best_tour){
			the_best_tour = best_tour;
			the_best_path.clear();
			for(int i = 0; i < n; ++i){
				the_best_path.push_back(points[path[i]]);
			}
		}
		
		//rewarding the best
		for (int i = 0; i < n-1; ++i)
		{
			adj_matrix[path[i]*n + path[i+1]]->pheromones = (1.0 - alpha)*adj_matrix[path[i]*n + path[i+1]]->pheromones + (alpha*(1/best_tour));
		}

		//lowering the others
		// for(int h = 0; h < generated_ants; h++){
		// 	path = ants[h].get_path();
		// 	best_tour = ants[h].get_path_lenght();
		// 	if(h!=best_ant){
		// 		for (int i = 0; i < n-1; ++i)
		// 		{
		// 			adj_matrix[path[i]*n + path[i+1]]->pheromones =(1.0 - alpha)*adj_matrix[path[i]*n + path[i+1]]->pheromones ;
		// 		}
		// 	}
		// }
		//---------------------------------------------------------

		delete[] ants;
	}
	auto stop_time = std::chrono::high_resolution_clock::now();
	algorithm_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
	the_best_lenght = the_best_tour;
	return the_best_tour;
}

void ACS_System::print_more_details() const{
	print_details();
	std::cout << "Time for generating adjacency matrix: " 
	<< (double)matrix_creation_duration.count()/1000000 << "/" << matrix_creation_duration.count() << " seconds/microseconds " << std::endl;
	std::cout << "Time for algorithm and generating adjacency matrix: " 
	<<  (double)(algorithm_duration.count() + matrix_creation_duration.count())/1000000 << "/" 
	<< matrix_creation_duration.count() + algorithm_duration.count() << " seconds/microseconds " << std::endl;
}

ACS_System::~ACS_System(){
	clear_matrix();
}

#endif