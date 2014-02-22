#ifndef _toolboxFunctions_
#define _toolboxFunctions_

#include "../common_files/Region.h"
#include "../common_files/Point2D.h"
#include "../common_files/GridFun2D.h"
#include <math.h>

using namespace std;

const double PI  =3.141592653589793238462;

void initializePhi(GridFun2D& Phi, double N, Region& omega);
void initializePhiPrime(GridFun2D& Phi, double N, double, double);

/** Returns a vector containing the prescribed initial data on the grid
	We are making the initial data be (.5 - x*x)_+
	@param myGridFun is number of panels
	*/
void initializeData(GridFun2D&);
void initializeData2(GridFun2D&);
void initializeData(GridFun2D&, const Region&);
void initializeAnalyticSoln(GridFun2D&, int, int);
double getTestBesselSoln(double, double, double);
void initializeBesselData(GridFun2D&);
void initializeBesselData(GridFun2D&, double);
void getAnalyticSoln(GridFun2D&, int, int, double);

/**print a vector of doubles
 */
ostream& operator<<(ostream&, vector<double>);

/** Returns the Lp integral of the input
 * p defaults to 1
 */
double LpIntegral(const GridFun2D&, double p = 1);

/** Returns the Lp integral of the input over region omega
 * p defaults to 1
 */
double LpIntegral(const GridFun2D&, const Region& omega, double p = 1);

/** computes the gradient of first arg, puts it in second and third args
 */
void getGradient(const GridFun2D&, GridFun2D&, GridFun2D&);
#endif
