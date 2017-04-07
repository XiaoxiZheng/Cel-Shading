//--------------------------------------------------------
// Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdexcept>
#include<map>
#include <stdlib.h>
#include <assert.h>
using namespace std;

// GLEW
#define GLEW_STATIC
#include "stglew.h"
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

 //stlib and rtlib
#include "STColor4ub.h"
#include "STImage.h"
#include "utilities.h"
#include "STVector4.h"


// forward declarations
void MouseMotionCallback(int x, int y);
void MouseCallback(int button, int state, int x, int y);
void ManipulationMode(int button, int state, int x, int y);
void KeyCallback(unsigned char key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);
void CleanUp (void);
void GenerateTeaPotModel(GLint grid, GLdouble scale);
void GenerateCubeMap(void);
void LoadCubeFace(GLenum target, char *filename, int num);
void GenerateTextureCorrdinates(void);
void SetUpEnvironmentMap(void);
void Spin (void);
void motion(int , int y);
void SpinObject(float axis[4], float p1x, float p1y, float p2x, float p2y);
void drawskybox();
unsigned int skybox[6];
void RotateObject(float delta_x, float delta_y);


//-----------------------------------
// globals
// a neccessary evil for most glut programs
//---------------------------------

//------------------------------------
// scene
// TO DO proj4_GLSLShaders
// Rendermode must remain as ENVIRONMENTMAP
// for this assignment
//------------------------------------

// lights
static float ambientLight[]  = {0.20, 0.20, 0.20, 1.0};
static float diffuseLight[]  = {1.00, 1.00, 1.00, 1.0};
static float specularLight[] = {1.00, 1.00, 1.00, 1.0};
float lightPosition[] = {10.0f, 15.0f, 10.0f, 1.0f};


//---------------------------------------------
// Shaders
// TO DO proj4_GLSLShaders
// All the shader names and
// shader programs you will need are declared here
//---------------------------------------------
std::string envmapFragmentShader;
std::string envmapVertexShader;
std::string reflectionFragmentShader;
std::string reflectionVertexShader;
std::string vertexShader;
std::string fragmentShader;
STShaderProgram *shader;
STShaderProgram *envmapshader;
STShaderProgram *reflectanceshader;


//---------------------------------------------
// All the mouse and window callbacks and variables
//---------------------------------------------
// Window size, kept for screenshots
static int gWindowSizeX = 800;
static int gWindowSizeY = 800;

// Stored mouse position for camera rotation, panning, and zoom.
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;
bool bSpin = false;
bool bMove = false;
int beginx;
int beginy;
float displayangle;
float displayaxisx;
float displayaxisy;
float displayaxisz;



//---------------------------------------------
// Textures
// TO DO proj4_GLSLShaders
// All textures declared here
//---------------------------------------------
// Cube map textures
static GLenum CubeFaceTarget[6] = {
  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};


//---------------------------------------------
// Textures
// TO DO proj4_GLSLShaders
// You have been given files in ../../data/images/stpeters
// You must initialize this variable with the texture files in the correct order.
// The names of the files are associated with their relation to the x, y and z planes.
// for example the first entry would be  char *cmapFiles[6] = { "../../data/images/stpeters/negx.jpg",
// To load other cubemaps, replace these mages with your own cubemap files in the correct order
// It is optional and not required to test other cube maps
//------------------------------------------------------------------------------------
char *cmapFiles[6];


//------------------------------------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// Loads a single cube face and is called 6 times by GenerateCubeMap for each face
// Complete this function
// Implement the following in order
// 1. generate a texture and bind it to the proper texture target before we 
//  use the texture id TEXTURE0 - use the functions glActiveTexture, glGenTextures and glBindTexture
// 2. load the file in an STImage and extract its pixels to a const STColor4ub* 
// 3. finally call gluBuild2DMipmaps to build the texture mipmap
//------------------------------------------------------------------------------------
void LoadCubeFace(GLenum target, char *filename,unsigned int num)
{
}


//------------------------------------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// This function has been implemented for you. It generates texture coordinates (S, T, R), glTexGeni function.
//------------------------------------------------------------------------------------
void GenerateTextureCoordinates(void)
{
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
}


//------------------------------------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// This function has been implemented for you. It sets up the texture wrap flags
//------------------------------------------------------------------------------------
void SetTextureWrapFlags(void)
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}



