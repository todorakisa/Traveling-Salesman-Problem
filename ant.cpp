#ifndef ANT_CPP
#define ANT_CPP

#include "ant.h"
#include <vector>
#include "edge.h"
#include <cmath>
#include <limits>

ant::ant(){
	index_of_path = 0;
	size_of_arrays = 0;
	path_lenght = 0;
}

void ant::setup(int size,int start_pos){
	size_of_arrays = size;
	visited = new bool[size_of_arrays];
	path = new int[size_of_arrays];
	for (int i = 0; i < size_of_arrays; ++i)
	{
		visited[i] = false;
	}
	visited[start_pos] = true;
	path[index_of_path] = start_pos;
}

void ant::make_step(std::vector<edge*> &adj_matrix,double alpha,double beta,double random_chance, double thao){
	int index = path[index_of_path]*size_of_arrays;
	int next_city = -1;

	//formula with random chance
	//---------------------------------------------------------
	double chance = random_double();
	if(random_chance > chance){

		double max = std::numeric_limits<double>::min();
		for (int i = 0; i < size_of_arrays; ++i)
		{
			if(adj_matrix[index + i] != nullptr && visited[i] != true){
				double len = adj_matrix[index + i]->pheromones * pow(1/adj_matrix[index + i]->weight, beta);
				if(len > max){
					max = len;
					next_city = i;
				}
			}
		}

		index_of_path++;
		visited[next_city] = true;
		path[index_of_path] = next_city;
		path_lenght+= adj_matrix[index + next_city]->weight;
	}else{
		double sum = 0;
		for (int i = 0; i < size_of_arrays; ++i)
		{
			if(adj_matrix[index + i] != nullptr  && visited[i] != true){
				sum+= adj_matrix[index + i]->pheromones * pow(1/adj_matrix[index + i]->weight, beta);
			}
		}

		double sum2 = 0;
		double numche = random_double();
		for (int i = 0; i < size_of_arrays; ++i)
		{
			if(adj_matrix[index + i] != nullptr && visited[i] != true){
				double probability = adj_matrix[index + i]->pheromones * pow(1/adj_matrix[index + i]->weight, beta)/sum;
				if(numche < (probability + sum2)){
					next_city = i;
					break;
				}
				sum2+= probability;
			}
		}

		index_of_path++;
		visited[next_city] = true;
		path[index_of_path] = next_city;
		path_lenght+= adj_matrix[index + next_city]->weight;		
	}
	//---------------------------------------------------------

	//local updating rule
	//---------------------------------------------------------
	adj_matrix[index + next_city]->pheromones = (1.0 - alpha)*adj_matrix[index + next_city]->pheromones + alpha*thao;
	//---------------------------------------------------------

}

double ant::random_double(){
	double l = 0.0;
	double u = 1.0;
	return ((double)rand() * (u-l))/(double) RAND_MAX + l;
}


double ant::get_path_lenght(){
	return path_lenght;
}

int* ant::get_path(){
	return path;
}

ant::~ant(){
	delete[] visited;
	delete[] path;
}

#endif