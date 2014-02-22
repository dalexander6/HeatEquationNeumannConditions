#include "TriSolver.h"

TriSolver::TriSolver(){
}


TriSolver::TriSolver(const TriSolver& inputSolver){
	lowerDiagonal = inputSolver.lowerDiagonal;
	diagonal = inputSolver.diagonal;
	upperDiagonal = inputSolver.upperDiagonal;
	systemSize = inputSolver.systemSize;
	
	return;
}

TriSolver::TriSolver(vector<double>& loDiag, vector<double>& diag, vector<double>& upDiag){
	//diag goes from 0 to systemsize-1
	//lower and upper diag go from 0 to systemsize-2
	lowerDiagonal = loDiag;
	diagonal = diag;
	upperDiagonal = upDiag;
	systemSize = diag.size();

	//COMMENTING OUT: THIS IS NOT THE WIKIPEDIA METHOD	
	//we do the LU factorization and overwrite diagonal entries to save memory
	//e_0 = a_0 automatically satisfied -- diagonal[0] = diagonal[0];
	
	for(int i = 1; i <= systemSize-1; i++)
	{
		lowerDiagonal[i-1] = lowerDiagonal[i-1]/diagonal[i-1];
		diagonal[i] = diagonal[i] - lowerDiagonal[i-1]*upperDiagonal[i-1];
	}
	
	//wikipedia thomas algorithm
	//c_i' step.  overwrite upDiag.
	/*
	upperDiagonal[0] = upperDiagonal[0]/ diagonal[0];

	for(int i = 1; i < systemSize-1; i++){
		upperDiagonal[i] = upperDiagonal[i]/(diagonal[i] - upperDiagonal[i-1]*lowerDiagonal[i-1]);
	}
	*/

	return;
}

/** Solves for u = A^{-1} f via a Trisolver alg
 * f and u go from 0 to systemSize-1
 * f is destroyed in the process
 */
void TriSolver::apply(vector<double>& f, GridFun1D& u){
	//Wikipedia method
	//the d_i' step
	//overwrites f
	/*
	f[0] = f[0]/ diagonal[0];
	for(int i = 1; i < systemSize; i++){
		f[i] = (f[i] - f[i-1]*lowerDiagonal[i-1])/(diagonal[i] - upperDiagonal[i-1]*lowerDiagonal[i-1]);
	}

	u[systemSize-1] = f[systemSize-1];
	for(int i = systemSize-2; i > 0; i--){
		u[i] = f[i] - upperDiagonal[i] * u[i+1];
	}
	*/

	

	//COMMENTING OUT: NOT WIKIPEDIA METHOD
	 //CHRIS ANDERSON METHOD
	u[0] = f[0];
	for(int i = 1; i <= systemSize-1; i++)
	{
		u[i] = f[i] - lowerDiagonal[i-1]*u[i-1];
	}
	
	u[systemSize-1] = u[systemSize-1]/diagonal[systemSize-1];
	
	for(int i = systemSize-2; i >= 0; i--)
	{
		u[i] = (u[i] - upperDiagonal[i]*u[i+1])/diagonal[i];
	}
	return;
}
	

/** Solves for u = A^{-1} f via a Trisolver alg
 * f and u go from 0 to systemSize-1
 * f is destroyed in the process
 */
void TriSolver::apply(vector<double>& f, vector<double>& u){
	/*
	//Wikipedia method
	//the d_i' step
	//overwrites f
	f[0] = f[0]/ diagonal[0];
	for(int i = 1; i < systemSize; i++){
		f[i] = (f[i] - f[i-1]*lowerDiagonal[i-1])/(diagonal[i] - upperDiagonal[i-1]*lowerDiagonal[i-1]);
	}

	u[systemSize-1] = f[systemSize-1];
	for(int i = systemSize-2; i > 0; i--){
		u[i] = f[i] - upperDiagonal[i] * u[i+1];
	}

	*/
	

	//COMMENTING OUT: NOT WIKIPEDIA METHOD
	 //CHRIS ANDERSON METHOD
	u[0] = f[0];
	for(int i = 1; i <= systemSize-1; i++)
	{
		u[i] = f[i] - lowerDiagonal[i-1]*u[i-1];
	}
	
	u[systemSize-1] = u[systemSize-1]/diagonal[systemSize-1];
	
	for(int i = systemSize-2; i >= 0; i--)
	{
		u[i] = (u[i] - upperDiagonal[i]*u[i+1])/diagonal[i];
	}
	return;
}
	
