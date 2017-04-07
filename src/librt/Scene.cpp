//------------------------------------------------------------------------------
// Copyright 2017 Corey Toler-Franklin, University of Florida
// Scene.cpp
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------



// GLEW
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Scene.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Intersection.h"
#include "Surface.h"
#include "Light.h"
#include "Sphere.h"
#include "STMatrix4.h"
#include "STVector2.h"
#include "CameraNode.h"
#include "TransformNode.h"
#include "LightNode.h"
#include "GeometryNode.h"
#include "utilities.h"
#include "STVector3.h"
#include "Triangle.h"
#include "TriangleMeshNode.h"
#include "STTriangleMesh.h"
#include "SurfaceNode.h"
#include "STVector4.h"


Scene::Scene(void)
    : m_background(RGBR_f(0, 0, 0, 1)),
      m_pCamera(NULL),
      m_renderMode(LAMBERTIAN),
      m_bHasManipulator (false),
      m_manipMotionType(MANIP_NONE), 
      m_activeManipGeom(AXIS_NONE),
      m_translatex(0),
      m_translatey(0),
      m_translatez(0),
      m_prex(0),
      m_prey(0),
      m_prez(0),
      m_flagx(0),
      m_flagy(0),
      m_flagz(0),
      m_rotatex(0),
      m_rotatey(0),
      m_rotatez(0),
      m_pLight(NULL),
      vpscreenfactor(1.0),
      screenScale(1.0),
      Ng2(0)
 {

    // init matrices
    m_rotation = IdentityMatrix();
    m_trans = IdentityMatrix();

    // init lights - ambiennt and diffuse
    InitLights();

    // init camera
    m_pCamera = new Camera();
   
    // Initialize the scene graph root
    m_pTree = new SceneNode("root", NULL);
    m_pTree->SetTransform(IdentityMatrix());
    m_pTree->SetWorldIT(IdentityMatrix());
    m_pTree->SetWorldIT(IdentityMatrix());

    // add a new CameraNode
    CameraNode *cNode = new CameraNode("camera", m_pTree);
    cNode->Initialize(m_pCamera);
    cNode->SetTransform(IdentityMatrix());
    cNode->SetWorldT(IdentityMatrix());
    cNode->SetWorldIT(IdentityMatrix());
    m_pTree->AddChild(cNode);

    // add a new lightnode
    AddLight(m_pLight, m_pTree);

    // set up the manipulation mode
    InitManipMode();
}


Scene::~Scene()
{

    //------------------------------------------------------------------------------------
    // TO DO: Proj3_sceneManip
    // clean  up 
    // 1. delete all the scene nodes
    // 2. empty the GeometryList (or whatever scene structure you use)
    //-------------------------------------------------------------------------------------

    if(m_pLight)
        delete(m_pLight);

    if(m_pCamera)
        delete(m_pCamera);


}





// initializes light parameters
void Scene::InitLights(void)
{
    ambientLight[0] = 0.20f;
    ambientLight[1] = 0.20f;
    ambientLight[2] = 0.20;
    ambientLight[3] = 1.0f;

    diffuseLight[0] = 1.0f;
    diffuseLight[1] = 1.0f;
    diffuseLight[2] = 1.0f;
    diffuseLight[3] = 1.0f;

    specularLight[0] = 1.0f;
    specularLight[1] = 1.0f;
    specularLight[2] = 1.0f;
    specularLight[3] = 1.0f;

    STVector3 position(-30.0f, 30.0f, 30.0f);
    m_pLight = new Light(position, RGBR_f(1.0,1.0,1.0,1.0), "light");
}

SceneNode * Scene::GetRoot(void)
{
    return(m_pTree);
}


void Scene::SetBackgroundColor(RGBR_f color)
{
    m_background = color;
}


RGBR_f Scene::GetBackgroundColor(void)
{
    return(m_background);
}


LightNode *Scene::AddLight(Light *lightin, SceneNode *pNode)
{
    m_lights.push_back(lightin);

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// lightin - light to add, the parent node (already in the tree)
// Add the light to the scene graph
// This is how lights are added to the graph
// 1. Create a new LightNode
// 2. Initialize the node with the light
// 3. Set transforms to I
// 4. Add the to the parent
//------------------------------------------------------------------------------------
    //create the lightnode
    LightNode *lightnode = new LightNode("lightNode", pNode);
    lightnode->Initialize(lightin);

    lightnode->SetTransform(IdentityMatrix());
    lightnode->SetWorldT(IdentityMatrix());
    lightnode->SetWorldIT(IdentityMatrix());

    // add
    pNode->AddChild(lightnode);

    return(lightnode);
//------------------------------------------------------------------------------------

}


TransformNode *Scene::AddTransform(STMatrix4 matrixin, SceneNode *pNode)
{

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// matrixin - transform to add, the parent node (already in the tree)
// Add the transform to the scene graph
// This is how transforms are added to the graph
// 1. Create a new TransformNode
// 2. Initialize the node with the matrixin
// 3. Set other transforms to I
// 4. Add the to the parent
//------------------------------------------------------------------------------------
    //create the transform node
    TransformNode *transnode = new TransformNode("transNode", pNode);
    transnode->SetTransform(matrixin);
    transnode->SetWorldT(matrixin);
    transnode->SetWorldIT(IdentityMatrix());

    // add
    pNode->AddChild(transnode);

    return(transnode);

//------------------------------------------------------------------------------------

}
SurfaceNode *Scene::AddSurface(Surface *pSurfacein, SceneNode *pNode)
{



//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// pSurfacein - surface to add, the parent node (already in the tree)
// Add the surface to the scene graph
// This is how surfaces are added to the graph
// 1. Create a new SurfaceNode
// 2. Initialize the node with the surface
// 3. Set transforms to I
// 4. Add the to the parent
//------------------------------------------------------------------------------------
    SurfaceNode *surface = new SurfaceNode("geomNode", pNode);
    surface->Initialize(pSurfacein);
    surface->SetTransform(IdentityMatrix());
    surface->SetWorldT(IdentityMatrix());
    surface->SetWorldIT(IdentityMatrix());

    pNode->AddChild(surface);

    return(surface);

//-------------------------------------------------------------------------------------
}



