#ifndef _GridFun1D_
#define _GridFun1D_
//#include "vectorDebug.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "GridParameters.h"
#include "PaddedGridParameters.h"
using namespace std;

class GridFun1D{
	friend ostream& operator<<(ostream&, const GridFun1D&);

	public:
		GridFun1D();
		GridFun1D(const GridFun1D&);
		GridFun1D(long, double, double);
		GridFun1D(const GridParameters&);
		~GridFun1D();
		GridFun1D operator =(const GridFun1D&);
		GridFun1D operator +=(const GridFun1D&);
		GridFun1D operator -=(const GridFun1D&);
		GridFun1D operator *=(double);
		GridFun1D operator /=(double);
		double getXMin() const { return myGrid->getXMin(); }
		double getXMax() const { return myGrid->getXMax(); }
		int getXPanels() const { return myGrid->getXPanels(); }
		double getHX() const { return myGrid->getHX(); }
		double& operator[](int);
		const double& operator[](int) const;

		void setToValue(double);
		double normInf();
private:
		double hx;
		double xMin;
		double xMax;
		double xPanel;
		GridParameters* myGrid;
		vector<double> values;
};
#endif
