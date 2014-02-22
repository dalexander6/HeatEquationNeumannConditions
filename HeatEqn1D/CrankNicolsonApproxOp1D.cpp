#include "CrankNicolsonApproxOp1D.h"

CrankNicolsonApproxOp1D::CrankNicolsonApproxOp1D(double dt, double alpha, const GridParameters& grid, const GridFun1D& V){
	this->alpha = alpha;
	this->dt = dt;
	myGrid = grid.Clone();
	int numPanels = myGrid->getXPanels();
	double hx = myGrid->getHX();
	
	//we set up the trisolver system
	//for Crank-Nicolson we need to solve [I-alpha dt/2 D_+ D_-]u^{n+1} = STUFF
	vector<double> diagonal(numPanels+1, 1+dt*alpha/(hx*hx));
	vector<double> lowerDiagonal(numPanels, -dt*alpha/(2*hx*hx)); //wrong at last entry 
	vector<double> upperDiagonal(numPanels, -dt*alpha/(2*hx*hx)); //wrong at first entry

	//add in the u_x V term
	for(int i = 0; i < numPanels; i++){
		lowerDiagonal[i] += -(dt/(4*hx))*V[i+1];
		upperDiagonal[i] += (dt/(4*hx))*V[i];
	}
	
	//add in the u V_x term
	//note that since we're assuming V is constant at the edges we don't have 
	//to worry about those and the indexing errors they could cause
	for(int i = 1; i < numPanels; i++){
		diagonal[i] += (dt/(4*hx))*(V[i+1]-V[i-1]);
	}
	/*
	//prev assumption broken.  Use left/right estimates at boundaries.
	//first order estimate is perfectly accurate as V is linear
	diagonal[0] += (dt/(2*hx))*(V[1]-V[0]);
	diagonal[numPanels] += (dt/(2*hx))*(V[numPanels]-V[numPanels-1]);
	*/
	
	//fix wrong entries
	//we are assuming Dirichlet BCs
	diagonal[0] = -1;
	diagonal[numPanels] = -1;
	lowerDiagonal[numPanels-1] = 0; //no entry here for Dirichlet BCs
	upperDiagonal[0] = 0; //no entry here for Dirichlet BCs
	assert(symmetryCheck(diagonal));
	
	tSolver = TriSolver(lowerDiagonal, diagonal, upperDiagonal);
	return;
}

/** This applies to the modified heat equation meant to approximate Neumann BCS 
 * note that while V is passed in if it's a different V than used in the constructor things won't work
 * */
void CrankNicolsonApproxOp1D::apply(const GridFun1D& uIn, GridFun1D& uOut, const GridFun1D& V){
	int numPanels = myGrid->getXPanels();
	if((uIn.getXPanels() != numPanels) || (uIn.getXPanels() != uOut.getXPanels())){ cout<<"Indexing problem in applying CrankNicolsonApproxOp1D"; }

	double hx = myGrid->getHX();
	//assert(symmetryCheck(uIn));
	//we are solving Au^{n+1} = Bu^n =: g
	//need to compute g := u^n + alpha (dt/2) (D_+) (D_i) u^n + (dt/2) D(u_n V) 
	//then apply trisolver to find u^{n+1}

	vector<double> g(numPanels+1,0);
	//we fix the BCs (here the 0th and nth elements correspond to boundary nodes)
	//we are assuming Dirichlet BCs
	g[0] = uIn[0];
	g[numPanels] = uIn[numPanels];

	//compute the inside
	for(long i = 1; i < numPanels; i++){
		g[i] = uIn[i];
		//add in alpha(dt/2) D+D- u_n 
		g[i] += (alpha*dt/(2*hx*hx))*(uIn[i-1]-2*uIn[i]+uIn[i+1]);
		//add in the u_x V term
		g[i] +=  - (dt/(4*hx))*(uIn[i+1] - uIn[i-1])*V[i];
		//add in u V_x term
		g[i] += -(dt/(4*hx))*uIn[i]*(V[i+1] - V[i-1]);
	}

	//assert(symmetryCheck(g));
	
	//trisolver time
	tSolver.apply(g, uOut);

	//assert(symmetryCheck(uOut, 1e-5));
	return;
}
