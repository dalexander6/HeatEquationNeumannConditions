#ifndef _CrankNicolsonOp1D_
#define _CrankNicolsonOp1D_
#include "TriSolver.h"
//#include "vectorDebug.h"
#include "GridFun1D.h"
class CrankNicolsonOp1D{
	public:
		CrankNicolsonOp1D();
		CrankNicolsonOp1D(double, double, const GridFun1D&);

		void initialize(double, double, const GridFun1D&);
		
		void apply(const GridFun1D&, GridFun1D&);
		
		TriSolver tSolver;
		double dt;
		double alpha;
		long numPanels;
		GridFun1D f;
};
#endif
