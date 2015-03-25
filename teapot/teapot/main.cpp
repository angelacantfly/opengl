//
//  main.cpp
//  teapot
//
//  Created by ANGELA ZHOU on 3/24/15.
//  Copyright (c) 2015 ANGELA ZHOU. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif


void wall1(float thickness)
{
    glPushMatrix();
    glTranslatef(100,100,0);
    glRotatef(90,1,0,0);
    glScalef(thickness,1,1);
    glutSolidCube(100);
    glPopMatrix();
}
void wall2(float thickness)
{
    glPushMatrix();
    glTranslatef(150,100,-50);
    glScalef(1,1,thickness);
    glutSolidCube(100);
    glPopMatrix();
}
void floor(float thickness)
{
    glPushMatrix();
    glTranslatef(150,50,0);
    glScalef(1,thickness,1);
    glutSolidCube(100);
    glPopMatrix();
}
void leg(float thickness)
{
    glPushMatrix();
    glScalef(thickness,.5,thickness);
    glutSolidCube(100);
    glPopMatrix();
}
void tableTop(float thickess)
{
    glPushMatrix();
    glTranslatef(150,100,0);
    glScalef(.5,thickess,.5);
    glutSolidCube(100);
    glPopMatrix();
}
void table()
{
    tableTop(.05);
    
    glPushMatrix();
    glTranslatef(125,75,-25);
    leg(.05);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(175,75,-25);
    leg(.05);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(175,75,25);
    leg(.05);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(125,75,25);
    leg(.05);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(150,110,0);
    glScalef(.1,.1,.1);
    glutSolidTeapot(100);
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float pos[] = {200,200,0};
    float dif[] = {.3,.3,.3,3};
    float spe[] = {1,1,1,1};
    float amb[] = {1,1,1,0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spe);
    
    glTranslatef(50,50,0);
    glRotatef(30,1,0,0);
    glRotatef(-30,0,1,0);
    wall1(.05);
    wall2(.05);
    floor(0.05);
    table();
    
    glFlush();
}
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,400,0,400,-400,400);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("woot");
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    
    glShadeModel(GL_SMOOTH);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
    
    
}
