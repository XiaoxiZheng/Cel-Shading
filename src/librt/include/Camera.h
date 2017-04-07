//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.h
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "STVector3.h"
#include "STMatrix4.h"

class Camera
{

public:
                            Camera(void);
                            ~Camera(void);

    void                    Reset                                       (void);
    void                    ResetUp                                     (void);
    void                    SetUpAndRight                               (void);


    STVector3               Position                                    (void);
    STVector3               LookAt                                      (void);
    STVector3               Up                                          (void);

    //------------------------------------------------------------------------------------
    // TO DO: Proj3_scenemanip
    // These are all of the new members added to the Camera class for this assignment
    //------------------------------------------------------------------------------------
    STVector3               Right                                       (void);

    void                    ToggleRotationMode                          (void);

    void                    Strafe                                      (float delta_x, float delta_y);
    void                    Zoom                                        (float delta_y);
    void                    RotateFly                                   (float delta_x, float delta_y);
    void                    RotateOrbit                                 (float delta_x, float delta_y);
    void                    Orbit                                       (float q[4], float p1x, float p1y, float p2x, float p2y);

  
    void                    SetLookAt                                   (STVector3 lookat);
    void                    SetPosition                                 (STVector3 position);
    void                    SetUp                                       (STVector3 up);
    //------------------------------------------------------------------------------------


private:

    // parameters
    STVector3               m_Position;
    STVector3               m_LookAt;
    STVector3               m_Right;
    STVector3               m_Up;

    //------------------------------------------------------------------------------------
    // TO DO: Proj3_scenemanip
    // These are all of the new members added to the Camera class for this assignment
    //------------------------------------------------------------------------------------
    float                   m_anglex;           // tracks small increments in x direction controlled by deltax mouse positions
    float                   m_angley;           // tracks small increments in y direction controlled by deltay mouse positions
    bool                    m_rotationMode;     // ORBIT or FLY mode
    float                   m_yaw;              // sway right to left - rotation around y
    float                   m_pitch;            //  pitch angle - tip up and down around x
    //---------------------------------------------------------------------------------


};


#endif //__CAMERA_H__

