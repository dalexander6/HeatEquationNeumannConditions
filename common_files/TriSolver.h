#ifndef _TriSolver_
#define _TriSolver_
#include <iostream>
#include <vector>
#include "GridFun1D.h"
//#include "vectorDebug.h"
using namespace std;

class TriSolver{
	public: 
		TriSolver();
		TriSolver(const TriSolver&);
		TriSolver(vector<double>&, vector<double>&, vector<double>&);
		void apply(vector<double>&, GridFun1D&);
		void apply(vector<double>&, vector<double>&);
//		template<class T> void apply(vector<double>&, T);
		
	private:
		int systemSize;
		vector<double> lowerDiagonal;	
		vector<double> diagonal;
		vector<double> upperDiagonal;
};

/** Solves for u = A^{-1} f via a Trisolver alg
 * f and u go from 0 to systemSize-1
 * f is destroyed in the process
 */
/*
template<class T>
void TriSolver::apply(vector<double> & f, T u){
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
*/
#endif
