//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// LightNode.cpp
// Light Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------------
#include "LightNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>





LightNode::LightNode(std::string name, SceneNode *pParent) 
    : SceneNode(name, pParent)
{ 
}


LightNode::~LightNode(void) 
{ 
}


void LightNode::Initialize(Light *pLight)
{
    m_pLight = pLight;
}

// updates scene geometry
void LightNode::Update(void)
{
  // Draw  geometry 

  SceneNode::Update();
}


