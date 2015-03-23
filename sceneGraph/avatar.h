//
//  avatar.h
//  sceneGraph
//
//  Created by ANGELA ZHOU on 3/22/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#ifndef __sceneGraph__avatar__
#define __sceneGraph__avatar__

#include <stdio.h>
#include "main.h"

void drawBottom();
void drawMiddle();
void drawArm(bool x);
void drawHead();
void drawEye(bool x);
void drawFloor();
void tileFloor(double x1, double y1, double x2, double y2, double r, double g, double b);

#endif /* defined(__sceneGraph__avatar__) */
