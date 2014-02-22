//
//#####################################################################
//                       GridParameters2D.h 
//
//                     GridParameters2D Class  
//
// A class containing parameters describing a grid
//
// Math 270E                                          Version 3/1/2013
//#####################################################################
//
//
#ifndef __GridParameters2D__
#define __GridParameters2D__

class GridParameters2D
{
public:

	GridParameters2D(){
		xMin  = 0.0; xMax  = 1.0;
		m  = 0;
		hx = 1;
		yMin = 0.0; 
		yMax = 1.0;
		n = 0;
		hy = 1;
	}

	GridParameters2D(const GridParameters2D& G){
		xMin  = G.xMin; xMax  = G.xMax;
		m  = G.m;
		hx = G.hx;
		yMax = G.yMax; yMin = G.yMin;
		n = G.n;
		hy = G.hy;
	}

	GridParameters2D(double xMin, double xMax, double yMin, double yMax, long mPanel, long nPanel)
	{
		this->xMin  = xMin; this->xMax  = xMax;
		this->yMin = yMin; this->yMax = yMax;
		m  = mPanel;
		n = nPanel;
		hx = (xMax-xMin)/double(m);
		hy = (yMax-yMin)/double(n);
	}

	//virtual ~GridParameters2D() {}
	
	virtual GridParameters2D* clone() const{
		return new GridParameters2D(*this);
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

	virtual double getYMin() const{
		return yMin;
	}

	virtual double getYMax() const{
		return yMax;
	}

	virtual double getHY() const{
		return (yMax - yMin) / (double)n;
	}

	double getYPanels() const{ return n; }
private:


	double xMin;       // Computational Region is [xMin,xMax] x [yMin, yMax]
	double xMax;

	double hx;      // mesh width in x direction
	long   m;       // Number of panels in the x direction

	double yMin;     
	double yMax;

	double hy;      // mesh width in y direction
	long   n;       // Number of panels in the y direction

};

#endif
