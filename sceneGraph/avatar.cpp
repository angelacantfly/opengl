//
//  avatar.cpp
//  sceneGraph
//
//  Created by ANGELA ZHOU on 3/22/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#include "avatar.h"
#include "common.h"
#include "main.h"

using namespace std;

GLfloat BOTTOM_RADIUS = 1.0;
GLfloat EYE_RADIUS = 0.25 * BOTTOM_RADIUS;

void drawFloor()
{
    // blend for reflection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // location
    double originx = -9;
    double originy = -9;
    
    // alternate between black (0) and white (1)
    int color = 0;
    
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glNormal3f(0,0,1);
    for (int row = 0 ; row < 9; ++row)
        for (int col = 0; col < 13; ++ col)
        {
            ++color;
            tileFloor(originx + 2 * row, originy + 2 * col, originx + 2 * (row + 1), originy + 2* (col + 1), color%2, color%2, color%2);
        }
    glPopMatrix();

    // stop blend for reflection
    glDisable(GL_BLEND);
}

void tileFloor(double x1, double y1, double x2, double y2, double r, double g, double b)
{
    glColor4f(r, g, b, 0.5);
    glRectf(x1, y1, x2, y2);
}

void drawArm(bool isLeft) {
    glColor3f(1,1,1);
    
    glPushMatrix();
    
    double wave_direction;
    if (isLeft) wave_direction = -1;
    else wave_direction = 1;
    
    // position for left and right arm
    if (isLeft) glTranslatef(-0.3,-0.1,0);
    else    glTranslatef(0.3,-0.1,0);
    
    // flip location of shoulder joint for left arm
    if (isLeft) glRotatef(180, 0, 1, 0);
    
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    glRotatef(90,0,1,0);
    glRotatef(WAVE_SWIM * wave_direction, 0, 1, 0);         // move arms front to back
    glRotatef(WAVE_UP_DOWN , 1, 0, 0);                      // move arms up and down
        gluCylinder(quadratic, 0.05, 0.05, 0.4, 20, 20);
    
    glPopMatrix();
}

void drawHead() {
    glColor3f(1,1,1);
    
    glPushMatrix();
    glTranslatef(0,1.9*BOTTOM_RADIUS,0);
    glRotatef(head_theta,1,0,0);    // look up and down
    glRotatef(head_beta,0,1,0);     // look left and right
        glutSolidSphere(BOTTOM_RADIUS*0.5, 20, 20); // head
        drawHat(BOTTOM_RADIUS);                     // hat
    
        drawEye(true);                              // left eye
        drawEye(false);                             // right eye
    
        drawEarring(true);                          // left earring
        drawEarring(false);                         // right earring
    glPopMatrix();
}

void drawEye(bool isLeft) {
    glColor3f(0,0,0);
    
    glPushMatrix();
    // position for each eye
    if (isLeft) glTranslatef(-0.25,0,0.5);
    else    glTranslatef(.25,0,0.5);
    
    glutSolidSphere(EYE_RADIUS*0.5, 20, 20);
    
    glPopMatrix();
}

void drawEarring(bool isLeft)
{
    glColor3f(1,1,0);   // yellow
    
    glPushMatrix();
    // position of each earring
    if (isLeft) glTranslatef(-0.5,-0.25,0);
    else    glTranslatef(.5,-0.25,0);
    
    glRotatef(90,0,1,0);
    glutSolidTorus(EYE_RADIUS/4, EYE_RADIUS/2, 20, 20);
    
    glPopMatrix();
}

void drawSnowmanTeapot(GLfloat radius)
{
    glColor3f(0.5,0,0.5); // purple
    
    glPushMatrix();
    glTranslatef(0,radius/2,0);
    glScalef(.1,.1,.1);
        glutSolidTeapot(3);
    glPopMatrix();
}

