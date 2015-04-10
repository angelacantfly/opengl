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

// robot trick
GLfloat trick = 0.0;

double phi = 1.3 + EPSLON;     // camera view: up and down
double beta = 0;               // camera view: left to right

double head_theta = 0.0;    // how much the robot nods
double head_beta = 0.0;     // how much the robot looks left and right

double HEADLAMPHEIGHT = 0;  // position of head lamp
double WAVE_SWIM = 0;       // how much robot moves arms (front to back)
double WAVE_UP_DOWN = 0;    // how much robot moves arms (up and down)

// toggle lighting
bool AMBIENT = false;
bool POINTLIGHT = true;
bool HEADLAMPSTATUS = false;
GLfloat lightPosition[]={0,3,0,1};

// toggle camera perspective
bool robotPerspective = false;

// toggle robot trick
bool robotTrick = false;
bool lookUp = true;

// curve
const int numCurves = 3;              // Controls the number of curves
const int numPoints = 3*numCurves+1;  // DO NOT CHANGE THIS
float points[numPoints][3];
int currPoint=0;
int typeCurrPoint = OTHER;

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
    glutIdleFunc(idle);
    
    // initalize opengl parameters
    init();
    
    // roller coaster: initialize points
    float spread=100;
    for (int i=0; i< numPoints; i++)
        points[i][0]=points[i][1]=points[i][2]=spread/2.0 - spread/(numPoints+1.0) *i;
    
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
    
    // initialize clear colors
    glClearColor(0,0,0,0);
    
    // initialize background color to purple
    glClearColor(0.44,0.24,0.37,0);
    
    // initialize shade model to smooth
    glShadeModel(GL_SMOOTH);
    
    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);    // start with the point light on

    glEnable(GL_COLOR_MATERIAL);
    
    // set color of point light
    GLfloat white[] = {1,1,1,1};		      // light color
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);   // set diffuse light color
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);  // set specular light color
    
    // set properties of headlamp
    GLfloat direction[] = {0, -1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);   // set diffuse light color
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);

    // enable depth buffering
    glEnable(GL_DEPTH_TEST);
    // initialize stencil clear value
    glClearStencil(0.0);
    
    // set polygon mode
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
    // texture mapping: magic ball
    LoadGLTextures("/Users/maureennaval/Desktop/opengl/sceneGraph/magicBall-01.png");
    
    drawFog();
}


void reshape(int width, int height)
{
    if (width<height)
        glViewport(0,0,width,width);
    else
        glViewport(0,0,height,height);
    
}

void idle()
{
    // only perform robot trick when user toggles menu
    if (robotTrick) {
        
        // nod up
        if (lookUp) {
            head_theta -= 1;
            WAVE_UP_DOWN -=2;       // move arms forward
            if (head_theta <= -60)  // now look down
                lookUp = !lookUp;
        }
        // nod down
        if (!lookUp) {
            head_theta += 1;
            WAVE_UP_DOWN += 2;          // move arms backward
            if (head_theta > 0)
                head_theta = 0;
                if (head_theta == 0)    // now look up
                    lookUp = !lookUp;
        }
        
        glutPostRedisplay();
    }
}