//------------------------------------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// This function has been implemented for you. It draws the skybox.
//------------------------------------------------------------------------------------
void drawskybox(){
        GLfloat fExtent = 10.f;
        glEnable(GL_AUTO_NORMAL);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_GEN_R);

        
        glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, skybox[0]);
        glBegin(GL_QUADS);

        glVertex3f(-fExtent, -fExtent, fExtent);
        glVertex3f(-fExtent, fExtent, fExtent);
        glVertex3f(-fExtent, fExtent, -fExtent);
        glVertex3f(-fExtent, -fExtent, -fExtent);

        glEnd();

        glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, skybox[1]);
        glBegin(GL_QUADS);

        glVertex3f(fExtent, -fExtent, -fExtent);
        glVertex3f(fExtent, -fExtent, fExtent);
        glVertex3f(fExtent, fExtent, fExtent);
        glVertex3f(fExtent, fExtent, -fExtent);

        glEnd();

        glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, skybox[2]);
        glBegin(GL_QUADS);

        glVertex3f(-fExtent, fExtent, fExtent);
        glVertex3f(-fExtent, fExtent, -fExtent);
        glVertex3f(fExtent, fExtent, -fExtent);
        glVertex3f(fExtent, fExtent, fExtent);

        glEnd();

        glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, skybox[2]);
        glBegin(GL_QUADS);

        glVertex3f(-fExtent, -fExtent, -fExtent);
        glVertex3f(-fExtent, -fExtent, fExtent);
        glVertex3f(fExtent, -fExtent, fExtent);
        glVertex3f(fExtent, -fExtent, -fExtent);

        glEnd();

        glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, skybox[4]);
        glBegin(GL_QUADS);

        glVertex3f(fExtent, -fExtent, fExtent);
        glVertex3f(-fExtent, -fExtent, fExtent);
        glVertex3f(-fExtent, fExtent, fExtent);
        glVertex3f(fExtent, fExtent, fExtent);

        glEnd();

        glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, skybox[5]);

        glBegin(GL_QUADS);
        glVertex3f(fExtent, -fExtent, -fExtent);
        glVertex3f(-fExtent, -fExtent, -fExtent);
        glVertex3f(-fExtent, fExtent, -fExtent);
        glVertex3f(fExtent, fExtent, -fExtent);

        glEnd();
        
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_TEXTURE_GEN_R);
        glEnable(GL_DEPTH_TEST);
}


//------------------------------------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// Generates the cube map. Complete this function which generates a cubemap.
//------------------------------------------------------------------------------------
void GenerateCubeMap(void)
{
    //----------------------------------------------------------------------
    // TO DO: Proj4_GLSLShaders
    // In order to achieve this task, you will have to do the following in order...
    // 1. For each of the six faces of the cube, call LoadCubeFace(GLenum target, char *filename,unsigned int num)
    // 2. Set texture parameters for interpolation using mipmaps.
    //     You will have to call make two calls to the function 
    //     void glTexParameteri( GLenum target,  GLenum pname,  GLint param);
    //     use the parameters GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR
    //                        GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    // 3. Now enable the texture - remember your texture type is a GL_TEXTURE_CUBE_MAP
    // 4. Call the functionGenerateTextureCoordinates() to set the texture coordinates
    // 5. Call the function SetTextureWrapFlags() to set the parameters for how to warp the texture

    //--------------------------------------------------------------------

    //-------------------------------------------------------------------------

    // enable the texture coordinates that will be used
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    // set the matrix mode
    glMatrixMode(GL_TEXTURE);
    glScalef(-1,-1,-1);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();

}


//------------------------------------------------------------
// Builds the Nvidia Teapot  model
//-------------------------------------------------------------
void GenerateTeaPotModel(GLint grid, GLdouble scale)
{
  float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
  long i, j, k, l;

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_MAP2_VERTEX_3);
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);
  glTranslatef(0.0, 0.0, -1.5);
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 4; k++) {
        for (l = 0; l < 3; l++) {
          p[j][k][l] = geomData_teapot[geom_teapot[i][j * 4 + k]][l];
          q[j][k][l] = geomData_teapot[geom_teapot[i][j * 4 + (3 - k)]][l];
          if (l == 1)
            q[j][k][l] *= -1.0;
          if (i < 6) {
            r[j][k][l] =
              geomData_teapot[geom_teapot[i][j * 4 + (3 - k)]][l];
            if (l == 0)
              r[j][k][l] *= -1.0;
            s[j][k][l] = geomData_teapot[geom_teapot[i][j * 4 + k]][l];
            if (l == 0)
              s[j][k][l] *= -1.0;
            if (l == 1)
              s[j][k][l] *= -1.0;
          }
        }
      }
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &p[0][0][0]);
    glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &q[0][0][0]);
    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    if (i < 6) {
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &r[0][0][0]);
      glEvalMesh2(GL_FILL, 0, grid, 0, grid);
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &s[0][0][0]);
      glEvalMesh2(GL_FILL, 0, grid, 0, grid);
    }
  }
}



