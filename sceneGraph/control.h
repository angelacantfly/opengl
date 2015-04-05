//
//  control.h
//  sceneGraph
//
//  Created by ANGELA ZHOU on 3/22/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#ifndef __sceneGraph__control__
#define __sceneGraph__control__

#include <stdio.h>
#include "common.h"

// menu items
enum MENU_TYPE
{
    AMBIENT_LIGHT,
    POINT_LIGHT,
    ROBOT_HEADLAMP,
    ROBOT_PERSPECTIVE,
    HELP_CAMERA,
    HELP_ROBOT
};

void make_menu();
void menu(int);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void special(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);

#endif /* defined(__sceneGraph__control__) */
