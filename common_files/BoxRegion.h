#ifndef __BoxRegion__
#define __BoxRegion__
//
//#####################################################################
//                       BoxRegion.h 
//
//                     box region Class  
//
//
//	describes a box in 2d
//#####################################################################
//
//

#include "Region.h"
#include "GridParameters2D.h"
#include <cmath>

using namespace std;
class BoxRegion : public Region, public GridParameters2D
{
public:
	BoxRegion(double xMin, double xMax, double yMin, double yMax, long mPanel, long nPanel) : GridParameters2D(xMin, xMax, yMin, yMax, mPanel, nPanel){
	}

	virtual double distance(double v[]) const{
		double x = v[0];
		double y = v[1];

		if( getXMin() <= x && x <= getXMax() ){
			//inside the box case
			if( getYMin() <= y && y <= getYMax()){
				return 0.0;
			}
			//below the box
			else if( y < getYMin() ){
				return getYMin() - y;
			}
			//above the box
			else if( y > getYMax() ){
				return y - getYMax();
			}
		}
		else if( getYMin() <= y && y <= getYMax() ){
			//to left of box
			if( x <= getXMin()){
				return getXMin() - x;
			}
			//to right of box
			else if( x > getXMax()){
				return x - getXMax();
			}
		}
		//top left corner
		else if( x < getXMin() && y > getYMax() ){
			return pow(pow(x - getXMin(), 2) + pow(y - getYMax(), 2), 0.5);
		}
		//top right corner
		else if( x > getXMax() && y > getYMax() ){
			return pow(pow(x - getXMax(), 2) + pow(y - getYMax(), 2), 0.5);
		}
		//bottom right corner
		else if( x > getXMax() && y < getYMin() ){
			return pow(pow(x - getXMax(), 2) + pow(y - getYMin(), 2), 0.5);
		}
		//bottom left corner
		else if( x < getXMin() && y < getYMin() ){
			return pow(pow(x - getXMin(), 2) + pow(y - getYMin(), 2), 0.5);
		}
		else{
			cout << "Shouldn't reach here" << endl;
		}

		return -1;
	}

	virtual double distance(Point2D& v) const{
		double x = v.getx();
		double y = v.gety();

		if( getXMin() <= x && x <= getXMax() ){
			//inside the box case
			if( getYMin() <= y && y <= getYMax()){
				return 0.0;
			}
			//below the box
			else if( y < getYMin() ){
				return getYMin() - y;
			}
			//above the box
			else if( y > getYMax() ){
				return y - getYMax();
			}
		}
		else if( getYMin() <= y && y <= getYMax() ){
			//to left of box
			if( x <= getXMin()){
				return getXMin() - x;
			}
			//to right of box
			else if( x > getXMax()){
				return x - getXMax();
			}
		}
		//top left corner
		else if( x < getXMin() && y > getYMax() ){
			return pow(pow(x - getXMin(), 2) + pow(y - getYMax(), 2), 0.5);
		}
		//top right corner
		else if( x > getXMax() && y > getYMax() ){
			return pow(pow(x - getXMax(), 2) + pow(y - getYMax(), 2), 0.5);
		}
		//bottom right corner
		else if( x > getXMax() && y < getYMin() ){
			return pow(pow(x - getXMax(), 2) + pow(y - getYMin(), 2), 0.5);
		}
		//bottom left corner
		else if( x < getXMin() && y < getYMin() ){
			return pow(pow(x - getXMin(), 2) + pow(y - getYMin(), 2), 0.5);
		}
		else{
			cout << "Shouldn't reach here" << endl;
		}

		return -1;
	}
};

#endif
