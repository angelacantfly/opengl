#include <iostream>
#include <glut/glut.h>
#include <math.h>

// function prototypes
void display(void);
void reshape(int width, int height);
void init();

void drawSnowman();
void drawBottom();
void drawMiddle();
void drawArm(bool x);
void drawHead();
void drawEye(bool x);
void drawFloor();

void keyboard(unsigned char key, int x, int y);

// global variables

// window dimensions
int windowWidth=600;
int windowHeight=600;
// position of snowman
double snowmanX = 0.0;
double snowmanZ = 0.0;
// nod angle
double theta = 0.0;

using namespace std;

// user controls position of snowman
void special(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) {
        snowmanX--;
    } else if (key == GLUT_KEY_RIGHT) {
        snowmanX++;
    } else if (key == GLUT_KEY_DOWN) {
        snowmanZ--;
    } else if (key == GLUT_KEY_UP) {
        snowmanZ++;
    }
    
    glutPostRedisplay();
}

// user controls snowman nod
void keyboard(unsigned char key, int x, int y)
{
    // nod up
    if (key == 'x')
        theta += 5;
    // nod down
    if (key == 'c')
        theta -= 5;
    
    glutPostRedisplay();
}

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
    
    // register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    
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
    glClearColor(0,0,0,0);
    
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
    gluLookAt(0, 15, 30, 0, 0, 0, 0, 1, 0);
    
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

void drawBottom(){
    GLfloat radius=1;
    GLfloat red[] = {1,0,0};
    glColor3fv(red);
    glPushMatrix();
    glTranslatef(0,radius,0);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
}

void drawFloor() {
    glColor3f(1,1,1);       // white floor
    glRotatef(-45,1,0,0);

    glRectf(-5, -5, 5, 5);  // centered at origin (y-plane)
}


void drawMiddle() {
    GLfloat radius=1;
    GLfloat red[] = {1,0,0};
    glColor3fv(red);
    glPushMatrix();
    glTranslatef(0,2*radius,0);
    glutSolidSphere(radius*0.75, 20, 20);
    glPopMatrix();
    
    drawArm(true); // left arm
    drawArm(false);// right arm
}

void drawArm(bool isLeft) {
    GLfloat blue[] = {0,0,1};
    glColor3fv(blue);
    glPushMatrix();
    
    if (isLeft) glTranslatef(-1,2,0.5);
    else    glTranslatef(0.5,2,0.5);
    
    glRectf(-0.5,0,1,0.125);
    glPopMatrix();
}

void drawHead() {
    GLfloat radius=1;
    GLfloat red[] = {1,0,0};
    glColor3fv(red);
    glPushMatrix();
    glTranslatef(0,3*radius,0);
    
    glRotatef(theta,1,0,0);
    glutSolidSphere(radius*0.5, 20, 20);
    
    drawEye(true);  // left eye
    drawEye(false); // right eye
    
    glPopMatrix();
}

void drawEye(bool isLeft) {
    GLfloat radius=0.25;
    GLfloat blue[] = {0,0,1};
    glColor3fv(blue);
    glPushMatrix();
    
    if (isLeft) glTranslatef(-0.25,0,0.5);
    else    glTranslatef(.25,0,0.5);
    
    glutSolidSphere(radius*0.5, 20, 20);
    glPopMatrix();
}