//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// adds a  triangle mesh to the scene
// Input: STTriangleMesh 
TriangleMeshNode *Scene::AddTriangleMesh(STTriangleMesh *pTrianglein, SceneNode *pNode)
{

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// pTrianglein - triangle mesh to add, the parent node (already in the tree)
// Add the geometry to the scene graph
// This is how triangle meshes are added to the graph
// You might change the way nodes are added to form your scene graph tree
// 1. Create a new TriangleMeshNode
// 2. Initialize the node with the mesh
// 3. Set transforms to I
// 4. Add the to the parent and geometry list
//------------------------------------------------------------------------------------


    TriangleMeshNode *tmeshnode = new TriangleMeshNode("geomNode", pNode);
    tmeshnode->Initialize(pTrianglein);
    tmeshnode->SetTransform(IdentityMatrix());
    tmeshnode->SetWorldT(IdentityMatrix());
    tmeshnode->SetWorldIT(IdentityMatrix());

    m_geometryList.push_back(tmeshnode);

    pNode->AddChild(tmeshnode);

    return(tmeshnode);

//-------------------------------------------------------------------------------------
}


void Scene::GetBBox(STPoint3 *gMassCenter, std::pair<STPoint3,STPoint3>  *gBoundingBox)
{
    std::vector<STTriangleMesh *> gTriangleMeshes;
    for(int i = 0; i < (int)m_geometryList.size(); ++i) {
        gTriangleMeshes.push_back(m_geometryList[i]->GetElement());
    }
    *gMassCenter = STTriangleMesh::GetMassCenter(gTriangleMeshes);
    *gBoundingBox=STTriangleMesh::GetBoundingBox(gTriangleMeshes);
    

    // transform bbox to model space
    STMatrix4 worldtransform = *(m_geometryList[0]->GetWorldT());
    STVector4 gmasscentervec4;
    STPoint3toSTVector4w1(*gMassCenter, &gmasscentervec4);
    STVector4 gmasscentervec4_new; 
    gmasscentervec4.Transform(worldtransform);
    STVector4 bboxmin; 
    STVector4 bboxmax; 
    STPoint3toSTVector4w1(gBoundingBox->first, &bboxmin);
    STPoint3toSTVector4w1(gBoundingBox->second, &bboxmax);
    bboxmin.Transform(worldtransform);
    bboxmax.Transform(worldtransform);
    gMassCenter->x = gmasscentervec4.x;
    gMassCenter->y = gmasscentervec4.y;
    gMassCenter->z = gmasscentervec4.z;
    gBoundingBox->first.x = bboxmin.x;
    gBoundingBox->first.y = bboxmin.y;
    gBoundingBox->first.z = bboxmin.z;
    gBoundingBox->second.x = bboxmax.x;
    gBoundingBox->second.y = bboxmax.y;
    gBoundingBox->second.z = bboxmax.z;
}


Camera *Scene::GetCamera(void)
{
    return(m_pCamera);
}


// computes the direction of the light in the scene
// and returns it
void Scene::GetLightPosition(float position[4])
{
    STVector3 positionvec = m_pLight->GetPosition();
    position[0] = positionvec.x;
    position[1] = positionvec.y;
    position[2] = positionvec.z;
    position[3] = 1.0f;
}




//-----------------------------------------------------
// clear the scene by removing surfaces
//-----------------------------------------------------
void Scene::Clear(void)
{
    GeometryList::iterator iter = m_geometryList.begin();
    GeometryList::iterator end  = m_geometryList.end();

    // delete objects
    for (; iter != end; ++iter) {
        delete *iter;
        *iter = NULL;
    }

    // clean up
    m_geometryList.clear();
}


//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// Update this code to draw the object correctly
// Note that - tree traversal and transform propogation has already happened when this function is called.
// This means that PropogateTransforms(m_pTree) has updated each scene node so that it has it's world transform 
// and normal transform already updated and stored.
// To complete this function:
// 1. Adjust this function to call draw on each geometry node in your new tree structure.
//    Currently it loops through the list m_geometryList and draws triangle meshes. If you are still managing this list
//    no change is necessary for this item.
// 2. Make sure that normals are actually transformed correctly before each draw call to void STTriangleMesh::Draw(bool smooth) const. 
//     There are many options for this: For example
//   - copy the TrangleMesh::Draw function in TrangleMesh.cpp (don't forget to declare the new function as public in the TriangleMesh.h)
//     but add the new input worldIT. Send in the worldIT of the current mesh. At every call to glNormal3f in the function 
//     TTriangleMesh::Draw(bool smooth, STMatrix4 worldIT) const, adjust the code to transform the normals by worldIT first.
//------------------------------------------------------------------------------------
void Scene::Draw(void)
{
    // for each geometry node in the tree
    for (int i = 0; i < (int)m_geometryList.size(); ++i) {

        // world transformation of this object and world normal transformation 
        STMatrix4 *myworldT;
        STMatrix4 *myworldIT;
        myworldT =  m_geometryList[i]->GetWorldT();
        myworldIT =  m_geometryList[i]->GetWorldIT();
        float myworldT_f[16];
        float myworldIT_f[16];
        STMatrix4x4tofloat16(*myworldT, myworldT_f);
        STMatrix4x4tofloat16(*myworldIT, myworldIT_f);

        // update the OpenGL model view matrix with the world matrix
        glMatrixMode(GL_MODELVIEW);  // set the OpenGL matrix mode
        glPushMatrix(); // push the matrix on the stack
        glMultMatrixf(myworldT_f); // update the modelview matrix by applying myworldT to it

        // now draw the scene and the manipulators if they are in the scene
        m_geometryList[i]->GetElement()->Draw(true);
        if((GetRenderMode() == NAVIGATION) 
            && ((CurrentManipMode() == LOCAL)
                || (CurrentManipMode() == PARENT))
            && (HasManipulator())) { 
                DrawManipulator();
        }
        // pop the matrix off the stack
        glPopMatrix();

    }
}








//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// These are all of the new functions added to the scene class for this assignment
//------------------------------------------------------------------------------------


STVector3 Scene::GetLightPosition(void)
{
    if(m_lights.size())
        return(m_lights[0]->GetPosition());

    STVector3 p(10.0f, 15.0f, 10.0f);
    return(p);
}


// toggles between modes
void Scene::ToggleRenderMode(void)
{
    if(m_renderMode == NAVIGATION) {
        RemoveManip();
        InitManipMode();
        m_renderMode = ENVIRONMENTMAP;
    }
    else if(m_renderMode == ENVIRONMENTMAP) {
        m_renderMode = NAVIGATION;
        InitManipMode();
    }
}

