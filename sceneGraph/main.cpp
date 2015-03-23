#include <iostream>
#include "main.h"
#include "control.h"
#include "avatar.h"

// global variables
using namespace std;

double snowmanX = 0.0;
double snowmanZ = 0.0;
double theta =  0.0;
double phi = 0.0;
bool AMBIENT = false;
bool POINTLIGHT = false;
double CAMERA_X = 20*sin(phi*3.14/180.0);
double CAMERA_Z = 20*cos(phi*3.14/180.0);




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
    GLfloat lightPosition[]={3,1,1,pointLight};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // set color of light0
    GLfloat white[] = {1,1,1,0};		      // light color
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);   // set diffuse light color
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);  // set specular light color
    
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
    gluLookAt(CAMERA_X, 15, CAMERA_Z, 0, 0, 0, 0, 1, 0);
    
    
    
    drawFloor();
    
    drawSnowman();
    
    glutSwapBuffers();
}

void drawSnowman() {
    // allow user control to move snowman
    glTranslatef(snowmanX,0,snowmanZ);

    // draw snowman
    drawBottom();
    drawMiddle();
    drawHead();
}


