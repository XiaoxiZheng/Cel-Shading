//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// GeometryNode.h
// Geometry Node for scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO:Proj3_scenemanip
// This is a new file added for assignment Proj3_scenemanip
//------------------------------------------------------------------------------

#ifndef __GEOMETRYNODE_H__
#define __GEOMETRYNODE_H__

#include"SceneNode.h"






class GeometryNode: public SceneNode {




public:

typedef enum {
    SURFACE          = 0, 
    TRIANGLEMESH      = 1, 
}GeometryType;



                                            GeometryNode                        (std::string name, SceneNode *pParent, GeometryType type);
                                            ~GeometryNode                       (void);
                                                

    virtual void                            Initialize                          () { std::cout << "Initializing ..."; }

    virtual void                             Update                             ()  {; }


protected:

    GeometryType                            m_type;




};


#endif //__GEOMETRYNODE_H__
//---------------------------------------------------------------------------------------------

