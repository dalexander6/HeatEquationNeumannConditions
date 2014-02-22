#include "toolboxFunctions.h"

/** Returns a vector containing the prescribed initial data on the grid
	If exercise 1: We are making the initial data be (.5 - x*x)_+
	if exercise 2: We are making the initial data be cos(2pi x) + 1.
	@param myGridFun is number of panels
	*/
void initializeData(GridFun1D& myGridFun, GridParameters& gridParams, int Exercise, int N){
	double x = 0;
	for(int i = 0; i <= gridParams.getXPanels(); i++){
		x = gridParams.getXMin() + i*gridParams.getHX();

		if(Exercise == 1){
			//See 201.ev1.12.Lec32.pdf Example 3
			//if |x| < 1, function is x(1-x).  If not, initialize to 0
			myGridFun[i] = (x >= 0 && x <= 1 ? x*(1-x) : 0);
		}
		if(Exercise == 2){
			if(x >= 0 && x <= 1){
				myGridFun[i] =  cos(2*PI*x)+1;
			}
			if(x < 0){
				myGridFun[i] = 2*exp(N*pow(x,3));
			}
			if(x > 1){
				myGridFun[i] = 2*exp(-N*pow(x-1,3));
			}

		}
		
	}
	return;
}

/** Checks whether gridFun is symmetric, up to a tolerance
 * @param gridFun is the thing we check for symmetry
 * @param tolerance is the symmetry tolerance for numerical error (default value: 1e-9)
 * @param verbosity sets how much output we give, (default value: 0 for no output)
 * @return true iff gridFun is symmetric up to tolerance
 */
bool symmetryCheck(const GridFun1D& gridFun, double tolerance, int verbosity){
	int i = 0;
	int j = gridFun.getXPanels();
	bool foundAsymmetry = false;
	while(i < j){
		if(abs(gridFun[i] - gridFun[j]) > tolerance){
			foundAsymmetry = true;
			if(verbosity == 1){
				cout << "Asymmetry found in " << &gridFun << endl;
			}
			break;
		}
		i++;
		j--;
	}

	return !foundAsymmetry;
}

/** Checks whether myvec is symmetric, up to a tolerance
 * @param gridFun is the thing we check for symmetry
 * @param tolerance is the symmetry tolerance for numerical error (default value: 1e-9)
 * @param verbosity sets how much output we give, (default value: 0 for no output)
 * @return true iff gridFun is symmetric up to tolerance
 */
bool symmetryCheck(const vector<double> myvec, double tolerance, int verbosity){
	int i = 0;
	int j = myvec.size() - 1;
	bool foundAsymmetry = false;
	while(i < j){
		if(abs(myvec[i] - myvec[j]) > tolerance){
			foundAsymmetry = true;
			if(verbosity == 1){
				cout << "Asymmetry found in " << &myvec << endl;
			}
			break;
		}
		i++;
		j--;
	}

	return !foundAsymmetry;
}

//Gets true solution for given exercise
//@param exercise controls which test solution we are getting
//1: See 201.ev1.12.Lec32.pdf Example 3 (which is slightly wrong)
//2: soln is e^{-4pi^2 t} cos(2pi x) + 1
void getTrueSoln(GridFun1D& trueSoln, double t, int Exercise){
	double x = 0;
	double toReturn = 0;
	for(int i = 0; i <= trueSoln.getXPanels(); i++){
		x = trueSoln.getXMin() + i*trueSoln.getHX();

		if(Exercise == 1){
		//solution is a fourier series so we only compute some terms.  fortunately higher modes decay faster.
			int numTerms = 200;
			toReturn = 1./6;
			for(int j = 1; j < numTerms; j++){
				toReturn -= 1/(j*j*PI*PI)*exp(-4*j*j*PI*PI*t)*cos(2*j*PI*x);
			}
			trueSoln[i] = toReturn;
		}
		else if(Exercise == 2){
			trueSoln[i] = exp(-4*PI*PI*t)*cos(2*PI*x) + 1;
		}
		else{
			cout << "exercise invalid" << endl;
		}

		//if we are on a bigger grid we should make solution 0 outside of it
		if(x < 0 || x > 1){
			trueSoln[i] = 0;
		}
	}

	return;
}

ostream& operator<<(ostream& out, vector<double> vec){
	out << "(";
	for(unsigned int i = 0; i < vec.size(); i++){
		out << vec[i] << ", ";
	}
	out << ")";
	return out;
}

/** Returns the Lp integral of the input
 * @param p specifies the L^p norm
 * if p = -1, taken as Linf norm
 */
double LpIntegral(const GridFun1D& v, double p){
	double sum = 0;
	double x = 0;

	//p == -1: L_inf norm
	if(p == -1){
		for(int i = 0; i < v.getXPanels(); i++){
			x = v.getXMin() + i*v.getHX();
			//let's integrate only from [0,1]
			if(x >= 0 && x <= 1){
				if(sum < fabs(v[i])){
					sum = fabs(v[i]);
				}
			}
		}
		return sum;
	}

	for(int i = 0; i < v.getXPanels(); i++){
		x = v.getXMin() + i*v.getHX();
		//let's integrate only from [0,1]
		if(x >= 0 && x <= 1){
			sum += pow(fabs(v[i]) , p);
		}
	}
	return pow(sum, 1./p)*v.getHX();
}

