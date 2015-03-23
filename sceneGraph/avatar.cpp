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
    //    glRotatef(-45,1,0,0);
    glRectf(x1, y1, x2, y2);
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
