#ifndef _DoubleArray2D_
#define _DoubleArray2D_

#include <iostream>
#include <iomanip>
using namespace std;

//
//####################################################################
//                    DoubleArray2D.h
//####################################################################
/**
   Provides a very "light weight" two dimensional array structure
   with initialization capabilities and optional bounds checking.

   <pre>
   The beginning index is 0               : (C convention)
   Data for the array is stored by ROWS   : (C convention)
   Access using (*,*), e.g. A(i,j) for (i,j)th element.: (NOT C convention) 
   </pre>

   The copy constructor creates a duplicate instance. Deleting the copy 
   will not delete the data of the original. <p>
   Created for use in Math 270A<p>

@author Chris Anderson (C) UCLA 
@version  Oct. 15, 2010
*/
//#####################################################################
// Chris Anderson (C) UCLA                               Oct. 15, 2010
//#####################################################################
//
class DoubleArray2D
{

public :
//
//###################################################################
//                 Constructors/Initialization
//###################################################################
//
    DoubleArray2D()
    {
    dataPtr       = 0;
    index1Size    = 0;
    index2Size    = 0;
    };

    DoubleArray2D(long m, long n)
    {
    dataPtr       = 0;
    index1Size    = 0;
    index2Size    = 0;
    initialize(m,n);
    };

    DoubleArray2D(const DoubleArray2D& D)
    {    
	dataPtr       = 0;
	index1Size    = 0;
	index2Size    = 0;
    initialize(D);
    };

    virtual ~DoubleArray2D()
    {
    if(dataPtr !=  0) delete [] dataPtr;
    }


    void initialize()
    {
    if(dataPtr !=  0) delete [] dataPtr;
    dataPtr       = 0;
    index1Size    = 0;
    index2Size    = 0;
    };


    void initialize(const DoubleArray2D& D)
    {

    if((index1Size !=  D.index1Size)||(index2Size != D.index2Size))
    {
    if(dataPtr != 0) delete [] dataPtr;
    index1Size    = D.index1Size;
    index2Size    = D.index2Size;
	dataPtr       = new double[index1Size*index2Size];
    }

	for(long i = 0; i < index1Size*index2Size; i++)
	{dataPtr[i] = D.dataPtr[i];}

    };


    void initialize(long m, long n)
    {
    if((index1Size != m)||(index2Size != n))
    {
        if(dataPtr != 0) delete [] dataPtr;
        index1Size    = m;
        index2Size    = n;
    	dataPtr       = new double[index1Size*index2Size];
    }

	for(long i = 0; i  < index1Size*index2Size; i++)
	{dataPtr[i] = 0.0;}
    };


    void operator=(const DoubleArray2D& D)
    {
	initialize(D);
    }
//
//###################################################################
//      Element Access with bounds checking toggled
//      using _DEBUG
//###################################################################
//
#ifdef _DEBUG 
    double&  operator()(long i1, long i2)
    {
    boundsCheck(i1, 0, index1Size-1,1);
    boundsCheck(i2, 0, index2Size-1,2);
    return *(dataPtr +  i2 + i1*index2Size);
    };

    const double&  operator()(long i1, long i2) const
    {
    boundsCheck(i1, 0, index1Size-1,1);
    boundsCheck(i2, 0, index2Size-1,2);
    return *(dataPtr +   i2  + i1*index2Size);
    };
#else
    inline double&  operator()(long i1, long i2)
    {
    return *(dataPtr +  i2 + i1*index2Size);
    };

    inline const double&  operator()(long i1, long i2) const
    {
    return *(dataPtr +  i2  + i1*index2Size);
    };
#endif

//
//###################################################################
//                Array Structure Access Functions
//###################################################################
//
    long getIndex1Size()  const {return index1Size;}
    long getIndex2Size()  const {return index2Size;}

    long getDataSize() const {return index1Size*index2Size;}

    double* const getDataPointer() const {return dataPtr;}

//  Input/Output
//
//  Prints out values as as if they were in the first Cartesian 
//  quadrant --- not in matrix indexing. 
//
//
friend ostream&  operator <<(ostream& outStream, const DoubleArray2D& A)
{
    for(long j = A.index2Size-1; j >=  0; j--)
    {
    for(long i = 0; i <=  A.index1Size-1; i++)
    {
      outStream <<  setw(5) << A(i,j) << " ";
    }
      outStream << endl;
    }
    return outStream;
}
//
//###################################################################
//                      Class Data Members
//###################################################################
//
    protected :

    double*      dataPtr;     // data pointer
    long      index1Size;     // coordinate 1 size
    long      index2Size;     // coordinate 2 size
//
//###################################################################
//                      Bounds Checking
//###################################################################
//
#ifdef _DEBUG
    static void boundsCheck(long i, long begin, long end, int coordinate)
    {
    if((i < begin)||(i  > end))
    {
    printf("Array index %d out of bounds \n",coordinate);
    printf("Offending index value %ld : Acceptable Range [%ld, %ld] \n",i, begin, end);
    }}
#else
static void boundsCheck(long, long, long, int){}
#endif
};


#endif  /* _DoubleArray2D_    */

