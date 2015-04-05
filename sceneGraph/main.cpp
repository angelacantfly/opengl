#include <iostream>
#include "main.h"
#include "control.h"
#include "avatar.h"

// global variables
using namespace std;

// location of robot
double AVATAR_POS_X = 0.0;
double AVATAR_POS_Y = 0.0;
double AVATAR_POS_Z = 0.0;

double phi = 89.41 + EPSLON;    // camera view: up and down
double beta = 0;            // camera view: left to right

double head_theta = 0.0;    // how much the robot nods
double head_beta = 0.0;     // how much the robot looks left and right


double HEADLAMPHEIGHT = 0;  // position of head lamp
double WAVE_SWIM = 0;       // how much robot moves arms (front to back)
double WAVE_UP_DOWN = 0;    // how much robot moves arms (up and down)

// toggle lighting
bool AMBIENT = false;
bool POINTLIGHT = false;
bool HEADLAMPSTATUS = false;

// toggle camera perspective
bool robotPerspective = false;

// how much user controls camera
double VIEW_RADIUS = 30;
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
    
    // initialize background color to purple
    glClearColor(0.44,0.24,0.37,0);

    // enable light0 and lighting
    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    
    // set color of point light
    GLfloat white[] = {1,1,1,0};		      // light color
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);   // set diffuse light color
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);  // set specular light color
    
    // set color of headlamp
    GLfloat red[] = {1,0,0,0};		      // light color
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
    GLfloat direction[] = {0, -1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);   // set diffuse light color
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);

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
    
    // regular camera view
    if (!robotPerspective) {
        gluLookAt(CAMERA_X, CAMERA_Y, CAMERA_Z, 0, 0, 0, 0, 1, 0);
    } else {
        gluLookAt(AVATAR_POS_X, AVATAR_POS_Y, AVATAR_POS_Z, 0, 0, 0, 0, 1,0);
    }

    if (HEADLAMPSTATUS) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);
    
    if (AMBIENT) {
        GLfloat ambientWhite[] = {0.2,0.2,0.2,0.2};
        glLightfv(GL_LIGHTING, GL_AMBIENT, ambientWhite);
    }
    else {
        GLfloat noambient[] = {0,0,0,0};
        glLightfv(GL_LIGHTING, GL_AMBIENT, noambient);
    }
    
    // SET POINT LIGHT POSITION
    GLfloat lightPosition[]={0,3,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    if (POINTLIGHT) glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);
    
    drawFloor();
    drawGenie();
    
    glutSwapBuffers();
}


void drawGenie() {
    glTranslatef(AVATAR_POS_X,0,AVATAR_POS_Z);

    // regular view
    if (!robotPerspective) {
        // draw genie's body parts
        drawGenieTeapot();
        drawGenieBottom();
        drawGenieMiddle();
        drawHead();
        drawSpotLight();
    }
//    
//    glTranslatef(-AVATAR_POS_X,0,-AVATAR_POS_Z);
//    glColor3f(1, 0, 0);
//    double BOTTOM_RADIUS = 1;
//    // position of light1
//    GLfloat ypos = 1.9 * BOTTOM_RADIUS + 0.5;
//    GLfloat zpos = AVATAR_POS_Z + 0.3 + 0.1 ;
//    GLfloat lightPosition[]={0,ypos,0,1};
//    
//    GLfloat hx, hy, hz;
//    hx = AVATAR_POS_X;
//    hy = 1.9 * BOTTOM_RADIUS + 0.5 * cos(head_theta/180 * M_PI);
//    hz = AVATAR_POS_Z + 0.4 + 0.4 * sin(head_theta/180 * M_PI)* cos(head_beta/180 * M_PI) ;
//    cout << "head_beta : " << head_beta << endl;
//    cout << "head_theta : " << head_theta << endl;
//    cout << "hy " << hy << "     hz " << hz<<endl;
//    //    glTranslatef(static_cast<GLfloat>(AVATAR_POS_X), ypos, zpos);
//    glTranslatef(hx, hy, zpos);
//    glutSolidSphere(0.1, 5, 5);
//    
//    GLfloat lightpos[] = {hx,hy,zpos,1};
//    // set color of light0
//    GLfloat ambientWhite[] = {0.2,0.2,0.2,0.2};
//    GLfloat white[] = {1,0,0,0};		      // light color
//    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
//    GLfloat direction[] = {0, -1.0, 1.0};
//    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);   // set diffuse light color
//    //glLightfv(GL_LIGHT1, GL_SPECULAR, white);  // set specular light color
//    //glLightfv(GL_LIGHT1, GL_AMBIENT, ambientWhite);
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);
}



void drawSpotLight()
{
    double BOTTOM_RADIUS = 1;
    
    // position of head lamp marker
    GLfloat headLampX = AVATAR_POS_X;
    GLfloat headLampY = 1.9 * BOTTOM_RADIUS + 0.5 * cos(head_theta/180 * M_PI);
    GLfloat headLampZ = AVATAR_POS_Z + 0.4 + 0.4 * sin(head_theta)* sin(head_beta) ;
    
    // draw head lamp marker
    glRotatef(head_beta,0,1,0);     // move with head left and right
    glRotatef(head_theta,1,0,0);    // move with head up and down
    glTranslatef(headLampX, headLampY, headLampZ);
        glColor3f(1, 0, 0);            // red
        glutSolidSphere(0.1, 5, 5);    // star-shaped
    glTranslatef(-headLampX, -headLampY, -headLampZ);
    glRotatef(-head_theta,1,0,0);    // look up and down
    glRotatef(-head_beta,0,1,0);     // look left and right
    
    // spot light properties
    GLfloat spotLightPosition[] = {headLampX,headLampY, headLampZ, 1};
    GLfloat yellow[] = {1,1,0,0};
    GLfloat direction[] = {0, -1.0, 1.0};
    
    glLightfv(GL_LIGHT1, GL_POSITION, spotLightPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow);   // set diffuse light color
    glLightfv(GL_LIGHT1, GL_SPECULAR, yellow);  // set specular light color
    
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
}

