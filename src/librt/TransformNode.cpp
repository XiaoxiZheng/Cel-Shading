//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// TransformNode.cpp
// Transform Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// This is a new file added for assignment Proj3_scenemanip
//------------------------------------------------------------------------------------
#include "TransformNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "stgl.h"




TransformNode::TransformNode(std::string name, SceneNode *pParent) :
    SceneNode(name, pParent)
{ 
}


TransformNode::~TransformNode(void) 
{ 
}


void TransformNode::Initialize(STMatrix4 m)
{
    m_Matrix = m;
}

void TransformNode::set(STMatrix4 m)
{
	m_Matrix = m;
}

// update the matrix transform on the stack
void TransformNode::Update(void)
{

    glPushMatrix();
    glMultMatrixf((float *)m_Matrix.table);


    SceneNode::Update();

    glPopMatrix();
}


