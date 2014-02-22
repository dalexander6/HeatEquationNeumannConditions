#ifndef _CrankNicolsonApproxOp1D_
#define _CrankNicolsonApproxOp1D_
#include "TriSolver.h"
#include "toolboxFunctions.h"
#include <assert.h>
#include "GridFun1D.h"
class CrankNicolsonApproxOp1D{
	public:
		CrankNicolsonApproxOp1D();
		
		CrankNicolsonApproxOp1D(double, double, const GridParameters&, const GridFun1D&);
		~CrankNicolsonApproxOp1D(){ delete myGrid; }

		void apply(const GridFun1D&, GridFun1D&, const GridFun1D&);
		
		TriSolver tSolver;
		double dt;
		double alpha;
		GridParameters* myGrid;
};
#endif