//-------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// You will have to complete this function by
// intializing the shaders and calling a function to 
// generate the cubemap
//------------------------------------------------------
void SetUpEnvironmentMap(void)
{

    // load camera projection matrix and model matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set the perspective view
    gluPerspective( 35.0,  1.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set the camera position
    // eye is at (0,0,8)
    // center is at (0,0,0)
    // up is in positive Y direction 
    gluLookAt(0.0, 0.0, 15.0, 
              0.0, 0.0, 0.0,          
              0.0, 1.0, 0.);          

    // enable depth testing
    glEnable(GL_DEPTH_TEST);


    //----------------------------------------------------
    // TO DO: Proj4_GLSLShaders
    // Follow the instructions in the assignment 
    // First - implemet your shaders in the shader files in the kernels directory
    // envmap.vert, envmap.frag, reflectance.vert, reflectance.frag
    // These are vertex and fragment shaders.
    // Now to complete this function
    // 1.Call GenerateCubeMap() to build the cubemap texture
    // 2. Allocate memory for the shaders (the shaders are of type STShaderProgram)
    // 3. Load the shader files - the file names are declared at the top of this file
    // To load shaders, use the function LoadVertexShader found in the STShaderProgram class.
    //---------------------------------------------------
    //----------------------------------------

    //GenerateCubeMap();
    envmapshader = new STShaderProgram();
    envmapshader->LoadVertexShader(envmapVertexShader);

    std::cout << "Print" << std::endl;

    envmapshader->LoadFragmentShader(envmapFragmentShader);

}



//----------------------------------------------------------------
// TO DO: Proj4_GLSLShaders
// This function has been implemented for you.
// It Initializes the application, loading all of the settings that
// we will be accessing later in our fragment shaders.
//----------------------------------------------------------------
void Setup()
{
    // reset everything
    //-----------------------------------------------
    glDisable (GL_TEXTURE_CUBE_MAP);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    if(shader)
        delete(shader);
    if(envmapshader)
        delete(envmapshader);
    if(reflectanceshader)
        delete(reflectanceshader);
    shader = NULL;
    envmapshader = NULL;
    reflectanceshader = NULL;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    // this is the function that sets up the environment map
    SetUpEnvironmentMap();

}

//----------------------------------------------------
// TO DO: Pro4_GLSLShaders
// clean up variables
//----------------------------------------------------
void CleanUp()
{
}



//--------------------------------------------------
// TO DO: Proj4_GLSLShaders
// Called everytime the display is rendered.
// Complete this function
//--------------------------------------------------
void ReflectanceMapping(void)
{

    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //--------------------------------------------------
    // TO DO: Proj4_GLSLShaders
    // Remove this code
    // This is just here so that you see a teapot
    // It is not needed for environmapping and needs
    // to be removed for enviorment mapping to work
    //---------------------------------------------------
    gluPerspective( 35.0,  1.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 15.0, 
              0.0, 0.0, 0.0,          
              0.0, 1.0, 0.);          
    //--------------------------------------------------


    //--------------------------------------------------
    // TO DO: Proj4_GLSLShaders
    // This function displays the environment mapped object.
    // To complete this function, add code that will ...
    // 1. bind the reflectanceshader shader and the envmapshader
    // 2. draw the skybox - drawskybox()
    // bind shaders and draw sky box here before the draw code below
    // ----------------------------------------------------------
        envmapshader->Bind();
    //-----------------------------------------------------------


    // this code draws the object - a teapot
    // Sets up the opengl matrix stack
    // and draws the model.
    // If the left mouse button is down: displayangle, displayaxisx, displayaxisy, displayaxisz
    // specify the rotation angle and axis for spinning the model
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.5); // move to position
    glRotatef(displayangle, displayaxisx, displayaxisy, displayaxisz); //  rotate around center
    glTranslatef(0.0, 0.0, 1.5); //move object to center
    GenerateTeaPotModel(5, 1.1);  // draw the teapot model
    glPopMatrix();

    //--------------------------------------------------
    // TO DO: Proj4_GLSLShaders
    // 3. you must determine the correct order to bind and unbind
    //   your shaders and textures.
    //----------------------------------------------------------

    //----------------------------------------------------------

    // done with front frame buffer so swap to 
    // the back frame buffer that was rendering 
    // in the background
    glutSwapBuffers();
}


//--------------------------------------------------
// Display the output image from our vertex and fragment shaders
//--------------------------------------------------
void DisplayCallback()
{
    ReflectanceMapping();
}

//--------------------------------------------------
// Reshape the window and record the size so
// that we can use it for screenshots.
// Note that if you resize the window and the aspect ratio
// is no longer 1:1, your object will be distorted on the screen
//----------------------------------------------------
void ReshapeCallback(int w, int h)
{
    gWindowSizeX = w;
    gWindowSizeY = h;

    if(gWindowSizeX < gWindowSizeY)
        gWindowSizeX = gWindowSizeY;
    if(gWindowSizeY < gWindowSizeX)
        gWindowSizeY = gWindowSizeX;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

}