// toggles between modes
void Scene::ToggleManipMode(void)
{
    if(m_renderMode == NAVIGATION) {
        m_modeQueue.push(m_modeQueue.front());
        m_modeQueue.pop();
    }
}


// toggles between modes
// make different parts of the geometry visible
void Scene::ToggleManipGeometry(void)
{
    if((m_renderMode == NAVIGATION) && (m_bHasManipulator)){
        if(m_manipGeomQueue.front() == AXIS_ROTATIONALL) {
            RemoveManip();
            InitManipGeometryMode();
        }
        else {
            m_manipGeomQueue.push(m_manipGeomQueue.front());
            m_manipGeomQueue.pop();
        }
    }
    else if((m_renderMode == NAVIGATION) &&  (!m_bHasManipulator)) {
        AddManipulator();
    }
}


// Inits the current mode
void Scene::InitManipMode(void)
{
    std::queue<ManipMode> empty;
    std::swap(m_modeQueue, empty);
    m_modeQueue.push(LOCAL);
    m_modeQueue.push(PARENT);
    m_modeQueue.push(NONE);

    InitManipGeometryMode();
    RemoveManip();
}


// Inits the current manip geometry mode
// helps with selection to show individual parts
void Scene::InitManipGeometryMode(void)
{
    std::queue<ManipGeom> empty;
    std::swap(m_manipGeomQueue, empty);
    m_manipGeomQueue.push(AXIS_ALL);
    m_manipGeomQueue.push(AXIS_TRANSXYZ);
    m_manipGeomQueue.push(AXIS_ROTATIONALL);
}


