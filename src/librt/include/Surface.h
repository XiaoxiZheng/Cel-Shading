//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.h
// Defines the base class for surfaces
//-----------------------------------------------------------------------------

#ifndef _SURFACE_H
#define _SURFACE_H


#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"
#include "defs.h"
#include "Lists.h"



class Surface
{

    public:
		Surface(void);
                                    Surface                             (std::string name);
                                    ~Surface                            (void);
	virtual								void							draw();
    virtual bool                    FindIntersection                     (Ray ray, Intersection *pIntersection){ return(false);} 
    int                             FindClosestIntersection             (Intersection *pIntersection);
	STVector3						GetPosition							();
	std::string		                getSurfaceNmae();
	void	                        setSurfaceNmae(std::string name);

	STVector3                   m_a;
	STVector3                   m_b;
	STVector3                   m_c;
	float                       m_radius;
	std::string						m_name;
protected:
    



    IntersectionList                m_intersections;

    STVector3                       m_center;

};


#endif //_SURFACE_H