//-------------------------------------------------
// Processes key press events
//-------------------------------------------------
void KeyCallback(unsigned char key, int x, int y)
{

    switch(key) {
   

        case 's': {
                //
                // Take a screenshot, and save as screenshot.jpg
                //
                STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
                screenshot->Read(0,0);
                screenshot->Save("../../data/images/screenshot.jpg");
                delete screenshot;
         }
        break;

        case 't': {
        }
        break;

        case 'q': {
            exit(0);
        }



        default:
            break;
    }

    glutPostRedisplay();
}


//-------------------------------------------------
// sets the move flag true based on mouse position
// and state
//-------------------------------------------------
void ManipulationMode(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    bSpin = false;
    glutIdleFunc(NULL);
    bMove = true;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    bMove = false;
  }
}


//-------------------------------------------------
// Mouse event handler
// sets the move flag true based on mouse position
// and state
//-------------------------------------------------
void MouseCallback(int button, int state, int x, int y)
{
    ManipulationMode(button, state, x, y);  
}


//-------------------------------------------------
// Mouse active motion callback (when button is pressed)
//-------------------------------------------------
void MouseMotionCallback(int x, int y)
{
    motion(x, y);
}


//-------------------------------------------------
// Spin object
//-------------------------------------------------

// spin
void Spin (void)
{
    glutPostRedisplay();
}

void SpinObject(float p1x, float p1y, float p2x, float p2y)
{
    float delta_x = p2x - p1x;
    float delta_y = p2y - p1y;

    delta_x = delta_x/100;
    delta_y = delta_y/100;


    displayangle = atan2(delta_y,delta_x) * 180 / 3.141;

    displayaxisx = 0;
    displayaxisy = 0;
    displayaxisz = 0;
    if(delta_x > delta_y)
        displayaxisy = 1;
    if(delta_y > delta_x)
        displayaxisx = 1;

}


void motion(int x, int y)
{
    if (bMove) {

        SpinObject((2.0 * beginx - gWindowSizeX) / gWindowSizeX,
        (gWindowSizeY - 2.0 * beginy) / gWindowSizeY,
        (2.0 * x - gWindowSizeX) / gWindowSizeX,
        (gWindowSizeY - 2.0 * y) / gWindowSizeY);

        beginx = x;
        beginy = y;
        bSpin = true;
        glutIdleFunc(Spin);
    }
}


//-------------------------------------------------
// user feedback on input args
//-------------------------------------------------
void usage()
{
}


//-------------------------------------------------
// main program loop
//-------------------------------------------------
int main(int argc, char** argv)
{
    //------------------------------------------------------------------------------------
    // TO DO: Proj4_GLSLShaders
    // Shader files are specified here
    // No additional implementation required
    //------------------------------------------------------------------------------------
    envmapFragmentShader            = std::string("kernels/envmap.frag");
    envmapVertexShader              = std::string("kernels/envmap.vert");
    reflectionFragmentShader        = std::string("kernels/reflectance.frag");
    reflectionVertexShader          = std::string("kernels/reflectance.vert");
    vertexShader                    = std::string("kernels/default.vert");
    fragmentShader                  = std::string("kernels/phong.frag");


    // TO DO: proj4_GLSLShaders
    // Initialize GLUT.
    // Note that if you resize the window and the aspect ratio
    // is no longer 1:1, your object will be distorted on the screen
    glutInitWindowSize(800, 800);
    glutInit(&argc, argv);


    // initialize display mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Program 4 GLSL Shaders");


    // Initialize GLUT and GLEW before
    // initializing your application.
#ifndef __APPLE__
    glewInit();
    if(!GLEW_VERSION_2_0) {
        printf("Your graphics card or graphics driver does\n"
            "\tnot support OpenGL 2.0, trying ARB extensions\n");

        if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
            printf("ARB extensions don't work either.\n");
            printf("\tYou can try updating your graphics drivers.\n"
                "\tIf that does not work, you will have to find\n");
            printf("\ta machine with a newer graphics card.\n");
            exit(1);
        }
    }
#endif

    // callback functions
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutKeyboardFunc(KeyCallback);
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotionCallback);
    glutIdleFunc(DisplayCallback);


    // set  the scene
    Setup();
    
    // init display axes
    displayaxisx = 0;
    displayaxisy = 0;
    displayaxisz = 0;

    // run the main glut loop
    glutMainLoop();
  
  
    // Cleanup code should be called here.
    CleanUp();

    // return
    return 0;
}


