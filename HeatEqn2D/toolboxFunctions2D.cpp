#include "toolboxFunctions2D.h"

/** Initializes the penalty term
 * @param N is the height
 * @param omega is the region
 */
void initializePhi(GridFun2D& Phi, double N, Region& omega){
	double x = 0;
	double hx = Phi.getHX();
	double xMin = Phi.getXMin();
	
	double y = 0;
	double hy = Phi.getHY();
	double yMin = Phi.getYMin();

	double v [2];
	Phi.setToValue(0.0);
	for(int i = 0; i <= Phi.getXPanels(); i++){
		x = xMin + i*hx;
		v[0] = x;
		for(int j = 0; j <= Phi.getYPanels(); j++){
			y = yMin + j*hy;
			v[1] = y;

			Phi(i,j) = N*pow(omega.distance(v),3);
		}
	}
	
	return;
}

/** Initializes the penalty term
 * @param N is the height
 * THIS ONLY WORKS FOR POLAR AND HENCE OMEGA IS ASSUMED TO BE CIRCLE RADIUS 1
 * This penalty term looks like
 * d^3 + alpha * d^exponent * cos^2(theta)
 * Note that cos^2(theta) = x^2 / r^2
 */
void initializePhiPrime(GridFun2D& Phi, double N, double exponent, double alpha){
	double x = 0;
	double hx = Phi.getHX();
	double xMin = Phi.getXMin();
	
	double y = 0;
	double hy = Phi.getHY();
	double yMin = Phi.getYMin();
	double r = 0;

	//try number 2: growing at "infinity"
	Phi.setToValue(0.0);
	for(int i = 0; i <= Phi.getXPanels(); i++){
		x = xMin + i*hx;
		for(int j = 0; j <= Phi.getYPanels(); j++){
			y = yMin + j*hy;
			r = sqrt(x*x+y*y);
			if(r <= 1){
				Phi(i,j) = 0;
			}
			else{
				Phi(i,j) = N*(pow(r-1,3) - alpha * pow(r-1,exponent-2) * x * x);
			}
		}
	}
	
	return;

}
/** Returns a vector containing the prescribed initial data on the grid
	We are making the initial data be (.5 - x*x)_+
	@param myGridFun is number of panels
	*/
void initializeData(GridFun2D& u){
	
	double x = 0;
	double y = 0;
	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			u(i,j) = (pow(.5,2) - pow(x-.5,2) - pow(y-.5,2) > 0 ? pow(.5,2) - pow(x-.5,2) - pow(y-.5,2): 0);
		}
	}
	return;
}

void initializeData2(GridFun2D& u){
	
	double x = 0;
	double y = 0;
	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			if( 0 <= x && x <= 1 && 0 <= y && y <= 1){
				u(i,j) = exp(y)*sin(x);
			}
		}
	}
	return;
}

void initializeData(GridFun2D& u, const Region& omega){
	double x = 0;
	double y = 0;
	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			double v[2];
			v[0] = x;
			v[1] = y;
			if(omega.distance(v) < 1e-9){
				u(i,j) = exp(y)*sin(x);
			}
		}
	}
	return;
}

/**Guessing this gets analytic solution on box or something provided
 * initial data is a product of trig functions
 */
void initializeAnalyticSoln(GridFun2D& u, int m, int n){
	double x = 0;
	double y = 0;
	
	u.setToValue(0.0);

	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			
			if( 0 <= x && x <= 1 && 0 <= y && y <= 1){
			//if(omega.distance(Point2D(x,y)) < 1e-9){
				u(i,j) = cos(2*PI*m*x) * cos(2*PI*n*y) + 1;
			}
		}
	}
	return;

}

/** This creates and returns by reference the eigenfunction solution that works on a box [0,1]x[0,1] at time t with wave numbers m and n
 */
