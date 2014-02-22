#ifndef _CrankNicolsonApproxOp2D_
#define _CrankNicolsonApproxOp2D_
#include <vector>
#include "TriSolver.h"
#include <assert.h>
#include "GridFun2D.h"
class CrankNicolsonApproxOp2D{
	public:
		CrankNicolsonApproxOp2D(){
		}
		
		CrankNicolsonApproxOp2D(double, double, const GridFun2D&, const GridFun2D&);

		~CrankNicolsonApproxOp2D(){
		}

		void apply(const GridFun2D&, GridFun2D&, const GridFun2D&, const GridFun2D&);
		
		vector<TriSolver> tSolverX;
		vector<TriSolver> tSolverY;
		double dt;
		double alpha;

};
#endif
