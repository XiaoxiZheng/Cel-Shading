    //------------------------------------------------------------------------------------
    // TO DO: Proj3_4 OpenGL
    // These are new members added to the matrix class for this assignment
    // No implementation required
    //------------------------------------------------------------------------------------

// STMatrix4.h
#ifndef __STMATRIX4_H__
#define __STMATRIX4_H__

#include "stForward.h"

#include <math.h>

/**
* STMatrix4 represents a 4x4 matrix
*/
struct STMatrix4
{
    inline STMatrix4();
    inline STMatrix4( const float* pf );
    inline void EncodeI();
    inline void EncodeT(float tx,float ty,float tz);
    inline void EncodeS(float sx,float sy,float sz);
    inline void EncodeR(float degrees,const STVector3& axis);
	inline void inv();
	inline bool gluInvertMatrix(float* m, float* invOut);
	inline void trans(float* in, float* out);
	inline void transpose();

    inline void GetT(float *tx,float *ty,float *tz);

    void Multiply( const STMatrix4 &m1, const STMatrix4 &m2 );
    void Multiply( const STMatrix4 &matrix);

    inline STVector3 operator*(const STVector3& v);
    STMatrix4 operator * ( const STMatrix4& mat) const;

    //
    // Local members
    //
    float table[4][4];

    /*CS148 -- implement other member functions here as necessary*/

};

#include "STMatrix4.inl"

#endif  // __STMATRIX4_H__
