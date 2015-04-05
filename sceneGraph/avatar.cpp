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
    double originx = -5;
    double originy = -5;
    int color = 0;
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glNormal3f(0,0,1);
    for (int row = 0 ; row < 5; ++row)
        for (int col = 0; col < 5; ++ col)
        {
            color ++;
            tileFloor(originx + 2 * row, originy + 2 * col, originx + 2 * (row + 1), originy + 2* (col + 1), color%2, color%2, color%2);
        }
    glRotatef(90,1,0,0);
    glPopMatrix();
}

void tileFloor(double x1, double y1, double x2, double y2, double r, double g, double b)
{
    glColor3f(r, g, b);
    glRectf(x1, y1, x2, y2);
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
    GLfloat white[] = {1,1,1};
    glColor3fv(white);
    
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
    glRotatef(-head_theta, 1, 0, 0);
    glRotatef(-head_beta,0,1,0);
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
    
    // position of each eye
    if (isLeft) glTranslatef(-0.5,-0.25,0);
    else    glTranslatef(.5,-0.25,0);
    
    // eye
    glRotatef(90,0,1,0);
    glutSolidTorus(EYE_RADIUS/4, EYE_RADIUS/2, 20, 20);
    glRotatef(-90,0,1,0);
    
    glPopMatrix();
}

void drawSnowmanTeapot(GLfloat radius)
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
    glRotatef(-angle, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-xtrans,-ytrans,0);
    glPopMatrix();
    
    // right part of hat
    glPushMatrix();
    xtrans = -xtrans;       // reflection of left part of hat
    angle = -angle;
    glTranslatef(xtrans, ytrans, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
        glutSolidTorus(0.1, 0.2, 20, 20);
    glRotatef(-angle, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-xtrans,-ytrans,0);
    glPopMatrix();

    // top part of hat
    glPushMatrix();
    glTranslatef(0, ytrans, 0);
        glutSolidSphere(topRadius, 10, 10);
//        if (HEADLAMPSTATUS) drawHeadLamp();
    glTranslatef(0, -ytrans, 0);
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
    cout << "head_beta : " << head_beta << endl;
    cout << "head_theta : " << head_theta << endl;
    //    glTranslatef(static_cast<GLfloat>(AVATAR_POS_X), ypos, zpos);
    glTranslatef(hx, hy, zpos);
    glutSolidSphere(0.1, 5, 5);
    
    GLfloat lightpos[] = {hx,hy,zpos,1};
    // set color of light0
    GLfloat ambientWhite[] = {0.2,0.2,0.2,0.2};
    GLfloat white[] = {1,0,0,0};		      // light color
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2}; // ambient
    GLfloat direction[] = {0, -1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);   // set diffuse light color
    //glLightfv(GL_LIGHT1, GL_SPECULAR, white);  // set specular light color
    //glLightfv(GL_LIGHT1, GL_AMBIENT, ambientWhite);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);

//    glPushMatrix();
//    glColor3f(1, 1, 0);             // yellow gem
//    glTranslatef(0, 0, ztrans);
//        glutSolidSphere(0.1, 5, 5); // star-shaped
//    glTranslatef(0, 0, -ztrans);
//    glPopMatrix();

}

void drawGenieMiddle() {
    // belly
    GLfloat brightPurple[] = {1, 0.53, 0.84};
    glColor3fv(brightPurple);
    
    glPushMatrix();
    glTranslatef(0, BOTTOM_RADIUS, 0);
    glRotatef(90,1,0,0);
        glutSolidTorus(BOTTOM_RADIUS/4, BOTTOM_RADIUS/3, 20, 20);
    glRotatef(-90,1,0,0);
    glTranslatef(0, -BOTTOM_RADIUS, 0);
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
    glRotatef(-90,1,0,0);
        drawArm(true);  // left arm
        drawArm(false); // right arm
    glTranslatef(0,-BOTTOM_RADIUS*1.5,0);
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
    glRotatef(-90,1,0,0);
    glTranslatef(0,-BOTTOM_RADIUS, 0);
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

