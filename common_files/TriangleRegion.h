//
//#####################################################################
//                       TriangleRegion.h 
//
//                     triangle region Class  
//
//
//	describes a triangle in 2d
//#####################################################################
//
//
#ifndef __TriangleRegion__
#define __TriangleRegion__

#include "Region.h"
#include "Point2D.h"
#include <cmath>

using namespace std;
class TriangleRegion : public Region
{
public:
	TriangleRegion(Point2D& v1, Point2D& v2, Point2D& v3) {
		m_v1 = v1;
		m_v2 = v2;
		m_v3 = v3;



	}

	virtual double distance(double v[]) const{
		Point2D vec(v[0],v[1]);
		return distance(vec);
	}

	virtual double distance(const Point2D& v) const{
		//compute v1 vs. e13 vs e12 distance
		


	}

	/** returns > 0 if p is to right of line thru v1 and v2
	 * < 0 if to left
	 * and 0 if on
	 * if line is horizontal, >0 if above
	 * and < 0 if below
	 */
	double edgeEqn(Point2D& p, Point2D& v1, Point2D& v2){
		double dy = v1.gety() - v2.gety();
		double dx = v1.getx() - v2.getx();


		e = (p.getx() - v1.getx())*dy - (p.gety() - v1.gety())*dx;
		if( dy > 0 ){
			return e;
		}
		else{
			return -e;
		}
	}

	Point2D m_v1;
	Point2D m_v2;
	Point2D m_v3;

	Point2D m_v12;
	Point2D m_v13;

	Point2D m_v21;
	Point2D m_v23;

	Point2D m_v31;
	Point2D m_v32;

};

#endif