void display()
{
    // check for openGL errors
    GLenum errCode;
    if ((errCode = glGetError()) != GL_NO_ERROR)
        cout << gluErrorString(errCode) << endl;
    
    // initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // regular camera view
    if (!robotPerspective) {
        gluLookAt(CAMERA_X, CAMERA_Y, CAMERA_Z, 0, 0, 0, 0, 1, 0);
    // view world from the robot's perspective
    } else {
        GLfloat angle = atan2f(0.25, 0.5) *180/M_PI;
        GLfloat length = 0.6;
        
        GLfloat headLampX = AVATAR_POS_X + length *sin(head_beta/180*M_PI);
        GLfloat headLampY = 1.9 * 1.0 + length* cos((head_theta + angle)/180 * M_PI);
        GLfloat headLampZ = AVATAR_POS_Z  + 0.7 * sin((head_theta+ angle)/180 * M_PI)* cos(head_beta/180 * M_PI) ;
        
        gluLookAt(headLampX, headLampY + 2, headLampZ, headLampX , 0, headLampZ + 3, 0, 1,0);
    }
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // set point light position
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // draw scene: robot (including teapot) and magic ball
    drawEverythingWithShadow();
    drawSpotLight();
    
    // reflect scene: floor
    // enable stencil test
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL,1,3);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glPushMatrix();
        glScalef(1,-1,1);
        drawEverythingWithShadow();
    glPopMatrix();
    // disable stencil test
    glDisable(GL_STENCIL_TEST);
    
    // floor
    drawFloor();
    
    // reflect scene: mirror
    glPushMatrix();
        glTranslatef(0, 0, -7);
        glScalef(1,1,-1);
        drawEverythingWithShadow();
    glPopMatrix();
    
    // mirror
    drawMirror();
    
    // billboard: galaxy
    glEnable(GL_TEXTURE_2D);
    drawBillboard();
    glDisable(GL_TEXTURE_2D);

    // roller coaster
    drawRollerCoaster();
    
    glutSwapBuffers();
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
    float floorDiffuse[]={1.0,0.0,0.5};
    float floorAmbient[]={1.0,0.0,0.5};
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

    
    glDisable(GL_POLYGON_OFFSET_FILL);

    drawGenie();
    drawMagicBall();
    
    // floor: tag
//    float floorDiffuse[]={1.0,0.0,0.0};
//    float floorAmbient[]={1.0,0.0,0.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floorAmbient);
    // disable buffers
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    // enable stencil buffer: floor
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL,0,3);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
    // enable face cull
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    drawFloor();
    // disable face cull
    glDisable(GL_CULL_FACE);
    // disable stencil test
    glDisable(GL_STENCIL_TEST);
    // enable buffers
    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    

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

void drawRollerCoaster(){
    glPushMatrix();
    
    // draw points
    glPointSize(5);
    glBegin(GL_POINTS);
    for (int i=0;i<numPoints;i++) {
        // alternate between 2 colors depending on number of points
        if (i%3==0) {
            glColor3f(1,0,1);   // purple
        }
        else
        {
            glColor3f(1,1,0);   // yellow
        }
        glVertex3f(points[i][0],points[i][1],points[i][2]); // point on x,y,z
    }
    glEnd();
    
    // draw blue curve
    glColor3f(0,0,1);
    for (int i=0; i<numCurves; i++)
    {
        drawCurve(3*i);
    }

    glPopMatrix();
}

/*  draw a bezier spline based on control points[startPoint],
 /*  points[startPoint+1], and points[startPoint+2], points[startPoint+3] */
void drawCurve(int startPoint) {
    if (startPoint<0 || startPoint+2>=numPoints)
        return;
    
    float coeff[3][4];
    float basisMatrix[4][4] = {
        {-1,  3, -3, 1},
        { 3, -6,  3, 0},
        {-3,  3,  0, 0},
        { 1,  0,  0, 0}};
    /*  compute coefficients for the x,y, and z cubic polynomials */
    for (int d=0; d<3; d++) { // compute for dimension x, y, and z
        for (int i=0; i< 4; i++) { // compute coeff[d][i]
            coeff[d][i]=0;
            for (int j=0;j<4;j++) {
                coeff[d][i] += basisMatrix[i][j] * points[j+startPoint][d];
            }
        }
    }
    
    /*  approximate the curve by a line strip through sample points	*/
    glBegin(GL_LINE_STRIP);
    float numSamples=10;
    float val[3];
    float t=0;
    while(t<1) {
        /* TODO: compute X(t), Y(t), and Z(T) and create openGL vertex */
        float polyVal[3];
        for (int i=0;i<3;i++) {
            polyVal[i] = coeff[i][0]*t*t*t + coeff[i][1]*t*t + coeff[i][2]*t + coeff[i][3];
            
        }
        glVertex3f(polyVal[0], polyVal[1], polyVal[2]);
        t += 1.0/numSamples;
        
    }
    /* the curve ends at a control point when t=1  				*/
    /* because the increment 1.0/numSamples  has finite precision	*/
    /* t probably won't hit 1.0 exactly, so we force it			*/
    
    glVertex3f(points[startPoint+3][0],points[startPoint+3][1],points[startPoint+3][2]);
    glEnd();
}

void drawFog()
{
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    GLfloat fogColor[4]= {1, 0.7, 0.7, 1.0};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.01);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
}

