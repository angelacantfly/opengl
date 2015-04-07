#include <iostream>
#include "main.h"
#include "control.h"
#include "avatar.h"
#include "shadow.h"
#include "SOIL.h"

// global variables
using namespace std;

// location of robot
double AVATAR_POS_X = 0.0;
double AVATAR_POS_Y = 0.0;
double AVATAR_POS_Z = 0.0;

double phi = M_PI/2.1 + EPSLON;     // camera view: up and down
double beta = 0;                    // camera view: left to right

double head_theta = 0.0;    // how much the robot nods
double head_beta = 0.0;     // how much the robot looks left and right


double HEADLAMPHEIGHT = 0;  // position of head lamp
double WAVE_SWIM = 0;       // how much robot moves arms (front to back)
double WAVE_UP_DOWN = 0;    // how much robot moves arms (up and down)

// toggle lighting
bool AMBIENT = false;
bool POINTLIGHT = false;
bool HEADLAMPSTATUS = false;
GLfloat lightPosition[]={0,3,0,1};

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    
    // create window
    glutCreateWindow("Genie's Great Adventure");
    
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
//    glLoadIdentity();
    
    // initialize background color to purple
    glClearColor(0.44,0.24,0.37,0);
    // initialize shade model to smooth
    glShadeModel(GL_SMOOTH);
    
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
    // initialize stencil clear value
    glClearStencil(0.0);
    
    // texture mapping: magic ball
    LoadGLTextures("/Users/maureennaval/Desktop/opengl/sceneGraph/magicBall-01.png");
    
//    // texture mapping: billboard
//    LoadGLTextures("/Users/maureennaval/Desktop/opengl/sceneGraph/tajMahal.png");
    
    // initialize stencil clear value
    glClearStencil(0.0);
    
    // fog
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    GLfloat fogColor[4]= {1, 0.7, 0.7, 1.0};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.01);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
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
    // check for openGL errors
    GLenum errCode;
    if ((errCode = glGetError()) != GL_NO_ERROR)
        cout << gluErrorString(errCode) << endl;
    glPopMatrix();
    
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
        gluLookAt(headLampX, headLampY + 2, headLampZ, headLampX , 0, headLampZ + 3, 0, 1,0);
    }
    glPushMatrix();

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
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    if (POINTLIGHT) glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    drawEverythingWithShadow();
    
    // billboard
    glEnable(GL_TEXTURE_2D);
        drawBillboard();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
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

void drawEverythingWithShadow() {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1,-1);
    
    // disable buffers
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    // enable stencil test
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL,0,3);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
    // enable face cull
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // draw floor
    float floorDiffuse[]={1.0,0.0,0.0};
    float floorAmbient[]={1.0,0.0,0.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floorDiffuse);
    drawFloor();
    
    // enable buffers
    glEnable(GL_DEPTH_TEST);
    // disable stencil test
    glDisable(GL_STENCIL_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    // disable face cull
    glDisable(GL_CULL_FACE);
    
    // enable stencil test: shadow
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 3);
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    
    // shadow
    GLfloat shadowMat[16];
    GLfloat groundplane[4]={0,1,0,0};
    shadowMatrixPointLight(shadowMat, groundplane, lightPosition);
    glPushMatrix();
    glMultMatrixf(shadowMat);
    GLfloat black[4]={0,0,0,0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
    drawGenie();
    glPopMatrix();
    // disable stencil test: shadow
    glDisable(GL_STENCIL_TEST);
    
    drawGenie();
    
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    // draw floor
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floorDiffuse);
    drawFloor();
    
    // draw magic ball
    drawMagicBall();
}

void _drawFloor(void)
{
    glPushMatrix();
    glNormal3f(0,1,0);
        glBegin(GL_QUADS);
        glVertex3f(-5,0,-5);
        glVertex3f(-5,0,5);
        glVertex3f(5,0,5);
        glVertex3f(5,0,-5);
        glEnd();
    glPopMatrix();
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

//    // make transparent by setting parts of image to background color
//    glColor4f(0.44,0.24,0.37,1);
    
    glTranslatef(0, 0, -5);
        glBegin(GL_QUADS);
        // bottom left corner
        glTexCoord2f(0, 0);
        glVertex3f(-10, 0, -5);
        // top left corner
        glTexCoord2f(0, 1);
        glVertex3f(-10, 10, -5);
        // top right corner
        glTexCoord2f(1, 1);
        glVertex3f(10, 10, -5);
        // bottom right corner
        glTexCoord2f(1, 0);
        glVertex3f(10, 0, -5);
        glEnd();
    glTranslatef(0, 0, 5);
    
    billboardEnd();
}

bool LoadGLTextures(char* fname)
{
    int textureId = SOIL_load_OGL_texture(fname, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(textureId == 0)
        return false;
    
    // magic ball texture
    // tell what texture to use
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // specify resampling method
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // how texture should be used
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    return true;
}

void drawMagicBall()
{
    glPushMatrix();
    glTranslatef(2, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
        GLUquadric *quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);   // add texture
        gluSphere(quad, 0.5, 20, 20);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(-2, -0.5, 0);
    glPopMatrix();
}
