//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"

// constructor
Sphere::Sphere(void)
{
      m_center = STVector3(0,0,0);
	  m_radius = 0.5;
}


// clean up here
Sphere::~Sphere()
{

}

void Sphere::draw(){

}

//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) 
{

    bool bFound = false;



   return(bFound);
}

