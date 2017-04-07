//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// SceneNode.cpp
// Base class for scene nodes.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// This is a new file added for assignment Proj3_scenemanip
//------------------------------------------------------------------------------------
#include "SceneNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>




SceneNode::SceneNode(std::string name, SceneNode *pParent)
    :m_parent   (pParent)
{ 
    m_name = name;
    m_worldIT = new STMatrix4();
    m_worldT = new STMatrix4();
    m_transform = new STMatrix4();
}


// destructor - calls destroy
SceneNode::~SceneNode(void) 
{ 
    Destroy();
}


// release this object from memory
void SceneNode::Release(void) 
{ 
    delete this; 
}


// update our scene node
void SceneNode::Update(void)
{
    // loop through the list and update the children
    for( std::vector<SceneNode*>::iterator i = m_lstChildren.begin(); i != m_lstChildren.end(); i++ )
    {
      (*i)->Update();
    }
}


// destroy all the children
void SceneNode::Destroy(void)
{
    for( std::vector<SceneNode*>::iterator i = m_lstChildren.begin();
        i != m_lstChildren.end(); i++ )
        (*i)->Release();

    m_lstChildren.clear();
}


// add a child to our custody
 void SceneNode::AddChild(SceneNode* pNode )
{
    m_lstChildren.push_back(pNode);
    pNode->SetParent(this);
}


 // get Children
std::vector<SceneNode*> SceneNode::GetChildren(void)
{
    return(m_lstChildren);
}


// set a pointer to the parent node
 void SceneNode::SetParent(SceneNode* pNode)
 {
     m_parent = pNode;
 }

 // set a pointer to the parent node
SceneNode *SceneNode::GetParent(void)
 {
     return(m_parent);
 }



 // get the name of this object
std::string SceneNode::GetName()
{
    return (m_name);
}





// set this object's local transform
void SceneNode::SetTransform(STMatrix4 m)
{
    *m_transform = m;
}


// set the world space transformation AB 
// where A  is the parent node's world transform
// and B is this object's local transform
void SceneNode::SetWorldT(STMatrix4 m)
{
    *m_worldT = m;
}


// set the world space transformation for normals
void SceneNode::SetWorldIT(STMatrix4 m)
{
    *m_worldIT = m;
}


// return the world space transformation AB 
// where A  is the parent node's world transform
// and B is this object's local transform
STMatrix4* SceneNode::GetWorldT(void)
{
    return(m_worldT);
}


// return the world space transformation for normals
STMatrix4* SceneNode::GetWorldIT(void)
{
    return(m_worldIT);
}


// return the local transform
STMatrix4* SceneNode::GetTransform(void)
{
    return(m_transform);
}


