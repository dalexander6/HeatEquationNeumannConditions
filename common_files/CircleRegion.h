//
//#####################################################################
//                       CircleRegion.h 
//
//                     circle region Class  
//
//
//	describes a circle in 2d
//#####################################################################
//
//
#ifndef __CircleRegion__
#define __CircleRegion__

#include "Region.h"
#include "Point2D.h"
#include <cmath>

using namespace std;
class CircleRegion : public Region
{
public:
	CircleRegion(double x0, double y0, double radius) : center(x0, y0) {
		m_x0 = x0;
		m_y0 = y0;
		m_radius = radius;

	}

	virtual double distance(double v[]) const{
		double x = v[0];
		double y = v[1];

		double distToCenter = pow(pow(x - m_x0,2) + pow(y-m_y0,2),.5);

		if( distToCenter <= m_radius){
			//inside the circle case
			return 0;
		}
		else{
			return distToCenter - m_radius;
		}
	}

	virtual double distance(const Point2D& v) const{
		double distToCenter = v.getDistance(center);

		if( distToCenter <= m_radius){
			//inside the circle case
			return 0;
		}
		else{
			return distToCenter - m_radius;
		}
	}

	Point2D center;
	double m_x0;
	double m_y0;
	double m_radius;

};

#endif
