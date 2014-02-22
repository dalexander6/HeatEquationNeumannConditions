#ifndef _GridFun2D_
#define _GridFun2D_
#include <vector>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "DoubleArray2D.h"
#include "GridParameters2D.h"

using namespace std;

class GridFun2D{
	friend ostream& operator<<(ostream&, const GridFun2D&);

public:
	GridFun2D(const GridParameters2D&);
	GridFun2D(const GridFun2D&);
	~GridFun2D();

	//operators
	GridFun2D operator =(const GridFun2D&);
	GridFun2D operator +=(const GridFun2D&);
	GridFun2D operator -=(const GridFun2D&);
	GridFun2D operator *=(double);
	GridFun2D operator /=(double);
	double& operator()(int, int);
	const double operator()(int,int) const;

	//get-ers
	double getXMin() const { return myGrid->getXMin(); }
	double getXMax() const { return myGrid->getXMax(); }
	int getXPanels() const { return myGrid->getXPanels(); }
	double getHX() const { return myGrid->getHX(); }
	double getYMin() const { return myGrid->getYMin(); }
	double getYMax() const { return myGrid->getYMax(); }
	int getYPanels() const { return myGrid->getYPanels(); }
	double getHY() const { return myGrid->getHY(); }

	//misc functions
	void setToValue(double);
	double normInf();

private:
	void copy(const GridFun2D& G);
	DoubleArray2D values;
	GridParameters2D* myGrid;
		
};
#endif
