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
            cout << "How to use the camera control: " << endl;
            break;
        }
        default:
        {       /* Nothing */       }
            break;
    }
    
    glutPostRedisplay();
    
    return;
}

