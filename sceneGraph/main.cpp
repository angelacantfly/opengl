#include <iostream>
#include "main.h"
#include "control.h"
#include "avatar.h"

// global variables
using namespace std;

// location of robot
double AVATAR_POS_X = 0.0;
double AVATAR_POS_Z = 0.0;

double alpha = 0.0;         // how much the robot turns head left and right
double phi = 0.0 + EPSLON;  // camera view: up and down
double beta = 15;           // camera view: left to right

double head_theta = 0.0;    // how much the robot nods
double head_beta = 0.0;

double HEADLAMPHEIGHT = 0;  // position of head lamp
double WAVE_SWIM = 0;       // how much robot moves arms (front to back)
double WAVE_UP_DOWN = 0;    // how much robot moves arms (up and down)

// toggle lighting
bool AMBIENT = false;
bool POINTLIGHT = false;

// how much user controls camera
double VIEW_RADIUS = 20;
double CAMERA_Z = VIEW_RADIUS * sin(phi) * cos(beta); // zoom in and out
double CAMERA_X = VIEW_RADIUS * sin(phi) * sin(beta); // left and right
double CAMERA_Y = VIEW_RADIUS * cos(phi);             // up and down

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


void drawGenie() {
    glTranslatef(AVATAR_POS_X,0,AVATAR_POS_Z);

    // draw genie's body parts
    drawGenieBottom();
    drawGenieMiddle();
    drawHead();
    drawGenieTeapot();
    glColor3f(1, 0, 0);
    //    // enable light1 and lighting
        glEnable(GL_LIGHT1);
    //
    double BOTTOM_RADIUS = 1;
        // position of light1
        GLfloat ypos = 2.0 * BOTTOM_RADIUS + 0.5;
        GLfloat zpos = AVATAR_POS_Z + 0.3 + 0.1 ;
        GLfloat lightPosition[]={static_cast<GLfloat>(AVATAR_POS_X),ypos,zpos,1};
    glTranslatef(static_cast<GLfloat>(AVATAR_POS_X), ypos, zpos);
    glutSolidSphere(0.1, 5, 5);
    
        // set color of light0
        GLfloat ambientWhite[] = {0.2,0.2,0.2,0.2};
        GLfloat white[] = {1,0,0,0};		      // light color
        GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
        GLfloat direction[] = {0, -1.0, 1.0};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white);   // set diffuse light color
        glLightfv(GL_LIGHT1, GL_SPECULAR, white);  // set specular light color
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambientWhite);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);
    
    
}

