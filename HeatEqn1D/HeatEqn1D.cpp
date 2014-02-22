//
// This program solves the heat equation u_t = alpha u_xx on [-1,1] with no-flow Neumann boundary conditions 

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string.h>
#include <sstream>
#include <math.h>
using namespace std;

#include "../common_files/GridFun1D.h"
#include "../common_files/TriSolver.h"
#include "../common_files/outputToGNUplot.h"
#include "CrankNicolsonOp1D.h"
#include "toolboxFunctions.h"


int main(int argc, char *argv[]){
    long    xPanel = 100; //spacial resolution
    long	tPanel = 800; //temporal resolution
	
//   Problem set up

    double xMin = 0.0; //set up initial region
    double xMax = 1.0;
    double hx   = (xMax-xMin)/(double)(xPanel);
    
	GridParameters myGrid(xMin, xMax, xPanel);		
    double tMin = 0.0;
    double tFinal = .5;
	double ht 	= (tFinal-tMin)/tPanel;

	double alpha = 1.0;
	double exercise = 2; //sets up exercise

	//number of times we output data to a text file
	int outputCount = 40;
	bool output = false; //set whether we want to output at all
	output = true;

	//so we output every numOutputs step
	int numOutputs = tPanel / outputCount;

// Echo input (using stdio since it's easier to create aligned output)

    printf("########    Crank-Nicolson   ########\n");
    printf("x in [%-6.3f, %-6.3f] \n",xMin, xMax);
    printf("Number of spacial panels	:  %-5ld   \n",xPanel);
    printf("hx			:  %-10.5f \n",hx);
    printf("ht			:  %-10.5f \n",ht);

// Initialize right hand side and iterates

    GridFun1D u(myGrid);
	GridFun1D uTrue(myGrid);
	GridFun1D uk(myGrid);
	GridFun1D ukp1(myGrid);
	
	symmetryCheck(u);

	//setup initial conditions
	//the N slot is set to 0
	initializeData(u, myGrid, exercise, 0);
	
	symmetryCheck(u);

	
	
	//instatiate relaxation operator
	CrankNicolsonOp1D crankNicolsonOp;
	crankNicolsonOp.initialize(ht, alpha, uk);

	//set up initial iterate
	uk = u;
		
	//set up filename holder
	stringstream ss;
	
	bool foundFirstAsymmetry = false;

	for(long i = 0; i < tPanel; i++){
		if(symmetryCheck(uk) == false && foundFirstAsymmetry == false){
			cout << "Step i = " << i << ", ";
			cout << "Symmetry check:  false" << endl;
//			cout << uk << endl;
			foundFirstAsymmetry = true;
		}

		getTrueSoln(uTrue, i*ht, exercise);
		if(i % numOutputs == 0 && output == true){
			outputToGNUplot(uk, "data", "HeatNormalSchemeU", i);
			//outputToGNUplot(uTrue, "data", "HeatTrueU", i);
		}

		crankNicolsonOp.apply(uk,ukp1);
		uk = ukp1;
	}
	
	//use ukp1 to store residual
	ukp1 -= uTrue;
	cout << "Final Error is: " << ukp1.normInf() << endl;	
	cout << "Final L1 norm of u is: " << LpIntegral(uk,1) << endl;
	cout << "Final L1 norm of uTrue is: " << LpIntegral(uTrue,1) << endl;

	
	//outputToGNUplot(uk, "data", "uAtEnd.dat", 0);
//	outputToGNUplot(uTrue, "data/uTrueAtEnd.dat");
	
	//STUFF valid for toy1
	/*
	outputToGNUplot(trueVelocities, tMin, tFinal, "trueVelocities.dat");
	
	GridFun1D diffVelocities = trueVelocities - velocities;
	outputToGNUplot(diffVelocities, tMin, tFinal, "diffVelocities.dat");
	
	GridFun1D diffXMins = trueXMins - xMins;
	outputToGNUplot(xMins, tMin, tFinal, "xMins.dat");
	outputToGNUplot(diffXMins, tMin, tFinal, "diffXMins.dat");
    printf("xMin at t = 0: %-10.5f, predictedxMin: %-10.5f \n",xMins[0], trueXMins[0]);
	*/
//	cout << "True error = " << uk.normInf() << "\n";
//	cout << "final numerator = " << num << "\n";
//	cout << "c/(1-c) || u_k - u_{k-1}|| = " << c/(1-c)*num << endl;
}
