#ifndef _Point2D_
#define _Point2D_
#include <iostream>
#include <cmath>


using namespace std;


class Point2D {
public:
	// Constructors
	Point2D();
	Point2D(double a, double b);

	// Gets-rs
	double getx() const ;
	double gety() const ;

	// Set-rs
	void setx(double a);
	void sety(double b);

	// Print functions
	void print();
	void print(int a);
	double getDistance(const Point2D& y) const;


private:
	double x;
	double y;
};

#endif
