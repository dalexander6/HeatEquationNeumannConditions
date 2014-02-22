//
//#####################################################################
//                       GridParameters.h 
//
//                     GridParameters Class  
//
// A class containing parameters describing a grid
//
// Math 270E                                          Version 3/1/2013
//#####################################################################
//
//
#ifndef __GridParameters__
#define __GridParameters__

class GridParameters
{
public:

	GridParameters()
	{
		xMin  = 0.0; xMax  = 1.0;
		m  = 0;
		hx = 1;
	}

	GridParameters(const GridParameters& G)
	{
		xMin  = G.xMin; xMax  = G.xMax;
		m  = G.m;
		hx = G.hx;
	}

	GridParameters(double xMin, double xMax ,long mPanel)
	{
		this->xMin  = xMin; this->xMax  = xMax;
		m  = mPanel;
		hx = (xMax-xMin)/double(m);
	}
	
	virtual GridParameters* Clone() const{
		return new GridParameters(*this);
	}

	virtual double getXMin() const{
		return xMin;
	}

	virtual double getXMax() const{
		return xMax;
	}

	virtual double getHX() const{
		return (xMax - xMin) / (double)m;
	}

	double getXPanels() const{ return m; }
private:


	double xMin;       // Computational Region is [xMin,xMax]
	double xMax;

	double hx;      // mesh width in x direction
	
	long   m;       // Number of panels in the x direction

};

#endif
