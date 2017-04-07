//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"



Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}


// Runs the shader according to the specified render mode
RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection)
{
    RGBR_f color;

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection);
            break;
        case PHONG:
            color = Phong(pIntersection, lightDirection);
            break;
        default:
            color = Lambertian(pIntersection, lightDirection);
            break;
        }



    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection)
{
    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;

    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 *lightDirection)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;



    return(color);
}


Shader::~Shader()
{
}

