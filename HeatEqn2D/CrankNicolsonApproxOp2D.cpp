#include "CrankNicolsonApproxOp2D.h"

CrankNicolsonApproxOp2D::CrankNicolsonApproxOp2D(double dt, double alpha, const GridFun2D& Vx, const GridFun2D& Vy){
	
	this->alpha = alpha;
	this->dt = dt;
	int xPanel = Vx.getXPanels();
	int yPanel = Vx.getYPanels();
	double hx = Vx.getHX();
	double hy = Vx.getHY();
	
	tSolverX.resize(yPanel-1);
	tSolverY.resize(xPanel-1);
	//we set up the trisolver system
	//for Crank-Nicolson we need to solve [I-alpha dt/2 D_+ D_-]u^{n+1} = STUFF
	//We will do this via ADI
	
	//Note that we need a different tsolver at each x and y slice
	//in the interior
	//due to the variance in V
	
	for(int j = 1; j < yPanel; j++){
		//we set up the trisolver system
		//Douglas method:
		//(I - A_x / 2) u_* = (I + A_x / 2 + A_y) u_k
		//(I - A_y / 2) u_{k+1} = U_* - A_y /2 u_k
		//for ADI we need to solve [I-dt/2 \alpha_x D_x+ D_x-]u_{n+1}^* = STUFF
		//and then [I-dt/2 \alpha_y D_y+ D_y-]u_{n+1} = STUFF

		vector<double> diagonalX(xPanel+1, 1+dt*alpha/(hx*hx)); //wrong at first and last entry
		vector<double> lowerDiagonalX(xPanel, -dt*alpha/(2*hx*hx)); //wrong at last entry -- should be 0
		vector<double> upperDiagonalX(xPanel, -dt*alpha/(2*hx*hx)); //wrong at first entry
		
		//add in the u_x Vx/2 term (not V_x: Vx is the x component of velocity)
		for(int i = 0; i < xPanel; i++){
			lowerDiagonalX[i] += -(dt/(4*hx))*Vx(i+1,j);
			upperDiagonalX[i] += (dt/(4*hx))*Vx(i,j);
		}
		
		//add in the u Vx_x/2 term
		for(int i = 1; i < xPanel; i++){
			diagonalX[i] += (dt/(4*hx))*(Vx(i+1,j)-Vx(i-1,j));
		}
		//fix wrong entries that correspond to including BCs and indexing and such
		diagonalX[0] = -1;	//our trisolver has boundary nodes included, and we use the eqn -u_0 = - u_0
		diagonalX[xPanel] = -1;	//we pick -1 to make the trisolver matrix neg. def.
		lowerDiagonalX[xPanel-1] = 0; //bottom row is just boundary data
		upperDiagonalX[0] = 0; //top row is just boundary data
		tSolverX[j-1] = TriSolver(lowerDiagonalX, diagonalX, upperDiagonalX);
	}

	//now set up Y trisolvers
	for(int i = 1; i < xPanel; i++){
		vector<double> diagonalY(yPanel+1, 1+dt*alpha/(hy*hy)); //wrong at first and last entry
		vector<double> lowerDiagonalY(yPanel, -dt*alpha/(2*hy*hy)); //wrong at last entry -- should be 0
		vector<double> upperDiagonalY(yPanel, -dt*alpha/(2*hy*hy)); //wrong at first entry

		//add in the u_y Vy/2 term
		for(int j = 0; j < yPanel; j++){
			lowerDiagonalY[j] += -(dt/(4*hy))*Vy(i,j+1);
			upperDiagonalY[j] += (dt/(4*hy))*Vy(i,j);
		}
		
		//add in the u Vy_y/2 term
		for(int j = 1; j < yPanel; j++){
			diagonalY[j] += (dt/(4*hy))*(Vy(i,j+1)-Vy(i,j-1));
		}
		
		diagonalY[0] = -1;
		diagonalY[yPanel] = -1;
		lowerDiagonalY[yPanel-1] = 0;
		upperDiagonalY[0] = 0;
		
		tSolverY[i-1] = TriSolver(lowerDiagonalY, diagonalY, upperDiagonalY);
	}
	return;
	
}

