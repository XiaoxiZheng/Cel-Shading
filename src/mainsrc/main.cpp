//--------------------------------------------------------
// Computer Graphics
// University of Florida
// Final Project - Interactive Cel Shading
// by   Nicola Frachesen
//      Guilain Huyghues-Despointes
//      Natalie Rumak
//      Xiaoxi Zheng
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdexcept>
#include <map>
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
void KeyCallback(unsigned char key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);
void SetUpShaders(void);



//Shaders
std::string ToonFragmentShader;
std::string ToonVertexShader;
STShaderProgram *toonshader;

//The Amount of quantization
int ToonMode = 2;

// Window size, kept for screenshots
static int gWindowSizeX = 800;
static int gWindowSizeY = 800;

// Stored mouse position for camera rotation, panning, and zoom.
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

//Camera Vectors
STVector3 mPosition;
STVector3 mLookAt;
STVector3 mRight;
STVector3 mUp;

//Information on the given model.
std::string meshOBJ;
std::vector<STTriangleMesh*> myModel;
std::pair<STPoint3,STPoint3> boundingBox;
STPoint3 massCenter;

//Camera Methods
void SetUpAndRight()
{
    mRight = STVector3::Cross(mLookAt - mPosition, mUp);
    mRight.Normalize();
    mUp = STVector3::Cross(mRight, mLookAt - mPosition);
    mUp.Normalize();
}

void resetCamera()
{
    mLookAt=STVector3(0.f,0.f,0.f);
    mPosition=STVector3(0.f,5.f,15.f);
    mUp=STVector3(0.f,1.f,0.f);

    SetUpAndRight();
}

void resetUp()
{
    mUp = STVector3(0.f,1.f,0.f);
    mRight = STVector3::Cross(mLookAt - mPosition, mUp);
    mRight.Normalize();
    mUp = STVector3::Cross(mRight, mLookAt - mPosition);
    mUp.Normalize();
}

void RotateCamera(float delta_x, float delta_y)
{
    float yaw_rate=1.f;
    float pitch_rate=1.f;

    mPosition -= mLookAt;
    STMatrix4 m;
    m.EncodeR(-1*delta_x*yaw_rate, mUp);
    mPosition = m * mPosition;
    m.EncodeR(-1*delta_y*pitch_rate, mRight);
    mPosition = m * mPosition;

    mPosition += mLookAt;
}

void ZoomCamera(float delta_y)
{
    STVector3 direction = mLookAt - mPosition;
    float magnitude = direction.Length();
    direction.Normalize();
    float zoom_rate = 0.1f*magnitude < 0.5f ? .1f*magnitude : .5f;
    if(delta_y * zoom_rate + magnitude > 0)
    {
        mPosition += (delta_y * zoom_rate) * direction;
    }
}

void StrafeCamera(float delta_x, float delta_y)
{
    float strafe_rate = 0.05f;
    
    mPosition -= strafe_rate * delta_x * mRight;
    mLookAt   -= strafe_rate * delta_x * mRight;
    mPosition += strafe_rate * delta_y * mUp;
    mLookAt   += strafe_rate * delta_y * mUp;
}

//Sets up the shaders
void SetUpShaders(void)
{

    // load camera projection matrix and model matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set the perspective view
    gluPerspective( 35.0,  1.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    //Load the shaders.
    toonshader = new STShaderProgram();
    toonshader->LoadVertexShader(ToonVertexShader);
    toonshader->LoadFragmentShader(ToonFragmentShader);
   

}


//The primary setup.
void Setup()
{
    //Reset everything in the scene
    myModel.clear();
    if(toonshader)
        delete(toonshader);
    toonshader = NULL;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    resetCamera();


    //Sets up the shaders
    SetUpShaders();

    //Load the object and get its center of mass and bounding box.
    STTriangleMesh::LoadObj(myModel,meshOBJ);
    massCenter=STTriangleMesh::GetMassCenter(myModel);
    boundingBox=STTriangleMesh::GetBoundingBox(myModel);

}

//Draws the model with the appropriate shader binding.
void drawModel(void)
{

    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Bind the shader
    toonshader->Bind();

    //Opengl matrix setup.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Make the model always scale to the same size, and place it in the center.
    STVector3 boundingSize=boundingBox.second-boundingBox.first;
    float maxSize=(std::max)((std::max)(boundingSize.x,boundingSize.y),boundingSize.z);
    glScalef(4.0f/maxSize,4.0f/maxSize,4.0f/maxSize);
    glTranslatef(-massCenter.x,-massCenter.y,-massCenter.z);

    //Draw any model(s).
    for (int i = 0; i < myModel.size(); i++){
        myModel[i]->Draw(true);
    }
    glPopMatrix();

    //Unbind the shader.
    toonshader->UnBind();

    //Change opengl buffers.
    glutSwapBuffers();
}


// Display the output image
void DisplayCallback()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    SetUpAndRight();

    gluLookAt(mPosition.x,mPosition.y,mPosition.z,
              mLookAt.x,mLookAt.y,mLookAt.z,
              mUp.x,mUp.y,mUp.z);
    drawModel();
}