void drawHat(GLfloat radius)
{
    glColor3f(1, 1, 1);
    
    GLfloat xtrans = 0.25 * BOTTOM_RADIUS;
    GLfloat ytrans = 0.5 * BOTTOM_RADIUS;
    GLfloat angle = 45;
    GLfloat topRadius = 0.35;
    
    // left part of hat
    glPushMatrix();
    glTranslatef(xtrans, ytrans, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
        glutSolidTorus(0.1, 0.2, 20, 20);
    glPopMatrix();
    
    // right part of hat
    glPushMatrix();
    xtrans = -xtrans;       // reflection of left part of hat
    angle = -angle;
    glTranslatef(xtrans, ytrans, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
        glutSolidTorus(0.1, 0.2, 20, 20);
    glPopMatrix();

    // top part of hat
    glPushMatrix();
    glTranslatef(0, ytrans, 0);
        glutSolidSphere(topRadius, 10, 10);
//        if (HEADLAMPSTATUS) drawHeadLamp();
    glPopMatrix();

}

void drawHeadLamp()
{
    glColor3f(1, 0, 0);
    double BOTTOM_RADIUS = 1;
    
    // position of light1
    GLfloat ypos = 1.9 * BOTTOM_RADIUS + 0.5;
    GLfloat zpos = AVATAR_POS_Z + 0.3 + 0.1 ;
    GLfloat lightPosition[]={0,ypos,0,1};
    
    GLfloat hx, hy, hz;
    hx = AVATAR_POS_X;
    hy = 1.9 * BOTTOM_RADIUS + 0.5 * cos(head_theta/180 * M_PI);
    hz = AVATAR_POS_Z + 0.4 + 0.4 * sin(head_theta)* sin(head_beta) ;
    glTranslatef(hx, hy, zpos);
    glutSolidSphere(0.1, 5, 5);
    
    GLfloat lightpos[] = {hx,hy,zpos,1};
    // set color of light0
    GLfloat white[] = {1,0,0,0};		      // light color
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
    GLfloat direction[] = {0, -1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);   // set diffuse light color
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);
}

void drawGenieMiddle() {
    // belly
    GLfloat brightPurple[] = {1, 0.53, 0.84};
    glColor3fv(brightPurple);
    
    glPushMatrix();
    glTranslatef(0, BOTTOM_RADIUS, 0);
    glRotatef(90,1,0,0);
        glutSolidTorus(BOTTOM_RADIUS/4, BOTTOM_RADIUS/3, 20, 20);
    glPopMatrix();

    // torso
    GLfloat pink[] = {1, 0.76, 0.77};
    glColor3fv(pink);
    
    glPushMatrix();
    glTranslatef(0,BOTTOM_RADIUS*1.5,0);
    glRotatef(90,1,0,0);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        gluCylinder(quadratic, BOTTOM_RADIUS/4, BOTTOM_RADIUS/2, BOTTOM_RADIUS/2, 20, 20);
        drawArm(true);  // left arm
        drawArm(false); // right arm
    glPopMatrix();
}

void drawGenieBottom()
{
    GLfloat purple[] = {0.8, 0.42, 0.67};
    glColor3fv(purple);
    
    glPushMatrix();
    glTranslatef(0, BOTTOM_RADIUS, 0);
    glRotatef(90,1,0,0);
        glutSolidCone(BOTTOM_RADIUS/2, BOTTOM_RADIUS, 20, 20);
    glPopMatrix();
}

void drawGenieTeapot()
{
    GLfloat yellow[] = {1,1,0};
    glColor3fv(yellow);
    
    glPushMatrix();
    glTranslatef(-1,0.25,0);
    glScalef(.1,.1,.1);
        glutSolidTeapot(3);
    glPopMatrix();
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
    glPushMatrix();
    glTranslatef(headLampX, headLampY, headLampZ);
    glRotatef(head_beta,0,1,0);     // move with head left and right
    glRotatef(head_theta,1,0,0);    // move with head up and down
    
    glColor3f(1, 0, 0);            // red
    glutSolidSphere(0.1, 5, 5);    // star-shaped
    glPopMatrix();
    
    // spot light properties
    GLfloat spotLightPosition[] = {headLampX, headLampY, headLampZ, 1};
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
    glPushMatrix();
    glTranslatef(2, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
        GLUquadric *quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);   // add texture
        gluSphere(quad, 0.5, 20, 20);
    glDisable(GL_TEXTURE_2D);
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
    
    // restore the previously stored modelview matrix
    glPopMatrix();
}

void drawBillboard() {
    billboardBegin();
    
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glBegin(GL_QUADS);
        // bottom left corner
        glTexCoord2f(0, 0);
        glVertex3f(-20, 0, -5);
        // top left corner
        glTexCoord2f(0, 1);
        glVertex3f(-20, 20, -5);
        // top right corner
        glTexCoord2f(1, 1);
        glVertex3f(20, 20, -5);
        // bottom right corner
        glTexCoord2f(1, 0);
        glVertex3f(20, 0, -5);
    glEnd();
    glPopMatrix();
    
    billboardEnd();
}

void drawMirror()
{
    // blend for reflection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPushMatrix();
    glColor4f(1, 1, 1, 0.5);
    glTranslatef(0, 5, 2);
    glScalef(1, -1, 1);
        glBegin(GL_QUADS);
        // bottom left corner
        glVertex3f(-10, 0, -5);
        // top left corner
        glVertex3f(-10, 5, -5);
        // top right corner
        glVertex3f(10, 5, -5);
        // bottom right corner
        glVertex3f(10, 0, -5);
        glEnd();
    glPopMatrix();
    
    // disable reflection
    glDisable(GL_BLEND);
}

void drawGenie() {
    // draw genie's body parts + accessories
    // only when in regular view
    if (!robotPerspective) {
        glPushMatrix();
        glTranslatef(AVATAR_POS_X,0,AVATAR_POS_Z);
        // teapot
        drawGenieTeapot();
        // body
        glRotatef(trick, 0, 1, 0);
        drawGenieBottom();
        drawGenieMiddle();
        drawHead();
        glPopMatrix();
    }
}