void getAnalyticSoln(GridFun2D& u, int m, int n, double t){
	double x = 0;
	double y = 0;

	u.setToValue(0.0);

	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			if( 0 <= x && x <= 1 && 0 <= y && y <= 1){
				u(i,j) = exp((-4*PI*PI * t)*(m*m + n*n)) * cos(2*PI*m*x) * cos(2*PI*n*y) + 1;
			}
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
 * p defaults to 1
 */
double LpIntegral(const GridFun2D& v, const Region& omega, double p){
	
	double sum = 0;
	double x = 0;
	double y = 0;
	double vec[2];
	for(int i = 0; i < v.getXPanels(); i++){
		x = v.getXMin() + i*v.getHX();
		vec[0] = x;
		for(int j = 0; j < v.getYPanels(); j++){
			y = v.getYMin() + j*v.getHY();
			vec[1] = y;
			//only integrate in Omega
			if(omega.distance(vec) < 1e-9){
				sum += pow(fabs(v(i,j)) , p);
			}
		}
	}
	return pow(sum, 1./p)*v.getHX()*v.getHY();
}

/** Returns the Lp integral of the input
 * @param p specifies the L^p norm
 * p defaults to 1
 */
double LpIntegral(const GridFun2D& v, double p){
	
	double sum = 0;
	for(int i = 0; i < v.getXPanels(); i++){
		for(int j = 0; j < v.getYPanels(); j++){
			sum += pow(fabs(v(i,j)) , p);
		}
	}
	return pow(sum, 1./p)*v.getHX()*v.getHY();
}

void getGradient(const GridFun2D& Phi, GridFun2D& Vx, GridFun2D& Vy){
	int i;
	int j;

	//on interior, use second order difference
	for( i = 1; i < Phi.getXPanels(); i++){
		for(j = 1; j < Phi.getYPanels(); j++){
			Vx(i,j) = (Phi(i+1,j) - Phi(i-1,j))/(2.*Phi.getHX());
			Vy(i,j) = (Phi(i,j+1) - Phi(i,j-1))/(2.*Phi.getHY());
		}
	}

	//bottom edge
	j = 0;
	for(i = 1; i < Phi.getXPanels(); i++){
		Vx(i,j) = (Phi(i+1,j) - Phi(i-1,j))/(2.*Phi.getHX());
		Vy(i,j) = (Phi(i,j+1) - Phi(i,j))/(Phi.getHY());
	}

	//bottom left corner
	i = 0;
	Vx(i,j) = (Phi(i+1,j) - Phi(i,j))/(Phi.getHX());
	Vy(i,j) = (Phi(i,j+1) - Phi(i,j))/(Phi.getHY());
	//bottom right corner
	i = Phi.getXPanels();
	Vx(i,j) = (Phi(i,j) - Phi(i-1,j))/(Phi.getHX());
	Vy(i,j) = (Phi(i,j+1) - Phi(i,j))/(Phi.getHY());



	//top edge
	j = Phi.getYPanels();
	for(i = 1; i < Phi.getXPanels(); i++){
		Vx(i,j) = (Phi(i+1,j) - Phi(i-1,j))/(2.*Phi.getHX());
		Vy(i,j) = (Phi(i,j) - Phi(i,j-1))/(Phi.getHY());
	}

	//top left corner
	i = 0;
	Vx(i,j) = (Phi(i+1,j) - Phi(i,j))/(Phi.getHX());
	Vy(i,j) = (Phi(i,j) - Phi(i,j-1))/(Phi.getHY());
	//top right corner
	i = Phi.getXPanels();
	Vx(i,j) = (Phi(i,j) - Phi(i-1,j))/(Phi.getHX());
	Vy(i,j) = (Phi(i,j) - Phi(i,j-1))/(Phi.getHY());


	//right edge
	i = Phi.getXPanels();
	for(j = 1; j < Phi.getYPanels(); j++){
		Vx(i,j) = (Phi(i,j) - Phi(i-1,j))/(Phi.getHX());
		Vy(i,j) = (Phi(i,j+1) - Phi(i,j+1))/(2.*Phi.getHY());
	}

	//left edge
	i = 0;
	for(j = 1; j < Phi.getYPanels(); j++){
		Vx(i,j) = (Phi(i+1,j) - Phi(i,j))/(Phi.getHX());
		Vy(i,j) = (Phi(i,j+1) - Phi(i,j-1))/(2.*Phi.getHY());
	}

	return;
}

/**gets Bessel data cos(3theta) J_3(lambda_3 r)e^{-lambda_3^2 t}
 */
double getTestBesselSoln(double x, double y, double t){
	if(x == 0 && y == 0){
		return 0;
	}
	double r = sqrt(x*x + y*y);
	double theta = atan2(y,x);
	//double lambda0 = 3.83170597020751;
	double lambda3 = 4.20118894121052;

	//J_0 is discontinuous at the origin!
	//return cos(theta)*j0(lambda0*r)*exp(-lambda0*lambda0*t);
	return cos(3*theta)*jn(3,lambda3*r)*exp(-lambda3*lambda3*t);
}

/** Returns a vector containing the prescribed initial data on the grid
	We are making the initial data be Bessel eigenfunction thing
	@param myGridFun is number of panels
	*/
void initializeBesselData(GridFun2D& u){
	double x = 0;
	double y = 0;
	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			if( x*x + y*y > 1)
				u(i,j) = 0;
			else{
				u(i,j) = getTestBesselSoln(x,y,0); 
				//cout << "(" << x << ", " << y << ") u = " << u(i,j) << endl;
			}
		}
	}
	return;
}

/** Returns a vector containing the prescribed data on the grid
	We are making the data be Bessel eigenfunction thing
	@param myGridFun is number of panels
	*/
void initializeBesselData(GridFun2D& u, double t){
	double x = 0;
	double y = 0;
	for(int i = 0; i <= u.getXPanels(); i++){
		x = u.getXMin() + i*u.getHX();
		for(int j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY();
			if( x*x + y*y > 1)
				u(i,j) = 0;
			else{
				u(i,j) = getTestBesselSoln(x,y,t); 
			}
		}
	}
	return;
}

