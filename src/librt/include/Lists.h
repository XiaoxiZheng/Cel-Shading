//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Lists.h
// List Definitions
//------------------------------------------------------------------------------


#ifndef __LISTS_H__
#define __LISTS_H__

#include <vector>
#include "Light.h"
#include "Intersection.h"


class Surface;
class TriangleMeshNode;


// convenient lists of objects
typedef std::vector<TriangleMeshNode*> GeometryList;
typedef std::vector<Surface*> SurfaceList;
typedef std::vector<Light *> LightList;
typedef std::vector<Intersection> IntersectionList;


#endif //__LISTS_H__

