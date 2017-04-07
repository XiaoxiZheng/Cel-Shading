//------------------------------------------------------------------------------
// Copyright 2017 Corey Toler-Franklin, University of Florida
// TriangleMeshNode.cpp
// TriangleMeshNode
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// This is a new file added for assignment Proj3_sceneManip
//-------------------------------------------------------------------------------------


# include <glut.h>


#include "GeometryNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>




GeometryNode::GeometryNode(std::string name, SceneNode *pParent, GeometryType type) 
    :SceneNode      (name, pParent),
     m_type         (type)
{ 
}


GeometryNode::~GeometryNode(void) 
{ 
}

