//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Triangle.h
// Defines a triangle surface enclosed by three points m_a, m_b, m_c
//-----------------------------------------------------------------------------


#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__



#include "Surface.h"
#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"



class Triangle : public Surface
{

public:
	Triangle(void);
	Triangle(std::string name);
								Triangle(std::string name,STVector3 a, STVector3 b, STVector3 c);
                                ~Triangle                       (void);

    bool                        FindIntersection                (Ray ray, Intersection *pIntersection);
	void						draw();

private:


    // vertices


    // linear systems
    bool                        IntersectionSolver              (Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w);

    STVector3                   ComputeNormalVector             (void);




};


#endif //__TRIANGLE_H__

