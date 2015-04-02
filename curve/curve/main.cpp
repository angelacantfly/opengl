
/*    CATMULL-ROM LAB	*/



#include <iostream>
#include <glut/glut.h>
#include <math.h>

// function prototypes
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void init(void);
void drawCurve(int i);

// global vars
const int numPoints = 4;
float points[numPoints][3];
int currPoint=0;

// viewpoint
double theta=.5, phi=.5, d=150;

// window
int width = 600;
int height = 600;


using namespace std;


int
main(int argc, char **argv)
{
    
    // set up window
    glutInitWindowSize(400, 400);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Bezier Demo");
    
    // register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    
    
    // initalize opengl parameters
    init();
    
    // initialize points
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
    gluPerspective(45.0, 1.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    
    // shading model
    glEnable(GL_SMOOTH);
    
    
    // initialize background color to black
    glClearColor(0.0,0.0,0.0,0.0);
    
    // enable depth buffering
    glEnable(GL_DEPTH_TEST);
    
}



void reshape(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    // preserve aspect ratio
    if (width < height)
        glViewport(0,0,width,width);
    else
        glViewport(0,0,height,height);
}

void display()
{
    // we'll draw axis lines centered at (0,0,0)
    double center[3]={0,0,0};
    
    // compute eye position
    // the eye is a distance d from the center at
    // at an angle phi from z in plane y=1
    // and then rotate the theta out of the y=1 plane
    // e.g. when the center is (0,0,0) and phi=theta=0 we are at (0,0,d)
    // looking at the origin
    
    glLoadIdentity();
    double eye[3]={0,0,0};
    eye[0] = center[0] + (float) d * cos(theta) * sin(phi);
    eye[1] = center[1] + (float) d * sin(theta);
    eye[2] = center[2] + (float) d * cos(theta) * cos(phi);
    
    // compute up vector
    // we use (0,1,0) as the default up position
    // this doesn't work if the eye is on the y-axis
    // but we just won't let the user do that
    double up[3]={0,1,0};
    
    gluLookAt(eye[0],eye[1],eye[2], center[0],center[1],center[2],up[0], up[1], up[2]);
    
    glTranslatef(0,-50,0);
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  now draw axis in x,y,z directions from center
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(center[0],center[1],center[2]);
    glVertex3f(center[0]+100,center[1],center[2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(center[0],center[1],center[2]);
    glVertex3f(center[0],center[1]+100,center[2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(center[0],center[1],center[2]);
    glVertex3f(center[0],center[1],center[2]+100);
    glEnd();
    
    
    glTranslatef(0,0,-20);
    
    // draw points
    glColor3f(1,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i=0;i<numPoints;i++) {
        glVertex3f(points[i][0],points[i][1],points[i][2]);
    }
    glEnd();
    glColor3f(1,1,1);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(points[currPoint][0],points[currPoint][1],points[currPoint][2]);
    glEnd();
    
    
    glColor3f(0,0,1);
    drawCurve(0);
    
    
    
    
    // draw to screen
    glutSwapBuffers();
}

void keyboard(unsigned char key, int mouseX, int mouseY)
{
    
    switch (key) {
            
        case 'h':
            cout << "Use p to print current control points.";
            cout << "Use i to zoom in." << endl;
            cout << "Use o to zoom in." << endl;
            cout << "Use n and N to change current point(indicated in white)." << endl;
            cout << "Use x to reduce x-value of current point." << endl;
            cout << "Use X to increase x-value of current point." << endl;
            cout << "Use y to reduce y-value of current point." << endl;
            cout << "Use Y to increase Y-value of current point." << endl;
            cout << "Use z to reduce z-value of current point." << endl;
            cout << "Use Z to increase Z-value of current point." << endl;
    
            break;
            
        case 'p':
            for (int i=0;i<numPoints;++i) {
                cout << points[i][0] << ", " << points[i][1] << "," << points[i][2] << endl;
            }
            break;
            
        case 'i':
            d-=5;
            break;
        case 'o':
            d+=5;
            break;
            
        case 'n':
            currPoint++;
            currPoint %= numPoints;
            break;
            
        case 'N':
            currPoint--;
            currPoint %= numPoints;
            break;
            
        case 'x':
            points[currPoint][0] -=1;
            break;
        case 'X':
            points[currPoint][0] +=1;
            break;
            
        case 'y':
            points[currPoint][1] -=1;
            break;
        case 'Y':
            points[currPoint][1] +=1;
            break;
            
            
        case 'z':
            points[currPoint][2] -=1;
            break;
        case 'Z':
            points[currPoint][2] +=1;
            break;
    }
    glutPostRedisplay();
}




/*
 *	This routine reads mouse movement and adjusts
 *	camera position/orientation.
 */

void motion(int x, int y)
{
    
    static int currX=-1;
    static int currY=-1;
    
    // wait until a mouse position is recorded and
    // avoid really big jumps
    if (currX>0  && abs(x-currX) < width/6 && abs(y-currY) < height/6) {
        
        //update phi and theta based on change in x and y
        int xChange = currX - x;
        int yChange = y - currY;
        phi += (xChange / 180.0);
        theta += (yChange / 180.0);
        
        // limit theta to -4pi/9 and 4pi/9
        // it is disorienting to lose "up"
        if (theta < -4*3.14159/9.0)
            theta = -4*3.14159/9.0;
        if (theta > 4*3.14159/9.0)
            theta = 4*3.14159/9.0;
    }
    currX = x;
    currY = y;
    glutPostRedisplay();
}


/*  draw a bezier spline based on control points[startPoint],
 /*  points[startPoint+1], and points[startPoint+2], points[startPoint+3] */

void drawCurve(int startPoint) {
    if (startPoint==0 || startPoint+2>=numPoints)
        return;
    
    float coeff[3][4];
    float basisMatrix[4][4] = { {-1,3,-3,1},{3,-6,3,0},{-3,3,0,0},{1,0,0,0}};
    /*  compute coefficients for the x,y, and z cubic polynomials */
    for (int d=0; d<3; d++) { // compute for dimension x, y, and z
        for (int i=0; i< 4; i++) { // compute coeff[d][i]
            coeff[d][i]=0;
            for (int j=0;j<4;j++) {
                // TODO: compute contribution from control point to coeff
                coeff[d][i] += basisMatrix[i][j]* points[d][j];
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

        float x = coeff[0][0]*t*t*t + coeff[0][1]*t*t + coeff[0][2] * t + coeff[0][3];
        float y = coeff[1][0]*t*t*t + coeff[1][1]*t*t + coeff[1][2] * t + coeff[1][3];
        float z = coeff[2][0]*t*t*t + coeff[2][1]*t*t + coeff[2][2] * t + coeff[2][3];
        glVertex3f(x, y, z);
        t += 1.0/numSamples;
        
    }
    /* the curve ends at a control point when t=1  				*/
    /* because the increment 1.0/numSamples  has finite precision	*/
    /* t probably won't hit 1.0 exactly, so we force it			*/
    
    glVertex3f(points[startPoint+1][0],points[startPoint+1][1],points[startPoint+1][2]);
    glEnd();
    
}
