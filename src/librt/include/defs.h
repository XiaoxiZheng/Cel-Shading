//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Defs.h
// Global Definitions
//------------------------------------------------------------------------------


#ifndef __DEFS_H__
#define __DEFS_H__

#include <vector>
#include "Light.h"
#include "Intersection.h"


//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// New definitions
// No implementation required
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// Manipulator modes 
// determines whether translations happen locally
// or in the parent coordinate system
// or if no manipulations at all
// No further implementation required
//--------------------------------------------------------------------------------------
typedef enum {
    NONE       = 0, // no manipulators
    LOCAL      = 1, // manipulators local transforms
    PARENT     = 2  // manupulators parent coordinate transforms

}ManipMode;


// Camera modes 
// determines whether rotations  focus around and object (orbit)
// or the camera view (fly)
typedef enum {
    FLY        = 0, 
    ORBIT      = 1
}CameraRotationMode;


// Manipulation modes 
// Specifies the type of manipulation
typedef enum {
    TRANS_YZ                = 0, 
    TRANS_XZ                = 1, 
    TRANS_XY                = 2, 
    TRANS_XYZ               = 3, 
    TRANS_X                 = 4, 
    TRANS_Y                 = 5, 
    TRANS_Z                 = 6,
    ROTATE_X                = 7,
    ROTATE_Y                = 8,
    ROTATE_Z                = 9,
    ROTATE_SCREEN           = 10,
    ROTATE_DUPLICATE        = 11,
    MANIP_NONE              = 12
}ManipMotionType;

// Manipulator geometry parts
// hides parts of the manipulator to make
// it easier to select parts of the geometry
// also used to determine which part of the 
// manipulator is selected
typedef enum {
    AXIS_ALL                    = 0, 
    AXIS_TRANSXYZ               = 1,
    AXIS_TRANSX                 = 2,
    AXIS_TRANSY                 = 3,
    AXIS_TRANSZ                 = 4,
    AXIS_ROTX                   = 5,
    AXIS_ROTY                   = 6,
    AXIS_ROTZ                   = 7,
    AXIS_ROTTRACKBALL           = 8,
    AXIS_ROTSCREEN              = 9,
    AXIS_ROTATIONALL            = 10,
    AXIS_DUPLICATE              = 11, 
    AXIS_NONE                   = 12
}ManipGeom;


//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO:Proj3_scenemanip
// Added NAVIGATIONMODE
// No implementation required
// render modes 
//---------------------------------------------------------------------------------------



// determines the type of image created
typedef enum {
    LAMBERTIAN      = 0,
    PHONG           = 1,
    MIRROR          = 2,
    ENVIRONMENTMAP  = 3,
    EFFECT_1        = 4,
    EFFECT_2        = 5,
    EFFECT_3        = 6,
    NAVIGATION
}RenderMode;


//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// New definitions
// No implementation required
//------------------------------------------------------------------------------------

// constants use for the manipulator
#define RENORMCOUNT 97         
#define TRACKBALLSIZE 0.8f;
const float PI    =  3.14159265358979323846f;

// TEXT_texture_cube_map support
//--------------------------------------------------------------
#ifndef GL_EXT_texture_lod_bias
# define GL_MAX_TEXTURE_LOD_BIAS         0x84fd
# define GL_TEXTURE_FILTER_CONTROL       0x8500
# define GL_TEXTURE_LOD_BIAS             0x8501
#endif

#ifndef GL_EXT_texture_cube_map
# define GL_NORMAL_MAP                          0x8511
# define GL_REFLECTION_MAP                      0x8512
# define GL_TEXTURE_CUBE_MAP                    0x8513
# define GL_TEXTURE_BINDING_CUBE_MAP            0x8514
# define GL_TEXTURE_CUBE_MAP_POSITIVE_X         0x8515
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_X         0x8516
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Y         0x8517
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y         0x8518
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Z         0x8519
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z         0x851A
# define GL_PROXY_TEXTURE_CUBE_MAP              0x851B
# define GL_MAX_CUBE_MAP_TEXTURE_SIZE           0x851C
#endif





// 1. Add any constant parameters that may be useful for your
//    special effect. Some examples are added below.
//------------------------------------------------
//------------------------------------------------
const double EPSILON = 1.0e-6; 
const double REFRACT_INDEX_VACUUM           = 1.0000;
const double REFRACT_INDEX_AIR              = 1.0003;
const double REFRACT_INDEX_WATER            = 1.3330;
const double REFRACT_INDEX_GLASS            = 1.5500;
const double REFRACT_INDEX_MIN              = 1.0000;
const double REFRACT_INDEX_MAX              = 9.0000;


#endif //__DEFS_H__


