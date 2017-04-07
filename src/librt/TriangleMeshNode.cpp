//------------------------------------------------------------------------------
// Copyright 2017 Corey Toler-Franklin, University of Florida
// GeometryNode.cpp
// Geometry Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------------



#include "TriangleMeshNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Triangle.h"
#include "STTriangleMesh.h"



TriangleMeshNode::TriangleMeshNode(std::string name, SceneNode *pParent)
    : GeometryNode(name, pParent, GeometryNode::TRIANGLEMESH),
    m_pElement(NULL)
{ 
}


TriangleMeshNode::~TriangleMeshNode(void) 
{ 
}


void TriangleMeshNode::Initialize(STTriangleMesh *pTriangle)
{
    assert(m_type == GeometryNode::TRIANGLEMESH);
    m_pElement = pTriangle;
}



STTriangleMesh *TriangleMeshNode::GetElement(void)
{
    return(m_pElement);
}



void TriangleMeshNode::Update(void)
{
    if(m_pElement) {
        m_pElement->Draw(true);
    }

    // Draw  geometry 
    GeometryNode::Update();
}

