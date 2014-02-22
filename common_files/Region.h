//
//#####################################################################
//                       Region.h 
//
//                     Region Class  
//
// This class describes a region by letting the user find the distance to the boundary
//
//#####################################################################
//
//
#ifndef __Region__
#define __Region__
#include "Point2D.h"



using namespace std;

class Region
{
public:

	/**Returns the distance of (x,y) to the region
	 */
	virtual double distance(double v[]) const = 0;
	virtual double distance(const Point2D&) const { return -1; };
	 
};

#endif
