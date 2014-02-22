#ifndef __ProfileOutput__
#define __ProfileOutput__

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

#include "Vector1D.h"

class ProfileOutput
{
    public : 

    ProfileOutput(double xA, double xB)
    {
    this->xA = xA;
    this->xB = xB;
    };

 
    void output(Vector1D& u, long outputIndex, const char* fileNamePrefix, int outputFormat)
    {
    //
    // compose file name 
    //

    fileStringStream.str("");
    fileStringStream << fileNamePrefix;
    if     (outputIndex <= 9)  {fileStringStream << "00" << outputIndex << ".dat";}
    else if(outputIndex <= 99) {fileStringStream << "0" << outputIndex  << ".dat";}
    else                       {fileStringStream <<        outputIndex  << ".dat";}

    FILE*  dataFile;

//
//  Open and then write to a file using standard C I/O. There are two versions 
//  of the following code because Microsoft wants programmers to not use the 
//  standard library routines. 
//
#ifndef _MSC_VER
    if( (dataFile = fopen((fileStringStream.str()).c_str(), "w+" )) == NULL )
    {
      printf( "The file %s could not be  opened\n",(fileStringStream.str()).c_str());
      return;
    }
#else
	if((fopen_s(&dataFile,(fileStringStream.str()).c_str(), "w" )) != 0)
    {
      printf( "The file %s could not be  opened\n",(fileStringStream.str()).c_str());
      return;
    }
#endif

    double mPanel = u.getSize() - 1;
    double dx     = (xB-xA)/double(mPanel);
  
    long i;
    double xPos;

    if(outputFormat != EXCEL) // MATLAB or GNUPLOT format space separated columns
    {
        for(i = 0; i < mPanel+1; i++)
        {
        xPos = xA + double(i)*dx;
        fprintf(dataFile,"%18.14e %18.14e",xPos,u[i]);
        fprintf(dataFile," \n");
        }
    }
    else    // EXCEL format (tab separated columns)
    {
        for(i = 0; i < mPanel+1; i++)
        {
        xPos = xA + double(i)*dx;
        fprintf(dataFile,"%18.14e \t %18.14e",xPos,u(i));
        fprintf(dataFile," \n");
        }
    }

	fclose(dataFile);
    }

    double xA;                         // interval bounds 
    double xB; 

    enum {MATLAB,GNUPLOT,EXCEL};       // data file output types 
    ostringstream  fileStringStream;   // String stream creating output file titles

};
#endif 
