//
//#####################################################################
//                       RunParameters.h 
//
//                      RunParameters Class  
// Math 270E                                          Version 1/14/2013
//#####################################################################
//
//
#ifndef __RunParameters__
#define __RunParameters__

class RunParameters
{
public :

	char     scheme;     // Difference scheme identifier
	double       dt;     // Time step size
	int     rkOrder;     // Order of Runge-Kutta method (1-4)
	char outputType;     // 'g' = gnuplot 'm' = matlab
	double		nu;		//diffusion coefficient
	bool includeDiffusion; //True means we add nu*Delta S
	bool outputData; //True means we output .dat files
	long numOutputs; //How many times we output .dat files
	double tFinal;
};


#endif
