//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Intersection.h
// Intersection points - store surface normal, time of intersection
// distance squared, surface
//
// This is used to carry data about the surface for rendering
//------------------------------------------------------------------------------



#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__


#include "STVector3.h"


class Surface;

class Intersection {

public:

                    Intersection                       (void);
                    ~Intersection                      (void);
    
    float           distanceSqu;
    STVector3       point;
    STVector3       normal;
    Surface         *surface;
};


#endif //__INTERSECTION_H__

