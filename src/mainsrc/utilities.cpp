//----------------------------------------
// Copyright 2015 Corey Toler-Franklin, 
// University of Florida
// utility functions
// utilities.cpp
//----------------------------------------



#include "utilities.h"
#include <limits>


//------------------------------------
// conversions
//------------------------------------

// converts a unsigned char to a float
float UcharToFloat(unsigned char c) 
{
    return(c/255.0f);
}


// converts a float to unsigned char 
unsigned char floatToUchar (float f) 
{
    return((unsigned char)(f * 255));
}


bool RayTest(STVector3 center, float radius, STVector3 position, 
             STVector3 start, STVector3 end, 
             STVector3 *pt, double *t) 
{ 
    bool bHit = false;
    *pt = distance(start, end, center, t);
    // double len = distance(*pt, position); 
    float len = distance(*pt, center); 
    bHit = (len < (radius+EPSILON)); 
    return(bHit);
} 

float getDistance(STVector3 center,
	STVector3 start, STVector3 end,
	STVector3 *pt, double *t){
	*pt = distance(start, end, center, t);
	// double len = distance(*pt, position); 
	float len = distance(*pt, center);
	return len;
}

//---------------------------------------------------------------
// (c) Copyright 1993, 1994, Silicon Graphics, Inc.
//  ALL RIGHTS RESERVED
//---------------------------------------------------------------

void normalize_quat(float q[4])
{
    int i;
    float mag;

    mag = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (i = 0; i < 4; i++) q[i] /= mag;
}

float tb_project_to_sphere(float r, float x, float y)
{
    float d, t, z;

    d = sqrt(x*x + y*y);
    if (d < r * 0.70710678118654752440) {    /* Inside sphere */
        z = sqrt(r*r - d*d);
    } else {           /* On hyperbola */
        t = r / 1.41421356237309504880;
        z = t*t / d;
    }
    return z;
}

void vzero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}

void vcopy(const float *v1, float *v2)
{
    register int i;
    for (i = 0 ; i < 3 ; i++)
        v2[i] = v1[i];
}

void vsub(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] - src2[0];
    dst[1] = src1[1] - src2[1];
    dst[2] = src1[2] - src2[2];
}

void vset(float *v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}


float vlength(const float *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vcross(const float *v1, const float *v2, float *cross)
{
    float temp[3];

    temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    vcopy(temp, cross);
}

void vscale(float *v, float div)
{
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

void vadd(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] + src2[0];
    dst[1] = src1[1] + src2[1];
    dst[2] = src1[2] + src2[2];
}


float vdot(const float *v1, const float *v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}


void combineQ(float q1[4], float q2[4], float dest[4])
{
    static int count=0;
    float t1[4], t2[4], t3[4];
    float tf[4];

    vcopy(q1,t1);
    vscale(t1,q2[3]);

    vcopy(q2,t2);
    vscale(t2,q1[3]);

    vcross(q2,q1,t3);
    vadd(t1,t2,tf);
    vadd(t3,tf,tf);
    tf[3] = q1[3] * q2[3] - vdot(q1,q2);


    dest[0] = tf[0];
    dest[1] = tf[1];
    dest[2] = tf[2];
    dest[3] = tf[3];

    if (++count > RENORMCOUNT) {
        count = 0;
        normalize_quat(dest);
    }
}

void axis_to_quat(float a[3], float phi, float q[4])
{
    vnormal(a);
    vcopy(a,q);
    vscale(q,sin(phi/2.0));
    q[3] = cos(phi/2.0);
}


void vnormal(float *v)
{
    vscale(v,1.0/vlength(v));
}


void build_rotmatrix(float m[4][4], float q[4])
{
    m[0][0] = 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
    m[0][1] = 2.0 * (q[0] * q[1] - q[2] * q[3]);
    m[0][2] = 2.0 * (q[2] * q[0] + q[1] * q[3]);
    m[0][3] = 0.0;

    m[1][0] = 2.0 * (q[0] * q[1] + q[2] * q[3]);
    m[1][1]= 1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]);
    m[1][2] = 2.0 * (q[1] * q[2] - q[0] * q[3]);
    m[1][3] = 0.0;

    m[2][0] = 2.0 * (q[2] * q[0] - q[1] * q[3]);
    m[2][1] = 2.0 * (q[1] * q[2] + q[0] * q[3]);
    m[2][2] = 1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]);
    m[2][3] = 0.0;

    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
}

float distance(STVector3 a, STVector3 b)
{
    float c =  (b.x - a.x) * (b.x - a.x);
          c += (b.y - a.y) * (b.y - a.y);
          c += (b.z - a.z) * (b.z - a.z);

    float r = fabs(sqrtf(c));
    return(r);
}

float distance(STPoint3 a, STPoint3 b)
{
    float c =  (b.x - a.x) * (b.x - a.x);
          c += (b.y - a.y) * (b.y - a.y);
          c += (b.z - a.z) * (b.z - a.z);

    float r = fabs(sqrtf(c));
    return(r);
}

// distance between a line and a point
STVector3 distance(STVector3 A, STVector3 B, const STVector3 P, double *t) 
{ 
    STVector3 AB = B - A; 
    double ab_square = AB.Dot(AB, AB); 
    STVector3 AP = P - A; 
    double ap_dot_ab = AP.Dot(AP, AB); 
    // t is a projection param when we project vector AP onto AB 
    *t = ap_dot_ab / ab_square; 
    // calculate the closest point 
    STVector3 Q;
    Q = A + AB * (*t); 
    return Q; 
}  


//------------------------------------------------------------------------