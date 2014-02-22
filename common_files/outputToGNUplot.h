//
//######################################################################
//
// outputToGNUplot.h : a routine that constructs of a gnuplot readable 
// data file that contains the the values of a scalar function of two 
// variables sampled on a cartesian product mesh, e.g. at the
// points (X(i),Y(j)) for i = 0 ... mPanels and j = 0 .. nPanels;
//                
// 
// Math 269B                                                 02/23/2010
//######################################################################
//
//
#ifndef __outputToGNUplot__
#define __outputToGNUplot__

#include "Vector1D.h"
#include "GridFun1D.h"
#include <math.h>
#include <stdio.h>
#include "GridFun1D.h"
#include <iostream>
#include <sstream>
using namespace std;

void outputToGNUplot(Vector1D& u, double xMin, double xMax, const char* fileName, long stepCount)
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

/** formats a filename
	pads it with up to 000 to make stuff in right order
	@param folder holds the folder name (if any)
	@param filePrefix holds the prefix to output
	@return a stringstream holding "folder/stepCountfileSuffix.dat"
	*/
void getFilename(const char* folder, const char* filePrefix, stringstream& filename, int stepCount){

    // Create file name of form SXXX.dat for step XXX
    filename.str("");

	filename << folder;
	filename << "/";
	
    // Code if one wants step designation in output file name prefixed with
    // 0's so that the file names are always the same length.
    if(stepCount < 10)       filename << filePrefix << 0 << 0 << 0 << stepCount << ".dat";
    else if(stepCount < 100) filename << filePrefix << 0  << 0    << stepCount << ".dat";
    else if(stepCount < 1000) filename << filePrefix << 0     << stepCount << ".dat";
    else                     filename << filePrefix << stepCount << ".dat";

	return;
}

void outputToGNUplot(GridFun1D& u, const char* folder, const char* filePrefix, int stepCount){

	stringstream outs;

	getFilename(folder, filePrefix, outs, stepCount);
    FILE* dataFile;

	const char* fileName = (outs.str()).c_str();
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
		fprintf(dataFile,"%-10.5e %-10.5e\n",u.getXMin() + i*u.getHX(),u[i]);
    }
    fprintf(dataFile,"\n");

    
    fclose(dataFile);
} 

/** writes to a file of the form folder/filePrefix + stepCount.dat
 */
void outputToGNUplot(GridFun1D& u, const GridParameters& gridParams, const char* folder, const char* filePrefix, int stepCount){

//  Open and then write to a file
//
	stringstream outs;

	getFilename(folder, filePrefix, outs, stepCount);
    FILE* dataFile;

	const char* fileName = (outs.str()).c_str();
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

#endif
