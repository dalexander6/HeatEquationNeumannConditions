#ifndef __Vector1D__
#define __Vector1D__

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#ifdef  _DEBUG 
#include <cstdio>
#endif
//
//####################################################################
//                    Vector1D.h
//####################################################################
/**
   
   Provides a "light weight" one dimensional vector structure
   with initialization capabilities, mathematical vector operations, and
   optional bounds checking.

   The beginning index is 0                        : (C convention)
   Access using (*), e.g. A(i) for ith element.    : (Not C convention)


   The copy constructor creates a duplicate instance.

   Created for use in Math 270E, 270C and 269B
*/
//#####################################################################
// Chris Anderson (C) UCLA                               April 19, 2012
//#####################################################################
//
class Vector1D
{
public :
//
//###################################################################
//                 Constructors/Initialization
//###################################################################
//
    Vector1D()
    {
    dataPtr      = 0;
    index1Size   = 0;
    }

    Vector1D(long m)
    {
    dataPtr       = 0;
    index1Size    = 0;
    initialize(m);
    };                                                       

    Vector1D(double* d, long m)
    {
    dataPtr       = 0;
    index1Size    = 0;
    initialize(d,m);
    };

    Vector1D(const Vector1D& D)
    {
    index1Size    = D.index1Size;
    dataPtr       = new double[index1Size];
    long i;
    for(i = 0; i < index1Size; i++){dataPtr[i] = D.dataPtr[i];}
    };                                                          ///<p>

    virtual ~Vector1D()
    {
    if(dataPtr != 0) delete [] dataPtr;
    }

    void initialize()
    {
    if(dataPtr != 0) delete [] dataPtr;
    index1Size = 0;
    }

    void initialize(const Vector1D& D)
    {
    if(dataPtr != 0) delete [] dataPtr;
    index1Size    = D.index1Size;
    dataPtr       = new double[index1Size];
    long i;
    for(i = 0; i < index1Size; i++){dataPtr[i] = D.dataPtr[i];}

    }
    void initialize(long m)
    {

    if(index1Size != m)
    {
       delete [] dataPtr;
       dataPtr = new double[m];
    }

    index1Size    = m;
    for(long i = 0; i < index1Size; i++)
    {dataPtr[i] = 0.0;}                                     
    };

    void initialize(double* d, long m)
    {
    initialize(m);
    for(long i = 0; i < index1Size; i++) {dataPtr[i] = d[i];}
    };
//
//###################################################################
//                  Element Access 
//###################################################################
//

#ifdef _DEBUG 
    double&  operator()(long i1)
    {
    boundsCheck(i1, 0, index1Size-1,1);
    return *(dataPtr +  i1);
    };

    double&  operator[](long i1)
    {
    boundsCheck(i1, 0, index1Size-1,1);
    return *(dataPtr +  i1);
    };

    const double&  operator()(long i1) const
    {
    boundsCheck(i1, 0, index1Size-1,1);
    return *(dataPtr +  i1);
    };                                                     
#else

    inline double&  operator()(long i1)
    {
    return *(dataPtr + i1);
    };

    inline double&  operator[](long i1)
    {
    return *(dataPtr + i1);
    };

    inline const double&  operator()(long i1) const
    {
    return *(dataPtr +  i1);
    };

    inline const double&  operator[](long i1) const
    {
    return *(dataPtr +  i1);
    };
#endif

//
//###################################################################
//                Array Structure Access Functions
//###################################################################
//

    double* getDataPointer(){return dataPtr;};   

    long getSize()  const {return index1Size;}
    long getIndex1Size()  const {return index1Size;}

    // Resizes array to exactly newSize