//------------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// Called whenever the object must move because the translation manipulator is called.
// prevMousePos - previous mouse position
// curMousePos - current mouse position
// You must complete this implementation
//------------------------------------------------------------------------------------------
//void Scene::Translate(STVector3 prevMousePos, STVector3 curMousePos)
void Scene::Translate(float delta_X, float delta_Y)
{
    // TO DO: Proj3_scenemanip
    // Consider M - The scene node's transformation, and T the adjustment determined by the mouse
    // The variable motion is set to the current axis by CurrentManipMotion() which knows which axis is selected.
    // 1. Check which manipulation mode the program is in by calling - CurrentManipMode() which returns the mode in the front of m_modeQueue
    // 2. For LOCAL mode - transform in the object's coordinate system, M = M * T
    // 3. For PARENT mode - transform in relation to the object's parent, M = T * M
    // 4. Formulate the transform along the axis by delta related to 
    //    the product of the difference in mouse positions and a constant term
    // 5. Make your manipulator move with the mouse position. 
    //    The point you press on should remain under the mouse as it moves.
    //    Scene::DrawManipulator handles this by setting the manipulator's transform.
    //    The manipulator Scene::DrawManipulator is called during the Scene::Draw
    //    function with the current modelview matrix affecting the manipulator geometry's position.
    // 6. It is up to you how you interpret the changes in mouse position. For example you could - 
    //    Form a ray corresponding to the mouse click and 
    //    the line corresponding to the manipulation axis in world space and
    //    Compute the t intervals along the axis that correspond to the mouse movement.
    //    OR you could simply find some mapping that uses the change in the mouse positions
    //    to increment the translation in x, y and z (depending on the axis) in a smooth way.
    // 7. Make sure the private member m_trans is updated with T, the change in translation
    // 8. Make sure the private members m_translatex, m_translatey and m_translates are updated with 
    //    the scaled change in x, y, and z
    //-----------------------------------------------------------------------------------------
    
    
    // deterine the axis of translation
    ManipMotionType motion = CurrentManipMotion();
    STMatrix4 maniM = STMatrix4();

    
    int mode[3] = { 0, 0, 0 };
    if (motion == TRANS_X){
        mode[0] = 1;
        
        STMatrix4 *transNode = m_pTree->GetChildren().at(2)->GetChildren().at(0)->GetWorldT();

        if (CurrentManipMode() == LOCAL){
            maniM.table[3][0] += 0.005*delta_X;
            transNode->Multiply(maniM);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(*transNode);
        }
        else if (CurrentManipMode() == PARENT){
            maniM.table[3][0] += 0.005*delta_X;
            maniM.Multiply(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(maniM);
        }
    }
    if (motion == TRANS_Y){
        mode[1] = 1;
        STMatrix4 *transNode = m_pTree->GetChildren().at(2)->GetChildren().at(0)->GetWorldT();
        
        if (CurrentManipMode() == LOCAL){
            maniM.table[3][1] += -0.005*delta_Y;
            transNode->Multiply(maniM);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetTransform(*transNode);

        }
        else if (CurrentManipMode() == PARENT){
            maniM.table[3][1] += -0.005*delta_X;
            maniM.Multiply(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(maniM);
        }
    }
    if (motion == TRANS_Z){
        mode[2] = 1;
        STMatrix4 *transNode = m_pTree->GetChildren().at(2)->GetChildren().at(0)->GetWorldT();
        
        if (CurrentManipMode() == LOCAL){
            maniM.table[3][2] += 0.005*delta_Y;
            transNode->Multiply(maniM);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(*transNode);
            
        }
        else if (CurrentManipMode() == PARENT){
            maniM.table[3][2] += 0.005*delta_X;
            maniM.Multiply(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(maniM);
        }
    }



    // tracks the center of the translation manipulator
    // geometry for ray-hit tests
    // used for selecting the translation manipulator
    m_flagx = m_prex + mode[0] * m_translatex; 
    m_flagy = m_prey + mode[1] * m_translatey;
    m_flagz = m_prez + mode[2] * m_translatez;


    // propogate the transformation to child nodes in the tree
    PropogateTransforms(m_pTree);
    //--------------------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// Called whenever the object is rotated by dragging the rotation manipulator.
// prevMousePos - previous mouse position
// curMousePos - current mouse position
// You must implement this function.

// STVector3 raystart(m_startX, m_startY, m_startZ);
// STVector3 raysend(m_endX, m_endY, m_endZ);

// Called by:     pScene->Rotate(raystart, raysend); from main();
//----------------------------------------------------------------------------------------------
//void Scene::Rotate(STVector3 prevMousePos, STVector3 curMousePos)
void Scene::Rotate(float delta_X, float deltax_Y)

{
    //-------------------------------------------------------------------------------------
    // TO DO: Proj3_scenemanip
    // Consider M - The scene node's transformation, and T the adjustment determined by the mouse
    // The variable motion is set to the current axis by CurrentManipMotion() which knows which axis is selected.
    // 1. Check which manipulation mode the program is in by calling - CurrentManipMode() which returns the mode in the front of m_modeQueue
    // 2. For LOCAL mode - transform in the object's coordinate system, M = M * T
    // 3. For PARENT mode - transform in relation to the object's parent, M = T * M
    // 4. Formulate the transform along the axis by delta related to 
    //    the product of the difference in mouse positions and a constant term
    // 5. Make your manipulator move with the mouse position. 
    //    The point you press on should remain under the mouse as it moves.
    //    Scene::DrawManipulator handles this by setting the manipulator's transform.
    //    The manipulator Scene::DrawManipulator is called during the Scene::Draw
    //    function with the current modelview matrix affecting the manipulator geometry's position.
    // 6. It is up to you how you interpret the changes in mouse position. For example you could - 
    //    Form a ray corresponding to the mouse click and 
    //    the line corresponding to the manipulation axis in world space.
    //    and compute the t intervals along the axis that correspond to the mouse movement.
    //    OR you could simply find some mapping the uses the change in the mouse positions
    //    to increment the rotation about the axis in a reasonably smooth way.
    // 7. Make sure the private member m_rotation is updated with T, the change in rotation amount.
    //---------------------------------------------------------------------------------

    // determine the axis of rotation
    ManipMotionType motion = CurrentManipMotion();
    STMatrix4 maniM = STMatrix4();



    // a roataion about xaxis
    if (motion == ROTATE_X){
        STVector3 axisX = STVector3(1,0,0);
        STMatrix4 *transNode = m_pTree->GetChildren().at(2)->GetChildren().at(0)->GetWorldT();

        if (CurrentManipMode() == LOCAL){
            maniM.EncodeR(-1.f*deltax_Y, axisX);
            transNode->Multiply(maniM);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(*transNode);
        }
        else if (CurrentManipMode() == PARENT){
            maniM.EncodeR(-1.f*deltax_Y, axisX);
            maniM.Multiply(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(maniM);
        }
    }
    // a rotation about the Y
    if (motion == ROTATE_Y){
        STVector3 axisY = STVector3(0,1,0);
        STMatrix4 *transNode = m_pTree->GetChildren().at(2)->GetChildren().at(0)->GetWorldT();

        if (CurrentManipMode() == LOCAL){
            maniM.EncodeR(-1.f*delta_X, axisY);
            transNode->Multiply(maniM);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(*transNode);
        }
        else if (CurrentManipMode() == PARENT){
            STVector3 axis = STVector3(0,1,0);
            maniM.EncodeR(-1.f*delta_X, axisY);
            maniM.Multiply(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(maniM);
        }
    }
    if (motion == ROTATE_Z){
        STVector3 axisZ = STVector3(0,0,1);
        STMatrix4 *transNode = m_pTree->GetChildren().at(2)->GetChildren().at(0)->GetWorldT();
        
        if (CurrentManipMode() == LOCAL){
            maniM.EncodeR(-1.f*delta_X, axisZ);
            transNode->Multiply(maniM);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(*transNode);
        }
        else if (CurrentManipMode() == PARENT){
            STVector3 axis = STVector3(0,1,0);
            maniM.EncodeR(-1.f*delta_X, axisZ);
            maniM.Multiply(*transNode);
            m_pTree->GetChildren().at(2)->GetChildren().at(0)->SetWorldT(maniM);
        }
    }

    // now you need to propogate this transform in the tree
    PropogateTransforms(m_pTree);
    //--------------------------------------------------------------------------------------
}


// spins the scene
void Scene::Spin(float QMat1[4], float QMat2[4], float QMat3[4])
{
    combineQ(QMat1, QMat2, QMat3);
    glutPostRedisplay();
}


//----------------------------------------------------
// TO DO: Proj3_scenemanip
// This function needs to be implemented.
// Propogates group transformations to child nodes
//----------------------------------------------------
void Scene::PropogateTransforms(SceneNode *pNode)
{
    //--------------------------------------------------------------------------------
    // TO DO: Proj3_scenemanip
    // Re-implement this function to traverse your scene graph structure
    // This function is called by Scene::Translate and Scene::Rotate
    // Basically, it updates the transformation in each scene node everytime the object moves.
    // You will traverse the scene graph here and make sure each 
    // node has the correct world transformation (and normal transformation). It is up to you how you build 
    // your scene graph structure using the Scenenode classes provided.
    // Currently all geometry nodes are stored in m_geometryList as they are added. This is
    // very inefficient for traversal. You must take advantage of a scene graph tree structure to create
    // a recursive function that traverses a given scene tree, and propagates group 
    // transformations to child nodes. You make have to update how nodes are inserted.
    // 
    // Consider A - the Object's parent's world transform
    //          B - the Object's local transform
    // 1. Implement a recursive function that:
    // 2. for an Object that is not at the root
    //             sets m_worldT and m_worldIT within the scene node
    //             m_worldT should be set to AB 
    //             (note that if B is to move in the parent frame, the order of multiplication would be BA)
    //             m_worldIT should be set to the matrix neccessary to properly transform normal vectors
    // 3. Finally traverse the tree making a recursive call to each of the scene nodes children
    // 
    //----------------------------------------------------------------------------------
        
    /*
    ManipMotionType motion = CurrentManipMotion();
    for(int i = 0; i < (int)m_geometryList.size(); ++i) {
        STMatrix4 *worldmatrix = m_geometryList[i]->GetWorldT();
        if(IsTranslation(motion))
            worldmatrix->Multiply(m_trans);
        else if(IsRotation(motion))
            worldmatrix->Multiply(m_rotation);
    }
     */
    //---------------------------------------------------------------------------------
    //ManipMotionType motion = CurrentManipMotion();
    
    
    //GetWorldT -
    //             return the world space transformation AB
    //             where A  is the parent node's world transform
    //             and B is this object's local transform
    
    if(pNode ->GetParent() != NULL){
        STMatrix4 *worldM = pNode->GetParent()->GetWorldT();
        STMatrix4 *currentM = pNode->GetWorldT();
        
        currentM->Multiply(*worldM);
        pNode->SetWorldT(*currentM);
        
        STMatrix4 inverseWorldM = *worldM;
        inverseWorldM.inv();
        pNode->SetWorldIT(inverseWorldM);
        
        //Ending condition for recursion:
        int counter = 0;
        int numOfChildren = pNode->GetChildren().size();
        while(counter < numOfChildren){
            PropogateTransforms(pNode->GetChildren().at(counter));
            counter++; 
        }
    }
}


void Scene::SetRenderMode (RenderMode mode)
{
    m_renderMode = mode;
}


RenderMode Scene::GetRenderMode (void)
{
    return(m_renderMode);
}


void Scene::AddManipulator(void)
{
    // use the provided bopunding box to add a manipulator
    // to the scene
    // if this is true, the manipulator is drawn

    m_bHasManipulator = true;
    fprintf(stderr, "addingmanip manip!\n");
}


// True if you are rotating the manipulator
bool Scene::RotatingManip(void)
{
    if   ( (RenderMode() == NAVIGATION)
        && (HasManipulator())
        && ((CurrentManipMode() == LOCAL) || (CurrentManipMode() == PARENT))
        && ((CurrentManipGeometryState() == AXIS_ALL) || 
            (CurrentManipGeometryState() == AXIS_ROTATIONALL))
        && ((CurrentManipMotion() == ROTATE_X) || 
            (CurrentManipMotion() == ROTATE_Y) || 
            (CurrentManipMotion() == ROTATE_Z) || 
            (CurrentManipMotion() == ROTATE_SCREEN) || 
            (CurrentManipMotion() == ROTATE_DUPLICATE)))
        return(true);

    return(false);
}


// True if you are rotating the manipulator
bool Scene::TranslatingManip(void)
{
    if   ( (RenderMode() == NAVIGATION)
        && (HasManipulator())
        && ((CurrentManipMode() == LOCAL) || (CurrentManipMode() == PARENT))
        && ((CurrentManipGeometryState() == AXIS_ALL) || 
            (CurrentManipGeometryState() == AXIS_TRANSXYZ))
        && ((CurrentManipMotion() == TRANS_YZ) || 
            (CurrentManipMotion() == TRANS_XZ) || 
            (CurrentManipMotion() == TRANS_XY) || 
            (CurrentManipMotion() == TRANS_X)  || 
            (CurrentManipMotion() == TRANS_Y)  ||
            (CurrentManipMotion() == TRANS_Z)))
        return(true);

    return(false);
}


bool Scene::HasManipulator(void)
{
    return(m_bHasManipulator);
}


bool Scene::SelectManipulator(int mouseX, int mouseY, int width, int height)
{

    double matModelView[16], matProjection[16]; 
    int viewport[4]; 
    double t = 0.0;
    STVector3 closestPt;
    bool bHit = false;

    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView ); 
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection ); 
    glGetIntegerv(GL_VIEWPORT, viewport ); 
    double winX = (double)mouseX; 
    double winY = viewport[3] - (double)mouseY; 

    GLdouble   m_startX, m_startY, m_startZ;
    GLdouble   m_endX,   m_endY,   m_endZ;

    gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
                 viewport, &m_startX, &m_startY, &m_startZ); 
    gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
                 viewport, &m_endX, &m_endY, &m_endZ); 

    ManipGeom selectedGeom;
    bHit = RayTestManip(STVector3(m_startX, m_startY, m_startZ), STVector3(m_endX, m_endY, m_endZ), &selectedGeom);
    if(bHit) {
       SetActiveManipGeom(selectedGeom);
       ManipMotionType mtype = MapGeomToMotion(selectedGeom);
       SetCurrentManipMotion(mtype);
    }

    //--------------------------------------------------------

    return(bHit);
}



void Scene::RemoveManip(void)
{
    m_bHasManipulator = false;
}


// Returns true if an object was selected
// Otherwise returns false
// Uses bounding spheres of groups for intersection tests
bool Scene::SelectObject(int mouseX, int mouseY, int width, int height, STPoint3 bspherecenter, float bsphereradius)
{

    if(HasManipulator())
        return(false);

    double matModelView[16], matProjection[16]; 
    int viewport[4]; 
    double t = 0.0;
    STVector3 closestPt;
    bool bHit = false;

    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView ); 
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection ); 
    glGetIntegerv(GL_VIEWPORT, viewport ); 
    double winX = (double)mouseX; 
    double winY = viewport[3] - (double)mouseY; 

    GLdouble   m_startX, m_startY, m_startZ;
    GLdouble   m_endX,   m_endY,   m_endZ;

    gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
                 viewport, &m_startX, &m_startY, &m_startZ); 
    gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
                 viewport, &m_endX, &m_endY, &m_endZ); 

    STVector3 center(bspherecenter.x, bspherecenter.y, bspherecenter.z);

    bHit = RayTest(center, bsphereradius, center,
                   STVector3(m_startX, m_startY, m_startZ), 
                   STVector3(m_endX, m_endY, m_endZ),
                   &closestPt, &t);
	SetCurrentManipMotion(MANIP_NONE);
    return(bHit);
}

