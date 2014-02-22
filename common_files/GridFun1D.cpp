#include "GridFun1D.h"
#include <assert.h>

GridFun1D::GridFun1D(){
	myGrid = NULL;
	cout << "Called default constructor";
}

GridFun1D::GridFun1D(const GridFun1D& G){
	hx = G.hx;
	xMin = G.xMin;
	xMax = G.xMax;
	xPanel = G.xPanel;
	values = G.values;
	myGrid = G.myGrid->Clone();
}

GridFun1D::GridFun1D(long xPanel, double xMin, double xMax){
	this->xMin = xMin;
	this->xMax = xMax;
	this->xPanel = xPanel;
	hx = (xMax - xMin)/xPanel;
	values.resize(xPanel+1,0.0);
}

/*
GridFun1D::GridFun1D(const GridParameters& gridParams){
	xMin = gridParams.getXMin();
	xMax = gridParams.getXMax();
	xPanel = gridParams.m;
	hx = gridParams.getHX();
	values.resize(xPanel+1,0.0);
}
*/

GridFun1D::GridFun1D(const GridParameters& gridParams){
	myGrid = gridParams.Clone();
	xMin = gridParams.getXMin();
	xMax = gridParams.getXMax();
	xPanel = gridParams.getXPanels();
	hx = gridParams.getHX();

	values = vector<double>(getXPanels()+1,0.0);
}

GridFun1D::~GridFun1D(){
	delete myGrid;
}


GridFun1D GridFun1D::operator=(const GridFun1D& G){
	if(this != &G){
		hx = G.hx;
		xMin = G.xMin;
		xMax = G.xMax;
		xPanel = G.xPanel;
		values = G.values;
		delete myGrid;

		myGrid = G.myGrid->Clone();
	}

	return *this;
}

GridFun1D GridFun1D::operator+=(const GridFun1D& G){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		values[i] += G[i];
	}
	return *this;
}

GridFun1D GridFun1D::operator-=(const GridFun1D& G){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		values[i] -= G[i];
	}
	return *this;
}


GridFun1D GridFun1D::operator*=(double alpha){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		values[i] *= alpha;
	}
	return *this;
}


GridFun1D GridFun1D::operator/=(double alpha){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		values[i] /= alpha;
	}
	return *this;
}

double& GridFun1D::operator[](int i){
	assert(i >= 0 && i < values.size());
	return values[i];
}

const double& GridFun1D::operator[](int i) const{
	return values[i];
}

void GridFun1D::setToValue(double d){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		values[i] = d;
	}		
	return;
}

double GridFun1D::normInf(){
	double max = 0;
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		if(abs(values[i]) > max){
			max = abs(values[i]);
		}
	}
	return max;
}

ostream& operator<<(ostream& outStream, const GridFun1D& G){
	for(long i = 0; i <=  G.getXPanels(); i++)
	{ 
	  outStream <<  setw(5) << G[i] << " ";
	  outStream << endl;
	}
	return outStream;
}