/** This applies to the modified heat equation meant to approximate Neumann BCS 
 * We use the Douglas ADI method from 270A hw 4
 * note that while V is passed in if it's a different V than used in the constructor things won't work
 * */
void CrankNicolsonApproxOp2D::apply(const GridFun2D& uIn, GridFun2D& uOut, const GridFun2D& Vx, const GridFun2D& Vy){

	int xPanel = Vx.getXPanels();
	int yPanel = Vx.getYPanels();
	double hx = Vx.getHX();
	double hy = Vx.getHY();
	//need to compute g := u^n + alpha (dt/2) D_x+ D_x- u^n - (dt/2) D_0x u Vx - (dt/2) u D_0x Vx - dt D_0y u Vy - dt u D_0y Vy 
	//then apply X trisolver
	
	//we make uTemp have the right BCs at top and bottom
	GridFun2D uTemp(uIn);
	uOut = uIn;

	long i = 0;
	long j = 0;	
	//loop over values of y, and trisolve in x direction
	// 		o o o o
	// 		o . . o	
	// 	-->	o . . o
	// 		o o o o
	//we don't need to do the y = 0 or y = yMax, since we have prescribed BCs there
	//fix y at level j
	for(j = 1; j < yPanel; j++){
		vector<double> g(xPanel+1, 0);
		vector<double> output(xPanel+1, 0);
		
		//we fix the BCs (here the 0th and nth elements correspond to boundary nodes)
		// o . . . . . o
		// o boundary, . interior
		g[0] = -uIn(0,j);
		g[xPanel] = -uIn(xPanel,j);
		//compute the inside
		//which is g = [I + k/2h^2 D+D- - 1/4h D_0 V - 1/4h V D_0] uIn
		for(i = 1; i < xPanel; i++){
			g[i] = uIn(i,j);
			g[i] += (alpha*dt/(2*hx*hx))*(uIn(i-1,j)-2*uIn(i,j)+uIn(i+1,j));
			g[i] += (alpha*dt/(hy*hy))*(uIn(i,j-1)-2*uIn(i,j)+uIn(i,j+1));
			//add in the -u_x Vx/2 term
			g[i] +=  - (dt/(4*hx))*(uIn(i+1,j) - uIn(i-1,j))*Vx(i,j);
			//add in -u Vx_x/2 term
			g[i] += -(dt/(4*hx))*uIn(i,j)*(Vx(i+1,j) - Vx(i-1,j));

			//add in -u_y Vy term, bigger by factor of 2 in Douglas method
			g[i] +=  - (dt/(2*hy))*(uIn(i,j+1) - uIn(i,j-1))*Vy(i,j);
			//add in -u Vy_y term, also not implicit
			g[i] += -(dt/(2*hy))*uIn(i,j)*(Vy(i,j+1) - Vy(i,j-1));
		}
		//tsolver indexing is off by 1
		tSolverX[j-1].apply(g, output);
		for(i = 0; i <= xPanel; i++){
			uTemp(i,j) = output[i];
		}
	}
	//now we aim to apply Y trisolver
	//To solve (I-A_y) u_{k+1} = u_* - A_y/2 u_k

	for(i = 1; i < xPanel; i++){
		vector<double> g(yPanel+1, 0);
		vector<double> output(yPanel+1, 0);
		
		//we fix the BCs (here the 0th and nth elements correspond to boundary nodes)
		g[0] = -uIn(i,0);
		g[yPanel] = -uIn(i,yPanel);
		//compute the inside
		for(j = 1; j < yPanel; j++){
			g[j] = uTemp(i,j);
			//u_yy /2 term
			g[j] -= ((alpha*dt)/(2*hy*hy))*(uIn(i,j-1)-2*uIn(i,j)+uIn(i,j+1));

			//add in u_y Vy/2 term 
			g[j] +=   (dt/(4*hy))*(uIn(i,j+1) - uIn(i,j-1))*Vy(i,j);
			//add in u Vy_y/2 term
			g[j] += (dt/(4*hy))*uIn(i,j)*(Vy(i,j+1) - Vy(i,j-1));
		}
		//tsolver indexing off by one
		tSolverY[i-1].apply(g, output);
		for(j = 0; j <= yPanel; j++){
			uOut(i,j) = output[j];
		}
	}
	
	return;
}