// Proj3_scenemanip - No implementation required
// this has been done for you
// maps the geometry part to the motion
//    AXIS_ROTX    - ROTATE_X                
//    AXIS_ROTY    - ROTATE_Y               
//    AXIS_ROTZ    - ROTATE_Z              
//
//   AXIS_TRANSX   - TRANS_X                
//   AXIS_TRANSY   - TRANS_Y                 
//   AXIS_TRANSX    - TRANS_Z                 
//
//   AXIS_ROTSCREEN - ROTATE_SCREEN
//   AXIS_DUPLICATE - ROTATE_DUPLICATE
ManipMotionType  Scene::MapGeomToMotion(ManipGeom selectedGeom)
{
    ManipMotionType mType;

    switch(selectedGeom) {
    case AXIS_ROTX: mType = ROTATE_X; break;
    case AXIS_ROTY: mType = ROTATE_Y; break;
    case AXIS_ROTZ: mType = ROTATE_Z; break;

        case AXIS_TRANSX: mType = TRANS_X; break;
        case AXIS_TRANSY: mType = TRANS_Y; break;
        case AXIS_TRANSZ: mType = TRANS_Z; break;

        case AXIS_DUPLICATE: mType = ROTATE_DUPLICATE; break;
        case AXIS_ROTSCREEN: mType = ROTATE_SCREEN; break;
        default:mType = MANIP_NONE; break;
    }

    return(mType);
}


