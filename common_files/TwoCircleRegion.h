//
//#####################################################################
//                       TwoCircleRegion.h 
//
//                     circle region Class  
//
//
//	describes a region of the overlap of two circles in 2d 
//#####################################################################
//
//
#ifndef __TwoCircleRegion__
#define __TwoCircleRegion__

#include "Region.h"
#include "CircleRegion.h"

using namespace std;
class TwoCircleRegion : public Region
{
public:
	TwoCircleRegion(CircleRegion& c1, CircleRegion& c2) : m_Circle1(c1), m_Circle2(c2) {
	}

	virtual double distance(double v[]) const{
		double distTo1 = m_Circle1.distance(v);
		double distTo2 = m_Circle2.distance(v);
		
		//dist to two circles is minimum of distance to each
		double minDist = distTo1 < distTo2 ? distTo1 : distTo2;
		return minDist;
	}

	CircleRegion m_Circle1;
	CircleRegion m_Circle2;

};

#endif
