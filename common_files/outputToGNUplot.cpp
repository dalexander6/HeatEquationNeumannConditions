//
//######################################################################
//
// outputToGNUplot.cpp : a routine that constructs of a gnuplot readable 
// data file that contains the the values of a scalar function of two 
// variables sampled on a cartesian product mesh, e.g. at the
// points (X(i),Y(j)) for i = 0 ... mPanels and j = 0 .. nPanels;
//                
// 
// Math 269B                                                 02/23/2010
//######################################################################
//
//

#include "Vector1D.h"
#include "GridFun1D.h"
#include <math.h>
#include <stdio.h>
#include "GridFun1D.h"
#include <iostream>
using namespace std;

void outputToGNUplot(Vector1D& u, double xMin, double xMax, const char* fileName)
{

//  Open and then write to a file
//
    FILE* dataFile;

    if( (dataFile = fopen(fileName, "w+" )) == NULL )
    {
      printf( "The file %s could not be  opened\n",fileName);
      return;
    }
 
	long xPanel = u.getSize()-1;
	double hx   = (xMax-xMin)/(double)(xPanel);

//
//  Output the data.
// 
    for(long i = 0;  i <= xPanel;  i++)
    {
		fprintf(dataFile,"%-10.5e %-10.5e\n",xMin + i*hx,u(i));
    }
    fprintf(dataFile,"\n");

    
    fclose(dataFile);
} 

void outputToGNUplot(GridFun1D& u, const GridParameters& gridParams, const char* fileName){

//  Open and then write to a file
//
    FILE* dataFile;

    if( (dataFile = fopen(fileName, "w+" )) == NULL )
    {
      printf( "The file %s could not be  opened\n",fileName);
      return;
    }
 
//
//  Output the data.
// 
    for(long i = 0;  i < gridParams.getXPanels();  i++)
    {
		fprintf(dataFile,"%-10.5e %-10.5e\n",gridParams.getXMin() + i*gridParams.getHX(),u[i]);
    }
    fprintf(dataFile,"\n");

    
    fclose(dataFile);
} 



void outputToGNUplot(GridFun1D& u, double xMin, double xMax, const char* fileName)
{

//  Open and then write to a file
//
    FILE* dataFile;

    if( (dataFile = fopen(fileName, "w+" )) == NULL )
    {
      printf( "The file %s could not be  opened\n",fileName);
      return;
    }
 
//
//  Output the data.
// 
    for(long i = 0;  i < u.getXPanels();  i++)
    {
		fprintf(dataFile,"%-10.5e %-10.5e\n",xMin + i*u.getHX(),u[i]);
    }
    fprintf(dataFile,"\n");

    
    fclose(dataFile);
}
