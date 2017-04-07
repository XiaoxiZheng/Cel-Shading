//------------------------------------------------------------------------------
// Copyright 2017 Corey Toler-Franklin, University of Florida
// TRiangleMeshNode.h
// TRiangle Mesh Node for Scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO:Proj3_scenemanip
// This is a new file added for assignment Proj3_scenemanip
//------------------------------------------------------------------------------

#ifndef __SURFACENODE_H__
#define __SURFACENODE_H__

#include"GeometryNode.h"



class Surface;

class SurfaceNode: public GeometryNode {

public:

                                                    SurfaceNode                             (std::string name, SceneNode *pParent);
                                                    ~SurfaceNode                            (void);


    void                                            Initialize                              (Surface *pSurface);

    void                                            Update                                  (void);

    Surface *                                       getElement                              (void);


private:

    Surface *m_pElement;

};


#endif //__SURFACENODE_H__
//---------------------------------------------------------------------------------------------

