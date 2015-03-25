//
//  control.cpp
//  sceneGraph
//
//  Created by ANGELA ZHOU on 3/22/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#include "control.h"
#include "main.h"
#include <iostream>
using namespace std;

void make_menu()
{
    // Create a menu
    glutCreateMenu(menu);
    
    // Add menu items
    glutAddMenuEntry("Toggle Ambient Light", AMBIENT_LIGHT);
    glutAddMenuEntry("Toggle Point Light", POINT_LIGHT);
    glutAddMenuEntry("Help with camera control", HELP_CAMERA);
    
    // Associate a mouse button with menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

void menu(int item)
{
    switch (item)
    {
            
        case AMBIENT_LIGHT:
        {
            AMBIENT = 1 - AMBIENT;
            cout << "Toggle ambient light: " << (AMBIENT?"ON":"OFF") << endl;
            break;
        }
        case POINT_LIGHT:
        {
            POINTLIGHT = 1 - POINTLIGHT;
            cout << "Toggle point light: " << (POINTLIGHT?"ON":"OFF") << endl;
            
            float pointLight = 0;
            if (POINTLIGHT) pointLight = 1;
            GLfloat lightPosition[]={3,1,1,pointLight};
            glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
            
            break;
        }
        case HELP_CAMERA:
        {
            cout << "Camera control\n\
            \n\
            action         result\n\
            ------         ------\n\
            z              zoom out\n\
            Z      		   zoom in\n\
            a          	   spin left\n\
            A    		   fast spin left\n\
            s              spin right\n\
            S              fast spin right"
            << endl;
            break;
        }
        default:
        {       /* Nothing */       }
            break;
    }
    
    glutPostRedisplay();
    
    return;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        cout << "Left click with cursor at" << x << " " << y << endl;
}

void motion(int x, int y)
{
    cout << "Mouse at " << x << " " << y << endl;
    phi += (double)x/ (double)windowWidth;
    beta += (double)y/ (double)windowHeight;
    glutPostRedisplay();
}

// user controls position of snowman
void special(int key, int x, int y)
{
    
    switch (key) {
        case GLUT_KEY_LEFT:
            snowmanX--;
            break;
        case GLUT_KEY_RIGHT:
            snowmanX++;
            break;
        case GLUT_KEY_DOWN:
            snowmanZ--;
            break;
        case GLUT_KEY_UP:
            snowmanZ++;
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

// user controls snowman nod
void keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
        case 'c':
            theta += 5;
            break;
        case 'v':
            theta -= 5;
            break;
        case 'Z':
            // zoom in
            CAMERA_Z = CAMERA_Z - 1.0;
            cout << "zooming in." << endl;
            break;
        case 'z':
            // zoom out
            CAMERA_Z = CAMERA_Z + 1.0;
            cout << "zooming in." << endl;
            break;
        case 'a':
            // camera spin left
            phi -= (double)CAMERA_SPIN/ (double)windowWidth;
            CAMERA_X = 20*sin(phi*3.14/180.0);
            CAMERA_Z = 20*cos(phi*3.14/180.0);
            cout << "spin left: " << phi << endl;
            break;
        case 'A':
            // camera spin left
            phi -= (double)CAMERA_BIG_SPIN/ (double)windowWidth;
            CAMERA_X = 20*sin(phi*3.14/180.0);
            CAMERA_Z = 20*cos(phi*3.14/180.0);
            cout << "fast spin left: " << phi << endl;
            break;
        case 's':
            // camera spin right
            phi += (double)CAMERA_SPIN/ (double)windowWidth;
            CAMERA_X = 20*sin(phi*3.14/180.0);
            CAMERA_Z = 20*cos(phi*3.14/180.0);
            cout << "spin right: " << phi << endl;
            break;
        case 'S':
            // camera spin right
            phi += (double)CAMERA_BIG_SPIN/ (double)windowWidth;
            CAMERA_X = 20*sin(phi*3.14/180.0);
            CAMERA_Z = 20*cos(phi*3.14/180.0);
            cout << "fast spin right: " << phi << endl;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
