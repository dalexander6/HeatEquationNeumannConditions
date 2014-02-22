//
//#####################################################################
//                       PaddedGridParameters2D.h 
//
//                     Padded GridParameters2D Class  
//
// A class containing parameters describing a grid
// used for the padded heat equation approx
//
//#####################################################################
//
//
#ifndef __PaddedGridParameters2D__
#define __PaddedGridParameters2D__

#include "GridParameters2D.h"
class PaddedGridParameters2D : public GridParameters2D
{
public:

	PaddedGridParameters2D()
	{
		paddingWidth = 1.0;
	}

	PaddedGridParameters2D(double xMin, double xMax, double yMin, double yMax, long mPanel, long nPanel, double newPaddingWidth) : GridParameters2D(xMin, xMax, yMin, yMax, mPanel, nPanel){
		paddingWidth = newPaddingWidth;
	}
	
	virtual PaddedGridParameters2D* clone() const{
		return new PaddedGridParameters2D(*this);
	}

	virtual double getXMin() const{
		return GridParameters2D::getXMin() - paddingWidth;
	}

	virtual double getXMax() const{
		return GridParameters2D::getXMax() + paddingWidth;
	}

	virtual double getHX() const{
		return (getXMax() - getXMin()) / (double)GridParameters2D::getXPanels();
	}
	virtual double getYMin() const{
		return GridParameters2D::getYMin() - paddingWidth;
	}

	virtual double getYMax() const{
		return GridParameters2D::getYMax() + paddingWidth;
	}

	virtual double getHY() const{
		return (getYMax() - getYMin()) / (double)GridParameters2D::getYPanels();
	}

	double paddingWidth; //the length we pad to the end of the grid
};

#endif
