#include <iostream>
#include "main.h"
#include "control.h"
#include "avatar.h"

// global variables
using namespace std;

// location of robot
double AVATAR_POS_X = 0.0;
double AVATAR_POS_Z = 0.0;

double theta =  0.0;        // how much the robot nods
double phi = 0.0;           // camera view: left to right
double beta = 15;           // camera view: up and down

double HEADLAMPHEIGHT = 0;  // position of head lamp
double WAVE_SWIM = 0;       // how much robot moves arms (front to back)
double WAVE_UP_DOWN = 0;    // how much robot moves arms (up and down)

// toggle lighting
bool AMBIENT = false;
bool POINTLIGHT = false;

// how much user controls camera
double CAMERA_X = 20*sin(phi*3.14/180.0);   // left and right
double CAMERA_Z = 20*cos(phi*3.14/180.0);   // zoom in and out
double CAMERA_Y = 50*tan(beta*3.14/180.0);  // up and down


int main(int argc, char **argv)
{
    // initialize glut
    glutInit(&argc, argv);
    
    // set window size
    glutInitWindowSize(windowWidth,windowHeight);
    
    // establish glut display parameters
    glutInitDisplayMode(GLUT_DOUBLE   | GLUT_RGB  |GLUT_DEPTH);
    
    // create window
    glutCreateWindow("My Third OpenGL program");
    
    make_menu();
    
    // register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    // initalize opengl parameters
    init();
    
    // loop until something happens
    glutMainLoop();
    return 0;
}

void init()
{
    // initialize viewing system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, 1.0, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // initialize background color to black
    glClearColor(0,0.5,0.5,0);
    
    // enable light0 and lighting
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
    glEnable(GL_COLOR_MATERIAL);
    
    // position of light0
    float pointLight = 0;
    if (POINTLIGHT) pointLight = 1;
    GLfloat lightPosition[]={0,1,0,pointLight};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // set color of light0
    GLfloat ambientWhite[] = {0.2,0.2,0.2,0.2};
    GLfloat white[] = {1,1,1,0};		      // light color
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);   // set diffuse light color
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);  // set specular light color
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientWhite);
    
    // enable depth buffering
    glEnable(GL_DEPTH_TEST);
}


void reshape(int width, int height)
{
    if (width<height)
        glViewport(0,0,width,width);
    else
        glViewport(0,0,height,height);
    
}

void display()
{
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // initialize modelview matrix
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glLoadIdentity();
    gluLookAt(CAMERA_X, CAMERA_Y, CAMERA_Z, 0, 0, 0, 0, 1, 0);
    
    // toggle Ambient Light
    if (AMBIENT)
    {
        GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2};
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    }
    else
    {
        GLfloat no_ambient[] = {0,0,0,0};
        glLightfv(GL_LIGHT0, GL_AMBIENT, no_ambient);
    }
    
    // TOGGLE POINT LIGHT
    float pointLight = 0;
    if (POINTLIGHT) pointLight = 1;
    GLfloat lightPosition[]={0,3,0,pointLight};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    drawFloor();
    drawGenie();
    
    glutSwapBuffers();
}



void drawSnowman() {
    // allow user control to move snowman
    
    glTranslatef(AVATAR_POS_X,0,AVATAR_POS_Z);

    // draw snowman
    drawBottom();
    drawMiddle();
    drawHead();
}

void drawGenie() {
    glTranslatef(AVATAR_POS_X,0,AVATAR_POS_Z);

    // draw genie's body parts
    drawGenieBottom();
    drawGenieMiddle();
    drawHead();
}

