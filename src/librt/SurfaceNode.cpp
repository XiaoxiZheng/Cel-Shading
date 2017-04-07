//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// GeometryNode.cpp
// Geometry Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------------


#include "SurfaceNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Surface.h"



SurfaceNode::SurfaceNode(std::string name, SceneNode *pParent) 
    :GeometryNode(name, pParent, GeometryType::SURFACE),
     m_pElement(NULL)
{ 
}


 SurfaceNode::~SurfaceNode(void) 
{ 
}


void SurfaceNode::Initialize(Surface *pSurface)
{
    assert(m_type == GeometryType::SURFACE);
    m_pElement = pSurface;
}

Surface *SurfaceNode::getElement(void)
{
    return(m_pElement);
}



void SurfaceNode::Update(void)
{
    // Draw  geometry 
    // need code here for surface drawing
    SceneNode::Update();
}

