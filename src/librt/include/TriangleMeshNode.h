//------------------------------------------------------------------------------
// Copyright 2017 Corey Toler-Franklin, University of Florida
// TRiangleMeshNode.h
// TRiangle Mesh Node for Scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO:Proj3_scenemanip
// This is a new file added for assignment Proj3_scenemanip
//------------------------------------------------------------------------------

#ifndef __TRIANGLEMESHNODE_H__
#define __TRIANGLEMESHNODE_H__

#include"GeometryNode.h"





class STTriangleMesh;

class TriangleMeshNode: public GeometryNode {

public:

                                                    TriangleMeshNode                        (std::string name, SceneNode *pParent);
                                                    ~TriangleMeshNode                       (void);


    void                                            Initialize                              (STTriangleMesh *pTRiangleMesg);

    void                                            Update                                  (void);

    STTriangleMesh  *                               GetElement                             (void);


private:


    STTriangleMesh  *m_pElement;

};


#endif //__TRIANGLEMESHNODE_H__
//---------------------------------------------------------------------------------------------


