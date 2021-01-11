#ifndef POINT_H
#define POINT_H

struct point{
	double x;
	double y;
	bool flag;

	point(double x_,double y_);
	void print_point();
};

#endif