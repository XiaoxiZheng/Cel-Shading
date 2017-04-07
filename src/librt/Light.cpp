//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Light.cpp
// A light object
//------------------------------------------------------------------------------

#include "Light.h"
#include <assert.h>
#include <stdio.h>
#include <string>




Light::Light(STVector3 position, RGBR_f color, std::string id)
    :m_id               (id),
    m_color             (color),
    m_position          (position)
{

}


Light::~Light()
{

}


void Light::SetColor(RGBR_f color)
{
    m_color = color;
}


RGBR_f Light::GetColor(void)
{
    return(m_color);
}


void Light::SetPosition(STVector3 position)
{
    m_position = position;
}


STVector3 Light::GetPosition(void)
{
    return(m_position);
}






