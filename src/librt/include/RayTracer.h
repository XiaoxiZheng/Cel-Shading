//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------



#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__


#include<string>
#include "defs.h"
#include "Scene.h"
#include "RGBR_f.h"

class Shader;

class RayTracer
{

public:
                                RayTracer                                       (void);
                                ~RayTracer                                      (void);

    void                        Run                                             (Scene *pScene, std::string fName, RenderMode mode);



private:

    Shader                      *pShader;

    int                         m_maxLevel;
    float                       m_intensityThreshold;

    bool                        MinimumColor                                    (RGBR_f color);

    RGBR_f                      Shade                                           (Scene *pScene, Intersection *pIntersection);

};


#endif //__RAYTRACER_H__