// returns true if the motion type is a tranlation; otherwise false
bool Scene::IsTranslation(ManipMotionType motion)
{
    if((motion == TRANS_X) || (motion == TRANS_Y) || (motion == TRANS_Z))
        return(true);
    return(false);
}


// returns true if the motion type is a rotation; otherwise false
bool Scene::IsRotation(ManipMotionType motion)
{
    if((motion == ROTATE_X) || (motion == ROTATE_Y) || (motion == ROTATE_Z))
        return(true);
    return(false);
}


//-----------------------------------------------------------
// TO DO: Proj3_scenemanip
// No new implementation. This has been completed for you
// Checks if a ray hits a manipulator and updates the
// active geometry and manip motion type.
// This is similar to SelectObject, but this time
// checks for manipulator hits only and ignores the object
// geometry.
//--------------------------------------------------------
bool Scene::RayTestManip(STVector3 raystart, STVector3 rayend, ManipGeom *selectedGeom)
{
    double t = 0;
    STVector3 closestPt;
    bool hit = false;

    hit = RayTest(STVector3(2 + m_flagx, m_flagy, m_flagz), 0.4, STVector3(2 + m_flagx, m_flagy, m_flagz),
                 raystart, rayend,
                 &closestPt, &t);
    if ((hit) && (m_manipGeomQueue.front() == AXIS_TRANSXYZ)){
        std::cout<<"hit: AXIS_TRANSX" << std::endl;
        *selectedGeom = AXIS_TRANSX;
        return true;
    }

    hit = RayTest(STVector3(m_flagx, 2+m_flagy, m_flagz), 0.4, STVector3(m_flagx, 2+m_flagy, m_flagz),
            raystart, rayend,
            &closestPt, &t);
    if ((hit) && (m_manipGeomQueue.front() == AXIS_TRANSXYZ)){
        std::cout<<"hit: AXIS_TRANSY" << std::endl;
        *selectedGeom = AXIS_TRANSY;
        return true;
    }

    hit = RayTest(STVector3(m_flagx, m_flagy, 2 + m_flagz), 0.4, STVector3(m_flagx, m_flagy, 2 + m_flagz),
            raystart, rayend,
            &closestPt, &t);

    if ((hit) && (m_manipGeomQueue.front() == AXIS_TRANSXYZ)){
        std::cout<<"hit: AXIS_TRANSZ" << std::endl;
        *selectedGeom = AXIS_TRANSZ;
        return true;
    }

    hit = RayTest(STVector3(m_flagx, m_flagy, m_flagz), 0.5, STVector3(m_flagx, m_flagy, 2 + m_flagz),
        raystart, rayend,
        &closestPt, &t);
    if (hit)
            return false;



    if ((m_manipGeomQueue.front() == AXIS_ALL) || (m_manipGeomQueue.front() == AXIS_ROTATIONALL)) {

        float distanx = getDistance(STVector3(2 + m_flagx, m_flagy, m_flagz), raystart, rayend, &closestPt, &t);
        float distany = getDistance(STVector3(m_flagx, 2+m_flagy, m_flagz), raystart, rayend, &closestPt, &t);
        float distanz = getDistance(STVector3(m_flagx, m_flagy, 2+m_flagz), raystart, rayend, &closestPt, &t);


        if (distanx > distany && distanx > distanz)  {
            std::cout<<"hit: AXIS_ROTX" << std::endl;
            *selectedGeom = AXIS_ROTX;
            return true;
        }

        else{
                if (distany > distanz){
                std::cout<<"hit: AXIS_ROTY" << std::endl;
                *selectedGeom = AXIS_ROTY;
                return true;
            }
            else{
                std::cout<<"hit: AXIS_ROTZ" << std::endl;
                *selectedGeom = AXIS_ROTZ;
                return true;
            }
        }
    }


    return(false);
}

// returns identifier for the current manipulation mode LOCAL or PARENT or NONE
ManipMode Scene::CurrentManipMode(void)
{
    ManipMode mmanipmode = m_modeQueue.front();
    return (mmanipmode);
}

// returns identifier for the current visible manipulator geometry
ManipGeom Scene::CurrentManipGeometryState(void)
{
    ManipGeom mmanipGeomState = m_manipGeomQueue.front();
    return (mmanipGeomState);
}


// returns identifier for the current manipulation
ManipMotionType Scene::CurrentManipMotion(void)
{
    return (m_manipMotionType);
}

// gets identifier for the current manipulation
void Scene::SetCurrentManipMotion(ManipMotionType mmotiontype)
{
    m_manipMotionType = mmotiontype;
}


// returns identifier for the selected manip geometry part
ManipGeom Scene::GetActiveManipGeom(void)
{
    return (m_activeManipGeom);
}

// gets identifier for the selected manip geometry part
void Scene::SetActiveManipGeom(ManipGeom mgeom)
{
    m_activeManipGeom = mgeom;
}



//------------------------------------------------------------------------------------
// Screen space projections
//------------------------------------------------------------------------------------
// used as a scaler (in screen space) for advancing translation and rotations movements
float Scene::ScreenFactor(void)
{
    return(vpscreenfactor);
}

//-------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// Read this function and understand what it is doing.
// No further implementation is required.
// You can search the code to find references to ScreenFactor() and
// ViewProjectionScreenSpace to see how it is used.
// vpscreenfactor is always returned by the call ScreenFactor()
// This code is an example of working with matrices in the traditional OpenGL
//-------------------------------------------------------------------------
void Scene::ViewProjectionScreenSpace(STMatrix4 M)
{
    // memory for matrix data
    float modelMat_f[16];
    float projMat_f[16]; 

    // matrix data retrieved
    glGetFloatv (GL_MODELVIEW_MATRIX,  modelMat_f);  // model and view matrix combined
    glGetFloatv (GL_PROJECTION_MATRIX, projMat_f);   // projection matrix
    // place the data in a STMatrix4 class for eassy access to matrix functions
    STMatrix4 modelMat(modelMat_f);
    STMatrix4 projMat(projMat_f);

    // get the transform component of the affine transformation
    float x, y, z;
    M.GetT(&x, &y, &z);

    // compute viewport matrix
    STMatrix4 viewProjMat = modelMat * projMat;

    // transform the transformation in x, y and z by the viewport matrix
    STVector4 trans = vector4(x, y, z, 1.f);
    trans.Transform( viewProjMat );

    // use this to update the screen factor.
    // used for moving manipulator parts by small increments
    // in the manipulator draw function
    vpscreenfactor = screenScale * 0.15f * trans.w;
}




