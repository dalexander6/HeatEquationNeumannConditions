#include "Point2D.h"

Point2D::Point2D() { x = 0; y = 0; return;}

Point2D::Point2D(double a, double b) { x = a; y = b; return;}

double Point2D::getx() const { return x;}
double Point2D::gety() const { return y;}

void Point2D::setx(double a) { x = a; return; }
void Point2D::sety(double b) { y = b; return; }

void Point2D::print() {
	cout<<"("<<x<<","<<y<<")";
	return;
}

void Point2D::print(int a) {
	print(); cout<<endl;
	return;
}

ostream& operator<<(ostream& out, Point2D& p){
	out << "(" << p.getx() << "," << p.gety() << ")";
	return out;

}

double Point2D::getDistance(const Point2D& v) const{
	return pow(pow(x - v.x,2) + pow(y - v.y,2), 2); 
}