    void resize(long newSize)
    {
    long i;
    double*  newDataPtr = new double[newSize];
    double*  tmpDataPtr;

    if(newSize > index1Size) 
    {
        for(i = 0; i < index1Size; i++) newDataPtr[i] = dataPtr[i];
    }
    else
    {
        for(i = 0; i < newSize; i++) newDataPtr[i] = dataPtr[i];
    }

    index1Size = newSize;
    tmpDataPtr = dataPtr;
    dataPtr    = newDataPtr;

    if(tmpDataPtr != 0) delete [] tmpDataPtr;
    }



//
//###################################################################
//                     Vector Operators
//###################################################################
//

Vector1D operator+(const Vector1D& D)
{
    #ifdef _DEBUG 
    sizeCheck(this->index1Size,D.index1Size);
    #endif
    Vector1D R(*this);
    for(long i = 0; i < index1Size; i++)
    {
    R.dataPtr[i] += D.dataPtr[i];
    }
    return R;
}

Vector1D operator-(const Vector1D& D)
{
    #ifdef _DEBUG 
    sizeCheck(this->index1Size,D.index1Size);
    #endif
    Vector1D R(*this);
    for(long i = 0; i < index1Size; i++)
    {
    R.dataPtr[i] -= D.dataPtr[i];
    }
    return R;
}

Vector1D operator*(double alpha)
{
    Vector1D R(*this);
    for(long i = 0; i < index1Size; i++)
    {
    R.dataPtr[i] *= alpha;
    }
    return R;
}

friend Vector1D operator*(double alpha, const Vector1D& D)
{
    Vector1D R(D);
    for(long i = 0; i < D.index1Size; i++)
    {
    R.dataPtr[i] *= alpha;
    }
    return R;
}
                                                                ///<p>
Vector1D operator/(double alpha)
{
    Vector1D R(*this);
    for(long i = 0; i < index1Size; i++)
    {
    R.dataPtr[i] /= alpha;
    }
    return R;
}
//
//###################################################################
//          
//###################################################################
//
void operator=(const Vector1D& D)
{
    #ifdef _DEBUG 
    if(index1Size != 0)
    {
    sizeCheck(this->index1Size,D.index1Size);
    }
    #endif

//  If *this is a null instance, then initialize

    if(index1Size == 0)
    {
    initialize(D.index1Size);
    index1Size = D.index1Size;
    }

//  copy over the data

    for(long i = 0; i < D.index1Size; i++)
    {dataPtr[i] = D.dataPtr[i];}
}

void operator*=(double alpha)
{
    for(long i = 0; i < index1Size; i++)
    {dataPtr[i] *= alpha;}
}

void operator+=(const Vector1D& D)
{
    #ifdef _DEBUG 
    if(index1Size != 0)
    {
    sizeCheck(this->index1Size,D.index1Size);
    }
    #endif

    for(long i = 0; i < D.index1Size; i++)
    {dataPtr[i] += D.dataPtr[i];}
}                                                            ///<p>

void operator-=(const Vector1D& D)
{
    #ifdef _DEBUG 
    if(index1Size != 0)
    {
    sizeCheck(this->index1Size,D.index1Size);
    }
    #endif

    for(long i = 0; i < D.index1Size; i++)
    {dataPtr[i] -= D.dataPtr[i];}
}

void setToValue(double d)
{
    for(long i = 0; i < index1Size; i++)
    {
     dataPtr[i] = d;
    }
}

double dot(Vector1D& v)
{
    double dotVal = 0.0;
    for(long i = 0; i < index1Size; i++)
    {
    dotVal += (dataPtr[i]*v.dataPtr[i]);
    }
    return dotVal;
}

double normInf() const
{
    double valMax = 0.0;
    for(long i = 0; i < index1Size; i++)
    {
    valMax = (valMax > fabs(dataPtr[i])) ? valMax : fabs(dataPtr[i]);
    }
    return valMax;
}

double norm2() const
{
    double val = 0.0;
    for(long i = 0; i < index1Size; i++)
    {
    val += (dataPtr[i]*dataPtr[i]);
    }
    return sqrt(fabs(val));
}

double norm1() const
{
    double val = 0.0;
    for(long i = 0; i < index1Size; i++)
    {
    val += fabs(dataPtr[i]);
    }
    return val;
}

double normp(double p) const
{
    double val = 0.0;
    for(long i = 0; i < index1Size; i++)
    {
    val += pow(fabs(dataPtr[i]),p);
    }
    return val;
}

long getDimension()
{
    return index1Size;
}

//
//  Output
//
friend ostream& operator<<(ostream& outStream, const Vector1D& V)
{

    long i; 
    for(i = 0; i <  V.index1Size; i++)
    { 
      outStream <<  setw(5) << V.dataPtr[i] << " ";

    }
    outStream << endl;
    return outStream;
}
//
//###################################################################
//                      Class Data Members
//###################################################################
//
    protected :

    double*      dataPtr;     // data pointer
    long    index1Size;       // coordinate 1 size

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
    }
    }
#else
static void boundsCheck(long, long, long, int){}
#endif

#ifdef _DEBUG 
    static void sizeCheck(long size1, long size2)
    {
    if(size1 != size2)
    {
    printf("Array Sizes Are Incompatable %ld != %ld \n", size1, size2);
    }
    }
#else
static void sizeCheck(long, long){}
#endif
    
};

#endif


 