//---------------------------------------------------------------------
// Draw Geometry for manipulators
//----------------------------------------------------------------------
void Scene::DrawQuadrant(STVector3 origin, float size, bool bSelected, STVector3 axisU, STVector3 axisV)
{

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_CULL_FACE);

    STVector3 pts[4];
    pts[0] = origin;
    pts[1] = origin + (axisU * size);
    pts[2] = origin + (axisU + axisV)*size;
    pts[3] = origin + (axisV * size);

    if (!bSelected)
        glColor4f(1,1,0,0.5f);
    else
        glColor4f(1,1,1,0.6f);

    glBegin(GL_QUADS);
    glVertex3fv(&pts[0].x);
    glVertex3fv(&pts[1].x);
    glVertex3fv(&pts[2].x);
    glVertex3fv(&pts[3].x);
    glEnd();

    if (!bSelected)
        glColor4f(1,1,0.2f,1);
    else
        glColor4f(1,1,1,0.6f);

    glBegin(GL_LINE_STRIP);
    glVertex3fv(&pts[0].x);
    glVertex3fv(&pts[1].x);
    glVertex3fv(&pts[2].x);
    glVertex3fv(&pts[3].x);
    glEnd();

    glDisable(GL_BLEND);
}

void Scene::DrawCircle(STVector3 origin, RGBR_f color, STVector3 Xvert, STVector3 Yvert)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor4f(color.r, color.g, color.b, 1);
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 50 ; i++)
    {
        STVector3 vt;
        vt = Xvert * cos((2*PI/50)*i);
        vt += Yvert * sin((2*PI/50)*i);
        vt += origin;
        glVertex3f(vt.x,vt.y,vt.z);
    }
    glEnd();
}

void Scene::DrawCircleHalf(STVector3 origin, RGBR_f color, STVector3 Xvert, STVector3 Yvert, float camPlane[4])
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor4f(color.r, color.g, color.b, 1);
	glLineWidth(4.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 30 ; i++)
    {
        STVector3 vt;
        vt = Xvert  * cos((PI/30)*i);
        vt += Yvert * sin((PI/30)*i);
        vt +=origin;
        STVector3 camvec(camPlane[0],camPlane[1],camPlane[2]);
        if (camvec.Dot(camvec, vt))
            glVertex3f(vt.x,vt.y,vt.z);
    }
    glEnd();
}

void Scene::DrawAxis(STVector3 origin, RGBR_f color, STVector3 axis, STVector3 Xvert, STVector3 Yvert, float fct, float fct2, float col[4])
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor4fv(col);
    glBegin(GL_LINES);
    glVertex3fv(&origin.x);
    glVertex3f(origin.x + axis.x, origin.y + axis.y, origin.z + axis.z);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i=0;i<=30;i++)
    {
        STVector3 pt;
        pt = Xvert * cos(((2*PI)/30.0f)*i)*fct;
        pt += Yvert * sin(((2*PI)/30.0f)*i)*fct;
        pt += axis*fct2;
        pt += origin;
        glVertex3fv(&pt.x);
        pt = Xvert * cos(((2*PI)/30.0f)*(i+1))*fct;
        pt+= Yvert * sin(((2*PI)/30.0f)*(i+1))*fct;
        pt+=axis*fct2;
        pt+=origin;
        glVertex3fv(&pt.x);
        glVertex3f(origin.x + axis.x, origin.y + axis.y, origin.z + axis.z);

    }
    glEnd();

}

void Scene::DrawCam(STVector3 origin, STVector3 Xvert, STVector3 Yvert, float ng)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    int i = 0 ;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);

    glColor4f(1,1,0,0.5f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3fv(&origin.x);
    for (i = 0 ; i <= 50 ; i++)
    {
        STVector3 vt;
        vt  = Xvert * cos(((ng)/50)*i);
        vt += Yvert * sin(((ng)/50)*i);
        vt += origin;
        glVertex3f(vt.x,vt.y,vt.z);
    }
    glEnd();

    glDisable(GL_BLEND);


    glColor4f(1,1,0.2f,1);
    STVector3 vt;
    glBegin(GL_LINE_LOOP);

    glVertex3fv(&origin.x);
    for ( i = 0 ; i <= 50 ; i++)
    {
        STVector3 vt;
        vt  = Xvert * cos(((ng)/50)*i);
        vt += Yvert * sin(((ng)/50)*i);
        vt += origin;
        glVertex3f(vt.x,vt.y,vt.z);
    }

    glEnd();
}



