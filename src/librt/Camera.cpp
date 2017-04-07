//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.cpp
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#include "Camera.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "STMatrix4.h"
#include "utilities.h"
#include "defs.h"

// GLEW
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


 //---------------------------------------------------------   
// TO DO: Proj3_scenemanipip
//-----------------------------------
// Camera implementation
// to support the camera rotation and translation modes
// Make sure that the camera parameters are correct so that
// when we create our viewing and projection matrices
// in main.cpp the camera orientaiton and view frustrum is correct.
//-----------------------------------


// construct the camera
Camera::Camera(void)
{
    Reset();
    m_rotationMode = ORBIT;
    m_anglex = 0;
    m_angley = 0;
    m_yaw = 0;
    m_pitch = 0;
}


Camera::~Camera()
{

}



// reset the camera basis so camera is up right
void Camera::SetUpAndRight(void)
{

    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}

// reset the camera position to (0,0,0) looking down negative z
void Camera::Reset(void) 
{
    m_LookAt=STVector3(0.f,0.f,0.f);
    m_Position=STVector3(0.f,0.f,0.f);
    m_Up=STVector3(0.f,1.f,0.f);

    SetUpAndRight();
}



// resets the camera up vector
void Camera::ResetUp(void)
{
    m_Up = STVector3(0.f,1.f,0.f);
    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}


//----------------------------------------------------------------
// TO DO: Proj3_sceneManip
// Complete the functions:
// RotateFly(float delta_x, float delta_y) and RotateOrbit(float delta_x, float delta_y)
// They are called from this function. This function is complete.
// axis - axis of rotation 
// p1x, p1y - coordinates of mouse START position in screen coords
// p2x, p2y - coordinates of mouse END position in screen coords
//------------------------------------------------------------------------
void Camera::Orbit(float axis[4], float p1x, float p1y, float p2x, float p2y)
{
    // compute the change in x and y
    float delta_x = p2x - p1x;
    float delta_y = p2y - p1y;

    // rotate fly
    if (m_rotationMode != ORBIT){
        RotateFly(delta_x, delta_y);
        return;
    }

    // rotate orbit
    RotateOrbit(delta_x, delta_y);

}


//-------------------------------------------------------
// TO DO: Proj3_scenemanip
// Orbit - rotates about an object
// This is a analogous to a virtual trackball 
// Implement ORBIT here - ORBIT - rotates the camera with the camer look at vector
// fixed on the center of the object
// input  - float delta_x, float delta_y change in x and y in screen coords
// create the rotation matrix and use it to update the following members:
// m_LookAt - look at
// m_yaw - tracks a small incremental sway right to left - rotation around yqxis
// m_pitch -  pitch angle -  tracks a small incremental tip up and down around xaxis
// m_Position - camera position
//-----------------------------------------------------
void Camera::RotateOrbit(float delta_x, float delta_y)
{
    //To change the speeds easily
    m_yaw=1.f;
    m_pitch=1.f;
    
    //Move the cam pos to the look at
    m_Position -= m_LookAt;

    STMatrix4 m;

    //Rotate around the up axis based on the vertical mouse movement
    m.EncodeR(-1*delta_x*m_yaw, m_Up);
    m_Position = m * m_Position;

    //Rotate around the right axis base on the horizontal mouse movement
    m.EncodeR(-1*delta_y*m_pitch, m_Right);
    m_Position = m * m_Position;

    //Move the cam back to where it should be
    m_Position += m_LookAt;

    //Reset these
    m_anglex = 0;
    m_angley = 0;
}


//-----------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// Implement FLY here - FLY - rotates around a viewpoint
// input  - float delta_x, float delta_y change in x and y in screen coords
//-----------------------------------------------------------------------
void Camera::RotateFly(float delta_x, float delta_y)
{
    //-------------------------------------------------------------------------------
    // TO DO: Proj3_scenemanip
    // 1. Alter this code so that there are two camera rotation options
    // 3. All rotations are about the origin in world space
    // 4. Compute the coordinates of the world origin in camera space
    // 5. Contruct your rotation about this computed point, use the matrix to
    // 6. update the member variables:
    //    - m_anglex - tracks the latest small increment in the x angle for the mouse moves
    //    - m_angley - tracks the latest small increment in the y angle for the mouse moves
    //    - m_LookAt - look at vector
    //-------------------------------------------------------------------------------

    //Used to change the speed of movement
    m_yaw=0.02f;
    m_pitch=0.02f;
    
    //Move the lookAt Pos to the camera
    m_LookAt -= m_Position;

    //Rotate the camera around the up based on horizontal mouse movement
    STMatrix4 m;
    m.EncodeR(1*delta_x*m_yaw, m_Up);
    m_Position = m * m_Position;

    //Rotate the camera around the right axis based on the vertical mouse movement
    m.EncodeR(1*delta_y*m_pitch, m_Right);
    m_Position = m * m_Position;

    //Push the lookAt back out into world space
    m_LookAt += m_Position;

    //-------------------------------------------------------------------------------
}


void Camera::Zoom(float delta_y)
{
    STVector3 diff = m_LookAt - m_Position;
    STVector3 direction = m_LookAt - m_Position;
    float magnitude = direction.Length();
    direction.Normalize();
    float zoom_rate = 0.1f*magnitude < 0.5f ? .1f*magnitude : .5f;
    if(delta_y * zoom_rate + magnitude > 0)
    {
        m_Position = m_LookAt - diff + (delta_y * zoom_rate) * direction;
    }
}


//-----------------------------------------------------------
// TO DO: Proj3_scenemanip
// change the camera parameters for trnaslating the camera (Strafe)
// input  - float delta_x, float delta_y change in x and y in screen coords
// The members - m_Position and = m_LookAt need to be updated
//-------------------------------------------------------------
void Camera::Strafe(float delta_x, float delta_y)
{
    float strafe_rate = 0.05f;
    
    m_Position -= strafe_rate * delta_x * m_Right;
    m_LookAt   -= strafe_rate * delta_x * m_Right;
    m_Position += strafe_rate * delta_y * m_Up;
    m_LookAt   += strafe_rate * delta_y * m_Up;
}


STVector3 Camera::Position (void)
{
    return(m_Position);
}


STVector3 Camera::LookAt (void)
{

    return(m_LookAt);
}


STVector3 Camera::Up (void)
{
    return(m_Up);
}

//------------------------------------------------------------------------------------
// TO DO: Proj3_sceneManip
// These are all of the new members added to the Camera class for this assignment
//------------------------------------------------------------------------------------

// returns right vector
STVector3 Camera::Right (void)
{
    return(m_Right);
}


// toggles the  rotation modes -  orbit and fly
void Camera::ToggleRotationMode (void)
{
    if(m_rotationMode == ORBIT) {
        m_rotationMode = FLY;
        fprintf(stderr, "FLY\n");
    }
    else if(m_rotationMode == FLY) {
        m_rotationMode = ORBIT;
        fprintf(stderr, "ORBIT\n");
    }
}


// sets the look at vector
void Camera::SetLookAt(STVector3 lookat)
{
    m_LookAt = lookat;
}

// sets the eye point position
void Camera::SetPosition(STVector3 position)
{
    m_Position = position;
}

// sets the up vector
void Camera::SetUp(STVector3 up)
{
    m_Up = up;
}


//-----------------------------------------------------------------------------------------
