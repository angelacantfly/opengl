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
const double CAMERA_SPIN = 10;
const double CAMERA_BIG_SPIN = 30;
const double EPSLON = 0.00001;

// position of snowman
extern double AVATAR_POS_X;
extern double AVATAR_POS_Z;
extern double AVATAR_POS_Y;
extern const double AVATAR_EYE_POS;

// position of camera (user controlled)
extern double CAMERA_X;
extern double CAMERA_Z;
extern double CAMERA_Y;
extern double VIEW_RADIUS;

// position of head lamp
extern double HEADLAMPHEIGHT;

// arm positions
extern double WAVE_SWIM;    // front to back
extern double WAVE_UP_DOWN; // up and down

// robot control
extern double head_theta;    // head up and down
extern double head_beta;     // head left and right

// camera control
extern double phi;
extern double beta;

// toggle lights
extern bool AMBIENT;
extern bool POINTLIGHT;
extern bool HEADLAMPSTATUS;

// toggle view
extern bool robotPerspective;

void display(void);
void reshape(int width, int height);
void init();
void menu(int);
void keyboard(unsigned char key, int x, int y);

// robots
void drawSnowman();
void drawGenie();

void drawSpotLight();

<<<<<<< HEAD

// billboard
void billboardBegin();
void billboardEnd();
void drawBillboard();

// texture mapping
bool LoadGLTextures(char* fname);
=======
>>>>>>> parent of 4305b55... billboard

#endif
