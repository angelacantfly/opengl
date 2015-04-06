#include <iostream>
#include "main.h"
#include "control.h"
#include "avatar.h"
#include "SOIL.h"

// global variables
using namespace std;

// location of robot
double AVATAR_POS_X = 0.0;
double AVATAR_POS_Y = 0.0;
double AVATAR_POS_Z = 0.0;

double phi = M_PI/2 + EPSLON;    // camera view: up and down
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
    
    // texture mapping: billboard
    LoadGLTextures("/Users/maureennaval/Desktop/opengl/sceneGraph/tajMahal.png");
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
        GLfloat angle = atan2f(0.25, 0.5) *180/M_PI;
        GLfloat length = 0.6;
        GLfloat headLampX = AVATAR_POS_X + length *sin(head_beta/180*M_PI);
        GLfloat headLampY = 1.9 * 1.0 + length* cos((head_theta + angle)/180 * M_PI);
        GLfloat headLampZ = AVATAR_POS_Z  + 0.7 * sin((head_theta+ angle)/180 * M_PI)* cos(head_beta/180 * M_PI) ;
        gluLookAt(headLampX, headLampY, headLampZ, 0, 0, 0, 0, 1,0);
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
    
    // draw the scene
    drawFloor();
    drawGenie();
    
    // billboard
    glEnable(GL_TEXTURE_2D);
    drawBillboard();
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}


void drawGenie() {
    

    // regular view
    if (!robotPerspective) {
        // draw genie's body parts
        glTranslatef(AVATAR_POS_X,0,AVATAR_POS_Z);
        drawGenieTeapot();
        drawGenieBottom();
        drawGenieMiddle();
        drawHead();
        glTranslatef(-AVATAR_POS_X,0,-AVATAR_POS_Z);
        drawSpotLight();
    }
    
}



void drawSpotLight()
{
    double BOTTOM_RADIUS = 1;
    
    // position of head lamp marker
    // FIXME: the headlamp is not completely in sync with the head rotation
    //          when the head turns into weird angle
    GLfloat angle = atan2f(0.25, 0.5) *180/M_PI;
    GLfloat length = 0.6;
    GLfloat headLampX = AVATAR_POS_X + length *sin(head_beta/180*M_PI);
    GLfloat headLampY = 1.9 * BOTTOM_RADIUS + length* cos((head_theta + angle)/180 * M_PI);
    GLfloat headLampZ = AVATAR_POS_Z  + length * sin((head_theta+ angle)/180 * M_PI)* cos(head_beta/180 * M_PI) ;
    
    // draw head lamp marker
    glTranslatef(headLampX, headLampY, headLampZ);
    glRotatef(head_beta,0,1,0);     // move with head left and right
    glRotatef(head_theta,1,0,0);    // move with head up and down
    
        glColor3f(1, 0, 0);            // red
        glutSolidSphere(0.1, 5, 5);    // star-shaped
    glRotatef(-head_theta,1,0,0);    // look up and down
    glRotatef(-head_beta,0,1,0);     // look left and right
    glTranslatef(-headLampX, -headLampY, -headLampZ);
    
    
    // spot light properties
    GLfloat spotLightPosition[] = {headLampX,headLampY, headLampZ, 1};
    GLfloat yellow[] = {1,1,0,0};
    GLfloat direction[] = {static_cast<GLfloat>(1.0 * sin(head_beta/180*M_PI)) ,
                            -1.0,
                            static_cast<GLfloat>(1.0 * cos(head_beta/180 * M_PI))};
    
    glLightfv(GL_LIGHT1, GL_POSITION, spotLightPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow);   // set diffuse light color
    glLightfv(GL_LIGHT1, GL_SPECULAR, yellow);  // set specular light color
    
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    
}

void drawMagicBall()
{
    
}

void billboardBegin() {
    
    float modelview[16];
    int i,j;
    
    // save the current modelview matrix
    glPushMatrix();
    
    // get the current modelview matrix
    glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
    
    // undo all rotations
    // beware all scaling is lost as well
    for( i=0; i<3; i++ )
        for( j=0; j<3; j++ ) {
            if ( i==j )
                modelview[i*4+j] = 1.0;
            else
                modelview[i*4+j] = 0.0;
        }
    
    // set the modelview with no rotations
    glLoadMatrixf(modelview);
}

void billboardEnd() {
    
    // restore the previously
    // stored modelview matrix
    glPopMatrix();
}

void drawBillboard() {
    billboardBegin();
    
    glPushMatrix();
    glTranslatef(0, 0, -5);
        glBegin(GL_QUADS);
        // bottom left corner
        glTexCoord2f(0, 0);
        glVertex3f(-6, 0, -5);
        // top left corner
        glTexCoord2f(0, 1);
        glVertex3f(-6, 5, -5);
        // top right corner
        glTexCoord2f(1, 1);
        glVertex3f(6, 5, -5);
        // bottom right corner
        glTexCoord2f(1, 0);
        glVertex3f(6, 0, -5);
        glEnd();
    glTranslatef(0, 0, 5);
    glPopMatrix();
    
    billboardEnd();
}

bool LoadGLTextures(char* fname)
{
    int textureId = SOIL_load_OGL_texture(fname, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(textureId == 0)
        return false;
    
    // tell what texture to use
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // specify resampling method
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    // how texture should be used
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    return true;
}
