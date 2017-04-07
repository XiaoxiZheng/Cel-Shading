//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// LightNode.h
// Light Node for scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------


#ifndef __LIGHTNODE_H__
#define __LIGHTNODE_H__

#include"SceneNode.h"


class Light;

class LightNode: public SceneNode {

public:

                                            LightNode                   (std::string name, SceneNode *pParent);
                                            ~LightNode                  (void);
                                            
    void                                    Initialize                  (Light *pLight);

    void                                     Update                     (void);

private:

    Light           *m_pLight;

};


#endif //__LIGHTNODE_H__
//---------------------------------------------------------------------------------------------

