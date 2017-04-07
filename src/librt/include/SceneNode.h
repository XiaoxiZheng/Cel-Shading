//------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// This is a new file added for assignment Proj3_sceneManip
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// SceneNode.h
// Base class for scenes
//------------------------------------------------------------------------------


#ifndef __SCENENODES_H__
#define __SCENENODES_H__

#include<vector>
#include "STMatrix4.h"
#include "Surface.h"

class SceneNode {

public:
                                // constructor
                                SceneNode                                       (std::string name, SceneNode *pParent);

                                // destructor - calls destroy
                                virtual ~SceneNode                             (void);

    // release this object from memory
    void                        Release                                         (void);

    // update our scene node ( holds the draw functions)
    virtual void                Update                                          (void);

    // destroy all the children
    void                        Destroy                                         (void);

    // add a child to our custody
    void                        AddChild                                        (SceneNode* pNode);

    // TO TO: proj3_scenemanip
    // These set and get a pointer to the parent node, returns a pointer to the parent node
    void                        SetParent                                       (SceneNode* pNode);
    SceneNode                   *GetParent                                      (void);
    std::vector<SceneNode*>     GetChildren                                     (void);

    void                        SetWorldT                                       (STMatrix4 m);
    void                        SetWorldIT                                      (STMatrix4 m);
    void                        SetTransform                                    (STMatrix4 m);
    STMatrix4*                  GetWorldT                                       (void);
    STMatrix4*                  GetWorldIT                                      (void);
    STMatrix4*                  GetTransform                                    (void);

    // returns the node name
    std::string                 GetName();



protected:

    // TO TO: proj3_scenemanip
    // this is the name of this node
    // whenever you make your own nodes
    // you need to initialize this node with a name
    std::string                 m_name;

    // TO TO: proj3_scenemanip
    // These matrices control the object positions
    // use the public access functions SetWorldT(m), SetWorldIT() and SetTransform() to access and set these
    STMatrix4*              m_worldT;   // AB - combined parent and local transform
    STMatrix4*              m_worldIT;  // (AB')T matrix used for normal transformations
    STMatrix4*              m_transform;  // The local transformation matrix

    // TO TO: proj3_scenemanip
    // You have the set these when adding new nodes
    SceneNode*                  m_parent;  // pointer to the parent node

    // TO TO: proj3_scenemanip
    // list of children pointed to by this node
    // No further imnplementation required here
    std::vector<SceneNode*> m_lstChildren;
};


#endif //__SCENENODE_H__
//---------------------------------------------------------------------------------------------

