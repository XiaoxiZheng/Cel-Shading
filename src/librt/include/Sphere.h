//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Sphere.h
// Sphere surface object
//------------------------------------------------------------------------------


#ifndef __SPHERE_H__
#define __SPHERE_H__



#include "Surface.h"
#include "Ray.h"
#include "Intersection.h"


class Sphere  : public Surface 
{

public:
                                Sphere                              (void);
                                ~Sphere                             (void);

    bool                FindIntersection                    (Ray ray, Intersection *pIntersection);
	void draw();




};


#endif //__SPHERE_H__

