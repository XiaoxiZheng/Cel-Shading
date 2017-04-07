//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.h
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#ifndef __SCENE_H__
#define __SCENE_H__


//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// These are new include files added to the scene class for this assignment
//------------------------------------------------------------------------------------
#include<queue>
//------------------------------------------------------------------------------------

#include "Camera.h"
#include "defs.h"
#include "Ray.h"
#include "Lists.h"
#include "RGBR_f.h"
#include "SceneNode.h"


class STTriangleMesh;
class GeometryNode;
class LightNode;
class TriangleNode;
class SurfaceNode;
class TransformNode;


class Scene
{

public:
                                Scene                                       (void);
                                ~Scene                                      (void);


    void                        SetBackgroundColor                          (RGBR_f color);
    RGBR_f                      GetBackgroundColor                          (void);

    LightNode                   *AddLight                                   (Light *lightin, SceneNode *pNode);
    SurfaceNode                 *AddSurface                                 (Surface *pSurfacein, SceneNode *pNode);
    TriangleMeshNode            *AddTriangleMesh                            (STTriangleMesh *pTrianglein, SceneNode *pNode);
    TransformNode               *AddTransform                               (STMatrix4 transformin, SceneNode *pNode);

    void                        Draw                                        (void);


    SceneNode                   *GetRoot                                    (void);

    Camera                      *GetCamera                                  (void);
    void                        GetLightPosition                            (float position[4]);


    //------------------------------------------------------------------------------------
    // TO DO: Proj3_sceneManip
    // These are all of the new members added to the scene class for this assignment
    //------------------------------------------------------------------------------------

    void                        ToggleManipMode                             (void);
    void                        ToggleManipGeometry                         (void);
    void                        ToggleRenderMode                            (void);
    void                        InitManipMode                               (void);
    void                        InitManipGeometryMode                       (void);
    RenderMode                  GetRenderMode                               (void);
    void                        SetRenderMode                               (RenderMode mode);                                  
    
    void                        Translate                                   (float delta_x, float delta_y);
    void                        Rotate                                      (float delta_x, float delta_y); 
    //void                        Translate                                   (STVector3 prevMousePos, STVector3 curMousePos);
    //void                        Rotate                                      (STVector3 prevMousePos, STVector3 curMousePos);
    void                        Spin                                        (float QMat1[4], float QMat2[4], float QMat3[4]);

    void                        PropogateTransforms                         (SceneNode *pNode);

    STVector3                   GetLightPosition                            (void);

    void                        GetBBox                                     (STPoint3 *gMassCenter, std::pair<STPoint3,STPoint3>  *gBoundingBox);

    void                        AddManipulator                              (void);
    ManipMode                   CurrentManipMode                            (void);
    ManipGeom                   CurrentManipGeometryState                   (void);
    ManipMotionType             CurrentManipMotion                          (void);
    void                        SetCurrentManipMotion                       (ManipMotionType mmotiontype);
    void                        SetActiveManipGeom                          (ManipGeom mgeom);
    ManipGeom                   GetActiveManipGeom                          (void);
    bool                        RotatingManip                               (void);
    bool                        TranslatingManip                            (void);
    bool                        HasManipulator                              (void);
    void                        RemoveManip                                 (void);


    bool                        SelectObject                                (int mouseX, int mouseY, int width, int height, STPoint3 bspherecenter, float bsphereradius);
    bool                        SelectManipulator                           (int mouseX, int mouseY, int width, int height);
    void                        DrawManipulator                             (void);
    //--------------------------------------------------------------------------------------

    SceneNode                   *m_pTree;                           // root node of the scene graph
	float                       m_flagx, m_flagy, m_flagz;          // updated by Scene::Translate 0 tracks center of manipulator for Ray hit tests for manipulator selection
	STMatrix4                   m_rotation, m_trans;                // m_rotation is a rotation matrix updated by Scene::Rotate and 
                                                                    // tracks a small change in rotation about an axis
                                                                    // m_trans is a translation matrix updated by Scene::Translate and 
                                                                    // tracks a small change in translation  along an axis

    // lights
    float ambientLight[4];
    float diffuseLight[4];
    float specularLight[4];

private:



    // lights
    Light *m_pLight;
    void                        InitLights                                  (void);       






    // camera
    Camera                      *m_pCamera;

    // lights
    LightList                   m_lights;


    // background color
    RGBR_f                     m_background;


    // clear scene
    void                        Clear               (void);



    //------------------------------------------------------------------------------------
    // TO DO: Proj3_sceneManip
    // These are all of the new members added to the scene class for this assignment
    //------------------------------------------------------------------------------------

    // Geometry List - list of geometry nodes
    GeometryList m_geometryList;

    float m_translatex, m_prex;
    float m_translatey, m_prey;
    float m_translatez, m_prez;
    float m_rotatex, m_rotatey, m_rotatez;
    

    ManipMotionType m_last;
    bool IsRotation(ManipMotionType motion);
    bool IsTranslation(ManipMotionType motion);

    bool                        RayTestManip                        (STVector3 raystart, STVector3 rayend, ManipGeom *selectedGeom);

    ManipMotionType             MapGeomToMotion                     (ManipGeom selectedGeom);

    // used for manipulator geometry drawing
    STVector3 gblXVert;
    STVector3 gblYVert;
    float Ng2; 
    float screenScale; // used to compute vpscreenfactor
    float vpscreenfactor; // used as a scaler (in screen space) for advancing translation and rotations movements
    void                    DrawQuadrant                            (STVector3 origin, float size, bool bSelected, STVector3 axisU, STVector3 axisV);
    void                    DrawCircle                              (STVector3 origin, RGBR_f color, STVector3 Xvert, STVector3 Yvert);
    void                    DrawCircleHalf                          (STVector3 origin, RGBR_f color, STVector3 Xvert, STVector3 Yvert, float camPlane[4]);
    void                    DrawAxis                                (STVector3 origin, RGBR_f color, STVector3 axis, STVector3 Xvert, STVector3 Yvert, float fct, float fct2, float col[4]);
    void                    DrawCam                                 (STVector3 origin, STVector3 Xvert, STVector3 Yvert, float ng);
    float                   VProjScreenFactor                       (void);
    float                   ScreenFactor                            (void);
    void                    ViewProjectionScreenSpace               (STMatrix4 M);


    std::queue<ManipMode>       m_modeQueue;                        // the current mode is at the top LOCAL, PARENT, NONE
    std::queue<ManipGeom>       m_manipGeomQueue;                   // the current manip geom state is at the top, which parts are visible
    ManipMotionType             m_manipMotionType;                  // stores the current motion type, the selected geometry triggers this
    ManipGeom                   m_activeManipGeom;                  // active manip geometry

    RenderMode                  m_renderMode;                       // determines how objects are rendered

    bool                        m_bHasManipulator;                  // true if there is a manipulator in the scene




    //--------------------------------------------------------------------------------------





};


#endif //__SCENE_H__



