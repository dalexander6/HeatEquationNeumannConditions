//
// This program solves the heat equation u_t = alpha \Delta u + \nabla \cdot (u \vec v) on a box where the drift is meant to simulate no-flow Neumann boundary conditions over a region omega 
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string.h>
#include <sstream>
#include <math.h>
using namespace std;

#include "../common_files/GridFun2D.h"
#include "../common_files/BoxRegion.h"
//#include "../common_files/CircleRegion.h"
#include "../common_files/TwoCircleRegion.h"
//#include "../common_files/PolygonRegion.h"
#include "../common_files/GridParameters2D.h"
#include "../common_files/PaddedGridParameters2D.h"
#include "../common_files/GridOutput.h"
#include "CrankNicolsonApproxOp2D.h"
#include "toolboxFunctions2D.h"
#include "../common_files/Point2D.h"


int main(int argc, char *argv[]){
	/*
	vector<Point2D> vertices;
	vertices.push_back(Point2D(1,0));
	vertices.push_back(Point2D(0,1));
	vertices.push_back(Point2D(1,1));

//	PolygonRegion omega(vertices);
//	*/

	bool output = false; //set whether we output .dat files
	output = true;
    long    xPanel = 150; //spacial resolution
	long	yPanel = 150;
    long	tPanel = 20000; //temporal resolution
	
	//   Problem set up
//  double xMin = -1.0; //set up initial region
//	double yMin = -1.0;
    double xMin = 0.0; //set up initial region
    double xMax = 2.0;
	double yMin = 0.0;
	double yMax = 2.0;
	double paddingWidth = .5;

	
	GridParameters2D unpaddedGrid(xMin, xMax, yMin, yMax, xPanel, yPanel);
	PaddedGridParameters2D myGrid(xMin, xMax, yMin, yMax, xPanel, yPanel, paddingWidth);		
	//BoxRegion omega(xMin, xMax, yMin, yMax, xPanel, yPanel);

	CircleRegion omega(0.5,0.5,.5);

	CircleRegion c1(1.0,0.5,.3);
	CircleRegion c2(0.5,0.5,.2);
	//TwoCircleRegion omega(c1,c2);
	
	//CircleRegion omega(0.0,0.0,1);

    double tMin = 0.0;
    double tFinal = .018;
	double ht 	= (tFinal-tMin)/tPanel;

	double alpha = 1.0;
	double N = 800.0;

	//number of times we output data to a text file
	int outputCount = 40;

	//so we output every numOutputs step
	int numOutputs = tPanel / outputCount;

	// Echo input (using stdio since it's easier to create aligned output)
    printf("########    Crank-NicolsonApprox   ########\n");
    printf("x in [%-6.3f, %-6.3f] \n",myGrid.getXMin(), myGrid.getXMax());
    printf("Number of x panels	:  %-5ld   \n",xPanel);
    printf("Number of y panels	:  %-5ld   \n",yPanel);
    printf("Number of t panels	:  %-5ld   \n",tPanel);
	printf("N			:  %-5.0f \n", N);

	// Initialize right hand side and iterates
    GridFun2D u(myGrid);
	GridFun2D uk(myGrid);
	GridFun2D ukp1(myGrid);
	GridFun2D uTrue(myGrid);
	GridFun2D uDiff(myGrid);

	//set up penalty function
	GridFun2D Phi(myGrid);
	initializePhi(Phi, N, omega);

	//These are for adding Psi, a perturbation with non-normal direction
	//double C = .1; //coefficient of Psi term
	//double exponent = 2.0; //exponent of r in Psi term
	//initializePhiPrime(Phi, N, exponent, C);

	GridFun2D Vx(myGrid);
	GridFun2D Vy(myGrid);

	//get velocity = - \nabla \Phi
	getGradient(Phi, Vx, Vy);
	Vx *= -1.;
	Vy *= -1.;

	outputGridfunction(Phi, "data", "Phi", 0);
	outputGridfunction(Vx, "data", "Vx", 0);
	outputGridfunction(Vy, "data", "Vy", 0);

	//initial conditions
	initializeData(u, omega);
	//initializeData2(u);
//	initializeBesselData(u);
	
/*	
	int m = 1; //x wavenumber
	int n = 1; //y wavenumber
	initializeAnalyticSoln(u, m, n);
	*/
	
	
	outputGridfunction(u, "data", "u", 0);

	//instatiate relaxation operator
	CrankNicolsonApproxOp2D crankNicolsonApproxOp(ht, alpha, Vx, Vy);

	//set up initial iterate
	uk = u;
		
	for(long i = 0; i < tPanel; i++){
		//getAnalyticSoln(uTrue, m, n, i*ht);
		//initializeBesselData(uTrue, i*ht);
		if(i % numOutputs == 0 && output == true){
			outputGridfunction(uk, "data", "HeatApproxU", i);
			//outputGridfunction(uTrue, "data", "TrueU", i);
		//	uDiff = uTrue;
		//	uDiff -= uk;
			//outputGridfunction(uDiff, "data", "deltaU", i);
		}

		crankNicolsonApproxOp.apply(uk,ukp1, Vx, Vy);
		
		if(i % numOutputs == 0){
			cout << "Step i = " << i ;
			cout << ", L1 integral in omega is: " << LpIntegral(uk, omega, 1) << endl; 
			cout << ", L1 integral is: " << LpIntegral(uk, 1) << endl; 
			uTrue -= uk;
			/*
			if(LpIntegral(uTrue, omega, 1) > 1e10){
				cout << "Integral too large, exiting \n";
				return 0;
			}
			cout << "||u - uTrue||_1 = " << LpIntegral(uTrue, omega, 1) << endl;
			*/
			
		}
		uk = ukp1;

	}

	//outputToGNUplot(uk, "data", "uAtEnd.dat", 0);
	cout << "Run complete" << endl;
}
