//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Ray.h 
// A Ray - origin and direction
//------------------------------------------------------------------------------------------------

#include "Ray.h"




Ray::Ray(void)
    : m_origin          (STVector3(0,0,0)),
      m_direction       (STVector3(0,0,1))
{

}


Ray::~Ray()
{

}


// the origin of the ray
STVector3 Ray::Origin (void)
{
    return(m_origin);
}


// the direction vector
STVector3 Ray::Direction (void)
{
    return(m_direction);
}


// the origin of the ray
void Ray::SetOrigin (STVector3 point)
{
    m_origin = point;
}


// the direction vector
void Ray::SetDirection (STVector3 point)
{
    m_direction = point;
}

