//------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// This is a new file added for assignment Proj3_scenemanip
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// CameraNode.h
// Camera Node for scenes
//------------------------------------------------------------------------------


#ifndef __CAMERANODE_H__
#define __CAMERANODE_H__

#include"SceneNode.h"
#include"Camera.h"

class CameraNode: public SceneNode {

public:

                                            CameraNode(std::string name, SceneNode *pParent);
                                            ~CameraNode             (void);

                        void                Update                  (void);
                        void                Initialize              (Camera *pCamera);

private:

    Camera *m_pCamera;

};


#endif //__CAMERANODE_H__
//---------------------------------------------------------------------------------------------

