#ifndef POINT_CPP
#define POINT_CPP

#include "point.h"
#include <iostream>

point::point(double x_,double y_){
	x=x_;
	y=y_;
	flag = false;
}

void point::print_point(){
	std::cout << "(" << x << "," << y << ")";
}

#endif