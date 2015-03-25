//
//  main.hpp
//  sceneGraph
//
//  Created by ANGELA ZHOU on 3/22/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#ifndef sceneGraph_main_hpp
#define sceneGraph_main_hpp
#include "common.h"

// window dimensions
const int windowWidth=600;
const int windowHeight=600;
const double CAMERA_SPIN = 90;
const double CAMERA_BIG_SPIN = 420;


// position of snowman
extern double snowmanX;
extern double snowmanZ;
extern double CAMERA_X;
extern double CAMERA_Z;
extern double CAMERA_Y;

// nod angle
extern double theta;
extern double phi;
extern double beta;
extern bool AMBIENT;
extern bool POINTLIGHT;


void display(void);
void reshape(int width, int height);
void init();
void menu(int);
void keyboard(unsigned char key, int x, int y);

void drawSnowman();

#endif
