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
GLfloat BOTTOM_RADIUS = 1;
GLfloat EYE_RADIUS = 0.25;

void drawBottom(){
    GLfloat red[] = {1,1,1};
    glColor3fv(red);
    
    glPushMatrix();
    glTranslatef(0,BOTTOM_RADIUS,0);
        glutSolidSphere(BOTTOM_RADIUS, 20, 20);
    glPopMatrix();

}

void drawFloor() {
    glNormal3f(0, 1, 0);
    double originx = -5;
    double originy = -5;
    int color = 0;
    glRotatef(-90,1,0,0);
    for (int row = 0 ; row < 5; ++row)
        for (int col = 0; col < 5; ++ col)
        {
            color ++;
            tileFloor(originx + 2 * row, originy + 2 * col, originx + 2 * (row + 1), originy + 2* (col + 1), color%2, color%2, color%2);
        }
    glRotatef(90,1,0,0);
}

void tileFloor(double x1, double y1, double x2, double y2, double r, double g, double b)
{
    glColor3f(r, g, b);
    glRectf(x1, y1, x2, y2);
}

void drawMiddle() {
    GLfloat red[] = {1,1,1};
    glColor3fv(red);
    
    glPushMatrix();
    glTranslatef(0,2*BOTTOM_RADIUS,0);
        glutSolidSphere(BOTTOM_RADIUS*0.75, 20, 20);
    glPopMatrix();
    
    drawArm(true); // left arm
    drawArm(false);// right arm
}

void drawArm(bool isLeft) {
    GLfloat white[] = {1,1,1};
    glColor3fv(white);
    
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
    glRotatef(-WAVE_UP_DOWN , 1, 0, 0);
    glRotatef(-WAVE_SWIM * wave_direction, 0, 1, 0);
    glRotatef(-90,0,1,0);
    
    if (isLeft) glRotatef(-180, 0, 1, 0);
    
    if (isLeft) glTranslatef(0.3,0.1,0);
    else    glTranslatef(-0.3,0.1,0);
    
    glPopMatrix();
}

void drawHead() {
    GLfloat red[] = {1,1,1};
    glColor3fv(red);
    glPushMatrix();
    glTranslatef(0,1.9*BOTTOM_RADIUS,0);
    glRotatef(theta,1,0,0);
    glRotatef(beta,0,1,0);
        glutSolidSphere(BOTTOM_RADIUS*0.5, 20, 20); // head
        drawHat(BOTTOM_RADIUS);                     // hat
        drawEye(true);                              // left eye
        drawEye(false);                             // right eye
        drawEarring(true);                          // left earring
        drawEarring(false);                         // right earring
    glRotatef(-theta, 1, 0, 0);
    glRotatef(-beta,0,1,0);
    glTranslatef(0,-1.9*BOTTOM_RADIUS,0);
    glPopMatrix();
}

void drawEye(bool isLeft) {
    GLfloat black[] = {0,0,0};
    glColor3fv(black);
    
    glPushMatrix();
    
    // position for each eye
    if (isLeft) glTranslatef(-0.25,0,0.5);
    else    glTranslatef(.25,0,0.5);
    
    // eye
    glutSolidSphere(EYE_RADIUS*0.5, 20, 20);
    
    glPopMatrix();
}

void drawEarring(bool isLeft)
{
    GLfloat yellow[] = {1,1,0};
    glColor3fv(yellow);
    
    glPushMatrix();
    
    // position for each eye
    if (isLeft) glTranslatef(-0.5,-0.25,0);
    else    glTranslatef(.5,-0.25,0);
    
    // eye
    glRotatef(90,0,1,0);
    glutSolidTorus(EYE_RADIUS/4, EYE_RADIUS/2, 20, 20);
    glRotatef(-90,0,1,0);
    
    glPopMatrix();
}

void drawTeapot(GLfloat radius)
{
    GLfloat purple[] = {0.5,0,0.5};
    glColor3fv(purple);
    glPushMatrix();
    glTranslatef(0,radius/2,0);
    glScalef(.1,.1,.1);
        glutSolidTeapot(3);
    glPopMatrix();
}

void drawHat(GLfloat radius)
{
    glColor3f(1, 1, 1);
    
    GLfloat xtrans = 0.25;
    GLfloat ytrans = 0.5;
    GLfloat angle = 45;
    GLfloat topRadius = 0.35;
    
    // left part of hat
    glTranslatef(xtrans, ytrans, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
        glutSolidTorus(0.1, 0.2, 20, 20);
    glRotatef(-angle, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-xtrans,-ytrans,0);
    
    // right part of hat
    xtrans = -xtrans;       // reflection of left part of hat
    angle = -angle;
    glTranslatef(xtrans, ytrans, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
        glutSolidTorus(0.1, 0.2, 20, 20);
    glRotatef(-angle, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-xtrans,-ytrans,0);

    // top part of hat
    glTranslatef(0, ytrans, 0);
        glutSolidSphere(topRadius, 10, 10);
        drawHeadLamp(topRadius);
    glTranslatef(0, -ytrans, 0);
    
    
}

void drawHeadLamp(GLfloat ztrans)
{
    glColor3f(1, 1, 0);             // yellow gem
    glTranslatef(0, 0, ztrans);
        glutSolidSphere(0.1, 5, 5); // star-shaped
    glTranslatef(0, 0, -ztrans);
    
//    // enable light1 and lighting
//    glEnable(GL_LIGHT1);
//    
//    // position of light1
//    GLfloat ypos = 3 * BOTTOM_RADIUS + 0.5;
////    ypos += 30.0;
//    GLfloat zpos = AVATAR_POS_Z + 0.5 + 0.2;
////    zpos = AVATAR_POS_Z + 3;
//    GLfloat lightPosition[]={static_cast<GLfloat>(AVATAR_POS_X),ypos,zpos,1};
//    
//    // set color of light0
//    GLfloat ambientWhite[] = {0.2,0.2,0.2,0.2};
//    GLfloat white[] = {1,1,0,0};		      // light color
//    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
////    GLfloat direction[] = {0, 0, 1.0};
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);   // set diffuse light color
//    glLightfv(GL_LIGHT1, GL_SPECULAR, white);  // set specular light color
//    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientWhite);
////    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);

}

void drawGenieMiddle() {
    // belly
    glTranslatef(0, BOTTOM_RADIUS, 0);
    glRotatef(90,1,0,0);
        glutSolidTorus(BOTTOM_RADIUS/4, BOTTOM_RADIUS/3, 20, 20);
    glRotatef(-90,1,0,0);
    glTranslatef(0, -BOTTOM_RADIUS, 0);

    // torso
    glTranslatef(0,BOTTOM_RADIUS*1.5,0);
    glRotatef(90,1,0,0);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        gluCylinder(quadratic, BOTTOM_RADIUS/4, BOTTOM_RADIUS/2, BOTTOM_RADIUS/2, 20, 20);
    glRotatef(-90,1,0,0);
        drawArm(true);  // left arm
        drawArm(false); // right arm
    glTranslatef(0,-BOTTOM_RADIUS*1.5,0);
}

void drawGenieBottom()
{
    glColor3f(1, 1, 1);
    
    glTranslatef(0, BOTTOM_RADIUS, 0);
    glRotatef(90,1,0,0);
        glutSolidCone(BOTTOM_RADIUS/2, BOTTOM_RADIUS, 20, 20);
    glRotatef(-90,1,0,0);
    glTranslatef(0,-BOTTOM_RADIUS, 0);
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

