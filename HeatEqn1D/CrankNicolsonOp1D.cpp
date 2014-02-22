#include "CrankNicolsonOp1D.h"

CrankNicolsonOp1D::CrankNicolsonOp1D(){
}

CrankNicolsonOp1D::CrankNicolsonOp1D(double dt, double alpha, const GridFun1D& f){
	initialize(dt, alpha, f);
}

void CrankNicolsonOp1D::initialize(double dt, double alpha, const GridFun1D& f){
	this->dt = dt;
	this->alpha = alpha;
	this->f = f;
	numPanels = f.getXPanels();
	double hx = f.getHX();
	//we set up the trisolver system
	//for Crank-Nicolson we need to solve [I-alpha dt/2 D_+ D_-]u^{n+1} = STUFF
	vector<double> diagonal(numPanels+1, 1+dt*alpha/(hx*hx));
	vector<double> lowerDiagonal(numPanels, -dt*alpha/(2*hx*hx)); //wrong at last entry 
	vector<double> upperDiagonal(numPanels, -dt*alpha/(2*hx*hx)); //wrong at first entry

	//fix wrong entries
	//we are assuming no-flow Neumann BCs 
	lowerDiagonal[numPanels-1] = -alpha*dt/(hx*hx);
	upperDiagonal[0] = -alpha*dt/(hx*hx);
	
	tSolver = TriSolver(lowerDiagonal, diagonal, upperDiagonal);
	return;
}

void CrankNicolsonOp1D::apply(const GridFun1D& uIn, GridFun1D& uOut){
	double hx = f.getHX();
	//need to compute g := u^n + alpha (dt/2) (D_+) (D_i) u^n + dt f
	//then apply trisolver
	if((uIn.getXPanels() != numPanels) || (uIn.getXPanels() != uOut.getXPanels())){ cout<<"Indexing problem in applying GridFun1D"; }

	vector<double> g(numPanels+1, 0);
	GridFun1D output(uIn);
	//we fix the BCs (here the 0th and nth elements correspond to boundary nodes)
	//we are assuming no-flow Neumann BCs 
	g[0] = uIn[0] + alpha*dt/(hx*hx)*(uIn[1] - uIn[0]);
	g[numPanels] = uIn[numPanels] + alpha*dt/(hx*hx)*(uIn[numPanels-1] - uIn[numPanels]);
	//compute the inside
	for(long i = 1; i < numPanels; i++){
		g[i] = uIn[i] + (alpha*dt/(2*hx*hx))*(uIn[i-1]-2*uIn[i]+uIn[i+1]) - dt * f[i];
	}
	tSolver.apply(g, output);
	for(long i = 0; i <= numPanels; i++){
		uOut[i] = output[i];
	}
	return;
}