//Reshape window.
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

//Change the level of quantization used for the shader.
void UpdateToon(){
        if (ToonMode == 2){
            ToonFragmentShader            = std::string("kernels/toon2color.frag");
        }
         else if( ToonMode == 3){
            ToonFragmentShader            = std::string("kernels/toon3color.frag");
         }
          else if(ToonMode == 4){
            ToonFragmentShader            = std::string("kernels/toon4color.frag");
          }  
          else if(ToonMode == 5){
            ToonFragmentShader            = std::string("kernels/toon5color.frag");
          }
          else {
            ToonFragmentShader            = std::string("kernels/toon6color.frag");
          }
       
            SetUpShaders();
}

// Processes key press events
void KeyCallback(unsigned char key, int x, int y)
{

    switch(key) {
   

        case 's': {
            // Take a screenshot, and save as screenshot.jpg
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0,0);
            screenshot->Save("../../data/images/screenshot.jpg");
            delete screenshot;
         }
        break;

        case 'q': {
            exit(0);
        }
        break;

        //Increase or decrease quantization.
        case 'm': {
            
            if(ToonMode < 6){
               ToonMode = ToonMode+1; 
               UpdateToon();
            }
            
            
        } break;
        case 'n': {
            
            if(ToonMode > 2){
               ToonMode--; 
               UpdateToon();
            }
            
        }
        break;

        //Load a different model.
        case '1' : {
              meshOBJ                         = std::string("../../data/meshes/Leon.obj");
              Setup();
        }
        break;
        case '2' : {
              meshOBJ                         = std::string("../../data/meshes/cactus.obj");
              Setup();
        }
        break;
        case '3' : {
              meshOBJ                         = std::string("../../data/meshes/Dragon.obj");
              Setup();
        }
        break;
        case '4' : {
              meshOBJ                         = std::string("../../data/meshes/deer.obj");
              Setup();
        }
        break;
       
        default:
            break;
    }

    glutPostRedisplay();
}

//Process key calls.
void SpecialKeyCallback(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            StrafeCamera(10,0);
            break;
        case GLUT_KEY_RIGHT:
            StrafeCamera(-10,0);
            break;
        case GLUT_KEY_DOWN:
            StrafeCamera(0,-10);
            break;
        case GLUT_KEY_UP:
            StrafeCamera(0,10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Mouse event handler
void MouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON
        || button == GLUT_RIGHT_BUTTON
        || button == GLUT_MIDDLE_BUTTON)
    {
        gMouseButton = button;
    } else
    {
        gMouseButton = -1;
    }
    
    if (state == GLUT_UP)
    {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }
}


// Mouse active motion callback.
void MouseMotionCallback(int x, int y)
{
     if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0)
    {
        //compute delta
        float deltaX = x-gPreviousMouseX;
        float deltaY = y-gPreviousMouseY;
        gPreviousMouseX = x;
        gPreviousMouseY = y;
        
        //orbit, strafe, or zoom
        if (gMouseButton == GLUT_LEFT_BUTTON)
        {
            RotateCamera(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_MIDDLE_BUTTON)
        {
            StrafeCamera(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_RIGHT_BUTTON)
        {
            ZoomCamera(deltaY);
        }
        
    } else
    {
        gPreviousMouseX = x;
        gPreviousMouseY = y;
    }
}

//-------------------------------------------------
// main program loop
//-------------------------------------------------
int main(int argc, char** argv)
{
    //Give shader file names. 
    ToonFragmentShader            = std::string("kernels/toon2color.frag");
    ToonVertexShader              = std::string("kernels/toon.vert");
   
    //Give initial model file name.
    meshOBJ                         = std::string("../../data/meshes/deer.obj");
    
    // Initialize GLUT.
    glutInitWindowSize(800, 800);
    glutInit(&argc, argv);


    // initialize display mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Cel-Shading");


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

    // set  the scene
    Setup();

    // callback functions

    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutKeyboardFunc(KeyCallback);
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotionCallback);
    glutIdleFunc(DisplayCallback);
    glutSpecialFunc(SpecialKeyCallback);

    // run the main glut loop
    glutMainLoop();

    // return
    return 0;
}
