//
//######################################################################
//
// GridOutput.h: a routine that constructs of a gnuplot readable 
// data file that contains the the values of a scalar function of two 
// variables sampled on a cartesian product mesh, e.g. at the
// points (X(i),Y(j)) for i = 0 ... mPanels and j = 0 .. nPanels;
//                
// 
// Math 269B                                                 02/23/2010
//######################################################################
//
//
#ifndef __GridOutput__
#define __GridOutput__

#include "GridFun1D.h"
#include "GridFun2D.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/** formats a filename
	pads it with up to 000 to make stuff in right order
	@param folder holds the folder name (if any)
	@param filePrefix holds the prefix to output
	@return a stringstream holding "folder/stepCountfileSuffix.dat"
	*/
string getFilename(const char* folder, const char* filePrefix, int stepCount){
	stringstream filename("");
    // Create file name of form SXXX.dat for step XXX

	filename << folder;
	filename << "/";
	
    // Code if one wants step designation in output file name prefixed with
    // 0's so that the file names are always the same length.
    if(stepCount < 10)       filename << filePrefix << 0 << 0 << 0 << 0 << stepCount << ".dat";
    else if(stepCount < 100) filename << filePrefix << 0 << 0 << 0    << stepCount << ".dat";
    else if(stepCount < 1000) filename << filePrefix << 0 << 0    << stepCount << ".dat";
	else if(stepCount < 10000) filename << filePrefix << 0 << stepCount << ".dat";
    else                     filename << filePrefix << stepCount << ".dat";

	return filename.str();	
}

void outputGridfunction(GridFun1D& u, const GridParameters& gridParams, const char* folder, const char* filePrefix, int stepCount){

	//create filename with intelligent numbering prefixes
	string filename = getFilename(folder, filePrefix, stepCount);
	
	//open file
    FILE* dataFile;

	const char* fileName = filename.c_str();
    if( (dataFile = fopen(fileName, "w+" )) == NULL ){
      printf( "The file %s could not be  opened\n",fileName);
      return;
    }
 
	//Output the data.
    for(long i = 0;  i < gridParams.getXPanels();  i++){
		fprintf(dataFile,"%-10.5e %-10.5e\n",gridParams.getXMin() + i*gridParams.getHX(),u[i]);
    }
    fprintf(dataFile,"\n");

    fclose(dataFile);


}

void outputGridfunction(const GridFun2D& u,const char* folder, const char* filePrefix, int stepCount){

	//create filename with intelligent numbering prefixes
	string filename = getFilename(folder, filePrefix, stepCount);
	
	//open file
    FILE* dataFile;

	const char* fileName = filename.c_str();
    if( (dataFile = fopen(fileName, "w+" )) == NULL ){
      printf( "The file %s could not be  opened\n",fileName);
      return;
    }
 
 	double x; double y;
	//Output the data.
    for(long i = 0;  i < u.getXPanels();  i++){
		x = u.getXMin() + i*u.getHX();
		for(long j = 0; j < u.getYPanels(); j++){
			y = u.getYMin() + j*u.getHY(); 
			fprintf(dataFile,"%-10.5e %-10.5e % -10.5e\n",x,y,u(i,j));
		}
	}
    fprintf(dataFile,"\n");

    fclose(dataFile);
}

#endif
