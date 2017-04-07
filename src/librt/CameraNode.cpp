//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// CameraNode.cpp
// Camera Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------------
#include "CameraNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>





CameraNode::CameraNode(std::string name, SceneNode *pParent) 
    : SceneNode(name, pParent)
{ 
}


CameraNode::~CameraNode(void) 
{ 
}

// sets the  camera member
void CameraNode::Initialize(Camera *pCamera)
{
    m_pCamera = pCamera;
}

// draws the geometry
void CameraNode::Update(void)
{
  // Draw  geometry 

  SceneNode::Update();
}





