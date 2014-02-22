// This program tests out bessel function routines
#include <iostream>
using namespace std;

#include "../../common_files/GridFun1D.h"
#include "../../common_files/GridOutput.h"
#include "../../common_files/GridParameters.h"
#include <math.h>

void initializeJ(GridFun1D& J){
	double x = 0;
	double hx = J.getHX();
	double xMin = J.getXMin();
	J.setToValue(0.0);
	for(int i = 0; i <= J.getXPanels(); i++){
		x = xMin + i*hx;

		J[i] = j0(x);
	}
	
	return;
}

int main(int argc, char *argv[]){

    double xMin = 0.0; //set up initial region
    double xMax = 10.0;
	long xPanel = 50;
	double lambda0 = 3.8317;
	GridParameters myGrid(xMin, xMax, xPanel);		
    GridFun1D J(myGrid);
	initializeJ(J);
	outputGridfunction(J, myGrid, "data", "besselFunc", 0);
	return 0;
}
