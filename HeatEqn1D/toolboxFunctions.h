#ifndef _toolboxFunctions_
#define _toolboxFunctions_

#include "../common_files/GridFun1D.h"
#include "../common_files/PaddedGridParameters.h"

using namespace std;

const double PI  =3.141592653589793238462;

/** Returns a vector containing the prescribed initial data on the grid
	@param myGridFun is number of panels
	@param Exercise controls which test we are running.
	1 = (.5 - x*x)_+
	2 = cos(2*PI*x)+1
	*/
void initializeData(GridFun1D&, GridParameters&, int Exercise, int N);

/** Checks whether gridFun is symmetric, up to a tolerance
 */
bool symmetryCheck(const GridFun1D&, double tolerance = 1.0e-9, int verbosity = 0);

bool symmetryCheck(const vector<double>, double tolerance = 1.0e-9, int verbosity = 0);

//Gets true solution for given exercise
//@param exercise controls which test solution we are getting
//1: See 201.ev1.12.Lec32.pdf Example 3 (which is slightly wrong)
//2: soln is e^{-4pi^2 t} cos(2pi x) + 1
void getTrueSoln(GridFun1D&, double, int Exercise);

/**print a vector of doubles
 */
ostream& operator<<(ostream&, vector<double>);

/** Returns the Lp integral of the input
 * p defaults to 1
 */
double LpIntegral(const GridFun1D&, double p = 1);

#endif
