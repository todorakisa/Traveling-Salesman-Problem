#include<iostream>
#include "tsp_solver.h"
using namespace std;

int main(){
	srand(time(NULL));
	tsp_solver s;
	s.run();
	return 0;
}