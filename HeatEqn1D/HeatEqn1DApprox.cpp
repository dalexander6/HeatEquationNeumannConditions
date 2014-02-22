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
#include "../common_files/GridOutput.h"
#include "CrankNicolsonApproxOp1D.h"
#include "../common_files/PaddedGridParameters.h"
#include "toolboxFunctions.h"

int vExponent = 2;
/** Initializes the penalty term
 * @param M is the width
 * @param N is the height
 * @param xMin, xMax are the true original regions
 */
void initializeV(GridFun1D& V, double N, GridParameters& unpaddedGrid){
	double x = 0;
	double hx = V.getHX();
	double xMin = V.getXMin();
	double unpaddedXMin = unpaddedGrid.getXMin();
	double unpaddedXMax = unpaddedGrid.getXMax();
	
	//try number 2: growing at "infinity"
	V.setToValue(0.0);
//	cout << "---------------------" << endl;
//	cout << unpaddedXMin << " " << xMin << endl;
	for(int i = 0; i <= V.getXPanels(); i++){
		x = xMin + i*hx;

		if(x < unpaddedXMin){
			V[i] = N*abs(pow(x - unpaddedXMin,vExponent));
		}
		else if(x > unpaddedXMax){
			V[i]= -N*abs(pow(x - unpaddedXMax,vExponent));
		}
	}
	
	return;
}

int main(int argc, char *argv[]){

	bool output = false; //set whether we output .dat files
	output = true;
	bool verbosity = false; //do we output stuff at lots of times
	verbosity = true;
    long    xPanel = 300; //spacial resolution
    long	tPanel = 2000; //temporal resolution
	
	//   Problem set up
	double xMin = 0.0; //set up initial region
    double xMax = 1.0;
	double paddingWidth = 1.0;
	
    double tMin = 0.0;
    double tFinal = .3;

	double alpha = 1.0;
	double N = 100;
	double exercise = 2;

	//get params from input
	if(argc < 4){ 
		cout << "Needs arguments for xPanel, tPanel, Nn\n"; 
		cout << "using preset values of" << endl;
		cout << "xPanel = " << xPanel << ", tPanel = " << tPanel << ", N = " << N << endl;
	}
	else{
		xPanel = atoi(argv[1]);
		tPanel = atoi(argv[2]);
		N = atoi(argv[3]);
	}	
	double ht 	= (tFinal-tMin)/tPanel;
	GridParameters unpaddedGrid(xMin, xMax, xPanel);
	PaddedGridParameters myGrid(xMin, xMax, xPanel, paddingWidth);		
    
	//number of times we output data to a text file
	int outputCount = 40;

	//so we output every numOutputs step
	int numOutputs = tPanel / outputCount;

	// Echo input (using stdio since it's easier to create aligned output)
	if(verbosity){
		printf("########    Crank-NicolsonApprox   ########\n");
		printf("x in [%-6.3f, %-6.3f] \n",myGrid.getXMin(), myGrid.getXMax());
		printf("Number of spacial panels	:  %-5ld   \n",xPanel);
		printf("hx			:  %-10.5f \n",myGrid.getHX());
		printf("ht			:  %-10.5f \n",ht);
		printf("N			:  %-10.0f \n",N);
	}

	// Initialize right hand side and iterates
    GridFun1D u(myGrid);
	GridFun1D uk(myGrid);
	GridFun1D ukp1(myGrid);
	GridFun1D uTrue(myGrid);

	//set up penalty function
	GridFun1D V(myGrid);
	initializeV(V, N, unpaddedGrid);

	//V.setToValue(0);

	outputGridfunction(V, myGrid, "data", "V", 0);
	//initial conditions
	initializeData(u, myGrid, exercise, N);
	
	//instatiate relaxation operator
	CrankNicolsonApproxOp1D crankNicolsonApproxOp(ht, alpha, myGrid, V);

	//set up initial iterate
	uk = u;
		
	double L1mass = 0;
	double Lerror = 0;
	for(long i = 0; i < tPanel; i++){
		getTrueSoln(uTrue, i*ht, exercise);

		if(i % numOutputs == 0 && output == true){
			outputGridfunction(uk, myGrid, "data", "HeatApproxU", i);
			outputGridfunction(uTrue, myGrid, "data", "HeatTrueU", i);
			outputGridfunction(uTrue, myGrid, "data", "HeatTrueU", i);
			cout << "output created at i = " << i << ", t = " << i*ht << endl;
		}

		crankNicolsonApproxOp.apply(uk,ukp1, V);
		uk = ukp1;
		//cout error
		if(i % numOutputs == 0 && verbosity == true){
			cout << "Step i = " << i ;
			L1mass = LpIntegral(uk,1);
			cout << ", L1 integral is: " << L1mass; 
			cout << ", u[1] = " << uk[1] << endl;
			ukp1 -= uTrue;
			outputGridfunction(ukp1, myGrid, "data", "error", i);
			Lerror = LpIntegral(ukp1, -1) ;
			cout << "||u - uTrue||_inf = " << Lerror ;
			Lerror = LpIntegral(ukp1, 1) ;
			cout << ", ||u - uTrue||_1 = " << Lerror << endl;
		}

	}
	L1mass = LpIntegral(uk,1);
	ukp1 -= uTrue;
	Lerror = LpIntegral(ukp1, -1) ;
	
	//cout << vExponent << ", " << N << ", " << xPanel << ", " << tPanel << ", " << Lerror<< ", " << L1mass << endl;
	cout << "N: " << N << ", " << xPanel << " x " << tPanel << ". Final Linf error: " << Lerror<< ", final mass: " << L1mass << "." << endl;
	if(verbosity == false){
		cout << Lerror << endl;
	}

	//outputToGNUplot(uk, "data", "uAtEnd.dat", 0);
}
