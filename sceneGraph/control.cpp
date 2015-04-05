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
    glutAddMenuEntry("Toggle Robot Headlamp", ROBOT_HEADLAMP);
    glutAddMenuEntry("Toggle to Robot Perspective", ROBOT_PERSPECTIVE);
    glutAddMenuEntry("Help with Camera Control", HELP_CAMERA);
    glutAddMenuEntry("Help with Robot Control", HELP_ROBOT);
    
    // Associate a mouse button with menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int item)
{
    switch (item)
    {
        case AMBIENT_LIGHT:
        {
            // toggle
            AMBIENT = !AMBIENT;
            cout << "Toggle ambient light: " << (AMBIENT?"ON":"OFF") << endl;
            
            // enable or disable depending on current state of light
            if (AMBIENT)
            {
                GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.2};
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
            }
            else
            {
                GLfloat no_ambient[] = {0,0,0,0};
                glLightModelfv(GL_LIGHT_MODEL_AMBIENT, no_ambient);
            }
            break;
        }
        case POINT_LIGHT:
        {
            // toggle
            POINTLIGHT = !POINTLIGHT;
            cout << "Toggle point light: " << (POINTLIGHT?"ON":"OFF") << endl;
            
            // enable or disable depending on current state of light
            if (POINTLIGHT) {
                glEnable(GL_LIGHT0);
            }
            else {
                glDisable(GL_LIGHT0);
            }
            break;
        }
        case ROBOT_HEADLAMP:
        {
            HEADLAMPSTATUS = !HEADLAMPSTATUS;
            cout << "Toggle head light: " << (HEADLAMPSTATUS?"ON":"OFF") << endl;
            glutPostRedisplay();
            break;
        }
        case ROBOT_PERSPECTIVE:
        {
            robotPerspective = !robotPerspective;
            cout << "Toggle to robot's perspective: " << (robotPerspective?"ON":"OFF") << endl;
            glutPostRedisplay();
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
            d              spin right\n\
            D              fast spin right\n\
            w              look up\n\
            W              fast look up\n\
            s              look down\n\
            S              fast look down"
            << endl;
            break;
        }
        case HELP_ROBOT:
        {
            cout << "ROBOT control\n\
            \n\
            action         result\n\
            ------         ------\n\
            Left arrow     move left\n\
            Right arrow    move right\n\
            Up arrow       move backward\n\
            Down arrow     move forward\n\
            c              look down\n\
            C              look up\n\
            v              look left\n\
            V              look right\n\
            m              move arms backward\n\
            M              move arms forward\n\
            k              move arms up\n\
            K              move arms down"
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
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//        cout << "Left click with cursor at" << x << " " << y << endl;
}

void motion(int x, int y)
{
//    cout << "Mouse at " << x << " " << y << endl;
//    glutPostRedisplay();
}

// user controls position of robot
void special(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            AVATAR_POS_X--;
            break;
        case GLUT_KEY_RIGHT:
            AVATAR_POS_X++;
            break;
        case GLUT_KEY_DOWN:
            AVATAR_POS_Z--;
            break;
        case GLUT_KEY_UP:
            AVATAR_POS_Z++;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void recalculateCameraPos()
{
    CAMERA_Y = VIEW_RADIUS * cos(phi);
    CAMERA_X = VIEW_RADIUS * sin(phi) * sin(beta);
    CAMERA_Z = VIEW_RADIUS * sin(phi) * cos(beta);
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'c':
            // nod down
            head_theta += 5;
            if (head_theta > 90)
                head_theta = 90;
            break;
        case 'C':
            // nod up
            head_theta -= 5;
            if (head_theta < -90)
                head_theta = -90;
            break;
        case 'v':
            // head turn left
            head_beta -= 5;
            break;
        case 'V':
            // head turn right
            head_beta += 5;
            break;
        case 'Z':
            // zoom in
            VIEW_RADIUS -=3;
            if (VIEW_RADIUS < 0)
                VIEW_RADIUS = 0 + EPSLON;
            recalculateCameraPos();
            cout << "zooming in." << endl;
            break;
        case 'z':
            // zoom out
            VIEW_RADIUS += 3;
            recalculateCameraPos();
            cout << "zooming out." << endl;
            break;
        case 'a':
            // camera spin left
            beta -= (double)CAMERA_SPIN/ (double)windowWidth;
            recalculateCameraPos();
            cout << "spin left: " << beta << endl;
            break;
        case 'A':
            // camera spin left
            beta -= (double)CAMERA_BIG_SPIN/ (double)windowWidth;
            recalculateCameraPos();
            cout << "fast spin left: " << beta << endl;
            break;
        case 'd':
            // camera spin right
            beta += (double)CAMERA_SPIN/ (double)windowWidth;
            recalculateCameraPos();
            cout << "spin right: " << beta << endl;
            break;
        case 'D':
            // camera spin right
            beta += (double)CAMERA_BIG_SPIN/ (double)windowWidth;
            recalculateCameraPos();
            cout << "fast spin right: " << beta << endl;
            break;
        case 'w':
            // camera look up
            phi -=(double)CAMERA_SPIN/ (double)windowHeight;
            if (phi < 0)
                phi = 0 + EPSLON;
            recalculateCameraPos();
            cout << "look up: " << phi << endl;
            break;
        case 'W':
            // camera look up
            phi -=(double)CAMERA_BIG_SPIN/ (double)windowHeight;
            if (phi < 0)
                phi = 0 + EPSLON;
            recalculateCameraPos();
            cout << "fast look up: " << phi << endl;
            break;
        case 's':
            phi += (double)CAMERA_SPIN/ (double)windowHeight;
            if (phi > M_PI)
                phi = M_PI;
            recalculateCameraPos();
            cout << "look down: " << phi << endl;
            break;
        case 'S':
            phi +=(double)CAMERA_BIG_SPIN/ (double)windowHeight;
            if (phi > M_PI)
                phi = M_PI;
            recalculateCameraPos();
            cout << "fast look down: " << phi << endl;
            break;
        case 'm':
            WAVE_SWIM -= 5;
            break;
        case 'M':
            WAVE_SWIM += 5;
            break;
        case 'k':
            WAVE_UP_DOWN -=5;
            break;
        case 'K':
            WAVE_UP_DOWN +=5;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
