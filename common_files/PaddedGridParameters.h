//
//#####################################################################
//                       PaddedGridParameters.h 
//
//                     Padded GridParameters Class  
//
// A class containing parameters describing a grid
// used for the padded heat equation approx
//
//#####################################################################
//
//
#ifndef __PaddedGridParameters__
#define __PaddedGridParameters__

#include "GridParameters.h"
class PaddedGridParameters : public GridParameters
{
public:

	PaddedGridParameters()
	{
		paddingWidth = 1.0;
	}

	PaddedGridParameters(double xMin, double xMax ,long mPanel, double newPaddingWidth) : GridParameters(xMin, xMax, mPanel){
		paddingWidth = newPaddingWidth;
	}
	
	virtual PaddedGridParameters* Clone() const{
		return new PaddedGridParameters(*this);
	}

	virtual double getXMin() const{
		return GridParameters::getXMin() - paddingWidth;
	}

	virtual double getXMax() const{
		return GridParameters::getXMax() + paddingWidth;
	}

	virtual double getHX() const{
		return (getXMax() - getXMin()) / (double)GridParameters::getXPanels();
	}

	double paddingWidth; //the length we pad to the end of the grid
};

#endif