//-----------------------------------------------------------
// Actually draw the manipulator here
//-----------------------------------------------------------
void Scene::DrawManipulator(void)
{


    // color
    RGBR_f colorRed(1, 0, 0, 1);
    RGBR_f colorGreen(0, 1, 0, 1);
    RGBR_f colorBlue(0, 0, 1, 1);
    RGBR_f colorWhite(1,1,1,1);
    RGBR_f colorMagenta(1.0f,0.3f,1.0f, 1.0f);
    RGBR_f colorGrey(0.2f,0.2f,0.2f, 1.0f);

    // a, y and z axis
    STVector3 xaxis = STVector3(1, 0, 0);
    STVector3 yaxis = STVector3(0, 1, 0);
    STVector3 zaxis = STVector3(0, 0, 1);

    // camera basis
    STVector3 up = GetCamera()->Up();
    STVector3 right = GetCamera()->Right();
    STVector3 dir = GetCamera()->Position();

    STVector3 front;
    front = front.Cross(right, xaxis);
    front.Normalize();

    // camera plane
    float colx[4] = {1, 0, 0, 1};
    float coly[4] = {0, 1, 0, 1};
    float colz[4] = {0, 0, 1, 1};
    float colall[4] = {1, 1, 1, 1};

    float fct = 0.05f;
    float fct2 = 0.83f;



    //------------------------------------------------------------------------------
    // TO DO: Proj3_scenemanip
    // Updates the matrix transformation for the manipulator geometry
    // In order to complete this code
    // 1. Make sure that the member variable STMatrix4 m_trans is updated
    //   everytime the user drags the translation manipulator. m_trans
    //   is a translation matrix that holds the "scaled" incremental change in x, y, and z.
    //   You have to come up with a smart way to map the implemental change in x, y, and z
    //   from the mouse input so that the object and manipulator move as some controllable rate.
    //   m_trans is updated in the function Scene::Translate whenever the mouse
    //   drags the translation manipulator by some small change in x and y in screen space.
    // 2.Transform the local variable xaxis, yaxis, and zaxis depending on the manipulation
    //   mode - PARENT or LOCAL
    // 3.Make any changes required to the transformations to make them work as
    //  described in the assignment.
    //------------------------------------------------------------------------------
    STMatrix4 curModelMatrix;
    curModelMatrix.EncodeS(0.5, 0.5, 0.5);
    curModelMatrix = m_trans;
    curModelMatrix.table[0][3] = curModelMatrix.table[3][0];
    curModelMatrix.table[1][3] = curModelMatrix.table[3][1];
    curModelMatrix.table[2][3] = curModelMatrix.table[3][2];

    // computes an incremental screen projection factor to
    // move the manipulator parts at a reasonable speed
    // the function ScreenFactor() returns this factor
    // which is used below.
    ViewProjectionScreenSpace(curModelMatrix);

    STVector3 origin(0,0,0);
    curModelMatrix.GetT(&origin.x, &origin.y, &origin.z);


    //-------------------------------------------------------------------------------



    // draw rotation manipulator
    //------------------------------------------------------------------
    if((CurrentManipGeometryState() == AXIS_ALL) || 
        (CurrentManipGeometryState() == AXIS_ROTATIONALL)) {


        STVector3 X_UP;
        STVector3 X_RIGHT;
        STVector3 X_FRONT;
        STVector3 X_UP_sc;
        STVector3 X_RIGHT_sc;
        STVector3 X_FRONT_sc;


        STVector3 planenorm(GetCamera()->Position() - origin);
        planenorm.Normalize();
        STVector4 camplane = vector4(planenorm,0);
        
        // duplicate
        X_RIGHT   =   right    * ScreenFactor();
        X_UP      =   up       * ScreenFactor();
        if(CurrentManipMotion() == ROTATE_DUPLICATE)
            DrawCircle(origin, colorWhite, X_RIGHT, X_UP);
        else
            DrawCircle(origin, colorGrey, X_RIGHT, X_UP);


        // screen rot
        X_UP_sc    =  up * 1.2f       * ScreenFactor();
        X_RIGHT_sc =  right * 1.2f    * ScreenFactor();
        if(CurrentManipMotion() == ROTATE_SCREEN) 
            DrawCircle(origin, colorWhite, X_UP_sc, X_RIGHT_sc);
        else 
            DrawCircle(origin, colorWhite, X_UP_sc, X_RIGHT_sc);
           // DrawCircle(origin, colorMagenta, X_UP_sc, X_RIGHT_sc);

        // x rot
        right = STVector3::Cross(STVector3(0,0,-1), xaxis);
        right.Normalize();
        front = STVector3::Cross(right, xaxis);
        front.Normalize();
        X_RIGHT   =   right    * ScreenFactor();
        X_FRONT   =   front    * ScreenFactor();
        if(CurrentManipMotion() == ROTATE_X)
            DrawCircleHalf(origin, colorWhite, X_RIGHT, X_FRONT, camplane);
        else
            DrawCircleHalf(origin, colorRed, X_RIGHT, X_FRONT, camplane);


        // y rot
        right = STVector3::Cross(STVector3(0, 0, -1), yaxis);
        right.Normalize();
        front = STVector3::Cross(right, yaxis);
        front.Normalize();
        X_RIGHT   =   right    * ScreenFactor();
        X_FRONT   =   front    * ScreenFactor();
        if(CurrentManipMotion() == ROTATE_Y)
            DrawCircleHalf(origin, colorWhite, X_RIGHT, X_FRONT, camplane);
        else
            DrawCircleHalf(origin, colorGreen, X_RIGHT, X_FRONT, camplane);


        // z rot
        right = STVector3::Cross(STVector3(0, -1, 0), zaxis);
        right.Normalize();
        front = STVector3::Cross(right, zaxis);
        front.Normalize();
        X_RIGHT   =   right    * ScreenFactor();
        X_FRONT   =   front    * ScreenFactor();
        if(CurrentManipMotion() == ROTATE_Z)
            DrawCircleHalf(origin, colorWhite, X_RIGHT, X_FRONT, camplane);
        else
            DrawCircleHalf(origin, colorBlue, X_RIGHT, X_FRONT, camplane);
    }


    // cam
    if ((CurrentManipMotion() != MANIP_NONE) && ((CurrentManipMotion() != ROTATE_DUPLICATE)))
        DrawCam(origin, gblXVert*ScreenFactor(), gblYVert *ScreenFactor(), -Ng2);




    // draw translation manupulator
    //-----------------------------------------------
 
    // Translations
    if((CurrentManipGeometryState() == AXIS_ALL) ||
        (CurrentManipGeometryState() == AXIS_TRANSXYZ)) {

        DrawQuadrant(origin, 0.5f*ScreenFactor(), (CurrentManipMotion() == TRANS_XZ), xaxis, zaxis);
        DrawQuadrant(origin, 0.5f*ScreenFactor(), (CurrentManipMotion() == TRANS_XY), xaxis, yaxis);
        DrawQuadrant(origin, 0.5f*ScreenFactor(), (CurrentManipMotion() == TRANS_YZ), yaxis, zaxis);

        xaxis *= ScreenFactor();
        yaxis *= ScreenFactor();
        zaxis *= ScreenFactor();


        if(CurrentManipMotion() == TRANS_X)
            DrawAxis(origin, colorRed, xaxis, yaxis, zaxis, fct, fct2, colall);
        else
            DrawAxis(origin, colorRed, xaxis, yaxis, zaxis, fct, fct2, colx);


        // y axis
        if(CurrentManipMotion() == TRANS_Y) 
            DrawAxis(origin, colorGreen, yaxis, xaxis, zaxis, fct, fct2, colall);
        else
            DrawAxis(origin, colorGreen, yaxis, xaxis, zaxis, fct, fct2, coly);

    
        // z axis
        if(CurrentManipMotion() == TRANS_Z) 
            DrawAxis(origin, colorBlue, zaxis, xaxis, yaxis, fct, fct2, colall);
        else
            DrawAxis(origin, colorBlue, zaxis, xaxis, yaxis, fct, fct2, colz);
    }

}


