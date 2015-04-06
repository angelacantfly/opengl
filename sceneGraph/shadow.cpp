//
//  shadow.cpp
//  sceneGraph
//
//  Created by ANGELA ZHOU on 4/5/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#include "shadow.h"

/* Create a matrix that will project the desired shadow. */
void shadowMatrixPointLight(GLfloat shadowMat[16],
                       GLfloat groundplane[4],
                       GLfloat lightpos[4])
{
    GLfloat dot;
    
    
    /* Find dot product between light position vector and ground plane normal. */
    dot = groundplane[0] * lightpos[0] +
    groundplane[1] * lightpos[1] +
    groundplane[2] * lightpos[2] +
    groundplane[3] * lightpos[3];
    
    shadowMat[0] = dot - lightpos[0] * groundplane[0];
    shadowMat[4] = 0.f - lightpos[0] * groundplane[1];
    shadowMat[8] = 0.f - lightpos[0] * groundplane[2];
    shadowMat[12] = 0.f - lightpos[0] * groundplane[3];
    
    shadowMat[1] = 0.f - lightpos[1] * groundplane[0];
    shadowMat[5] = dot - lightpos[1] * groundplane[1];
    shadowMat[9] = 0.f - lightpos[1] * groundplane[2];
    shadowMat[13] = 0.f - lightpos[1] * groundplane[3];
    
    shadowMat[2] = 0.f - lightpos[2] * groundplane[0];
    shadowMat[6] = 0.f - lightpos[2] * groundplane[1];
    shadowMat[10] = dot - lightpos[2] * groundplane[2];
    shadowMat[14] = 0.f - lightpos[2] * groundplane[3];
    
    shadowMat[3] = 0.f - lightpos[3] * groundplane[0];
    shadowMat[7] = 0.f - lightpos[3] * groundplane[1];
    shadowMat[11] = 0.f - lightpos[3] * groundplane[2];
    shadowMat[15] = dot - lightpos[3] * groundplane[3];
    
    
}