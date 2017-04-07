//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// TransformNode.h
// Transform Node for scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------


#ifndef __TRANSFORMNODE_H__
#define __TRANSFORMNODE_H__



#include"SceneNode.h"
#include "STMatrix4.h"



class TransformNode: public SceneNode {

public:

                                            TransformNode               (std::string name, SceneNode *pParent);
                                            ~TransformNode              (void);

                        void                Initialize                  (STMatrix4 m);
						void				set(STMatrix4 m);
                        void                Update                      (void);




    STMatrix4           m_Matrix; 
	
};


#endif //__TRANSFORMNODE_H__
//---------------------------------------------------------------------------------------------

