//----------------------------------------
// Copyright 2015 Corey Toler-Franklin, 
// University of Florida
// utility functions
// utilities.h
//----------------------------------------



#ifndef __UTILITIES_H__
#define __UTILITIES_H__

//---------------------------------------------------------------
// TO DO: Proj3_sceneManip
// New declarations, no implementation required
//----------------------------------------------------------------
#include "STVector3.h"
#include "STVector4.h"
#include "STMatrix4.h"
//----------------------------------------------------------------



// conversions
float               UcharToFloat                (unsigned char c);
unsigned char       floatToUchar                (float f);


//---------------------------------------------------------------
// TO DO: Proj3_sceneManip
// New Functions added here, no implementation required
//----------------------------------------------------------------

// identity matrix
STMatrix4                   IdentityMatrix          (void);
void                        STMatrix4x4tofloat16    (STMatrix4 m, float mout[16]);
void                        STPoint3toSTVector4w1   (STPoint3 m, STVector4 *mout);


STVector3           distance                    (STVector3 A, STVector3 B, STVector3 P, double *t);
float               distance                    (STVector3 a, STVector3 b);
float               distance                    (STPoint3 a, STPoint3 b);
bool                RayTest                     (STVector3 center, float radius, STVector3 position, 
                                                 const STVector3 start, const STVector3 end, 
                                                 STVector3 *pt, double *t);
float               tb_project_to_sphere        (float, float, float);
void                vset                        (float *v, float x, float y, float z);
void                vsub                        (const float *src1, const float *src2, float *dst);
void                vzero                       (float *v);
void                vcopy                       (const float *v1, float *v2);
void                vadd                        (const float *src1, const float *src2, float *dst);
void                vscale                      (float *v, float div);
void                vcross                      (const float *v1, const float *v2, float *cross);
float               vdot                        (const float *v1, const float *v2);
float               vlength                     (const float *v);
void                axis_to_quat                (float a[3], float phi, float q[4]);
void                build_rotmatrix             (float m[4][4], float q[4]);
void                normalize_quat              (float [4]);
void                vnormal                     (float *v);
void                combineQ                    (float q1[4], float q2[4], float dest[4]);

float getDistance(STVector3 center,
STVector3 start, STVector3 end,
STVector3 *pt, double *t);
//----------------------------------------------------------------



#endif //__UTILITIES_H__

