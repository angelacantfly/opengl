//
//  shadow.h
//  sceneGraph
//
//  Created by ANGELA ZHOU on 4/5/15.
//  Copyright (c) 2015 Maureen Naval. All rights reserved.
//

#ifndef __sceneGraph__shadow__
#define __sceneGraph__shadow__

#include <stdio.h>
#include "main.h"

void shadowMatrixPointLight(GLfloat shadowMat[16],
                            GLfloat groundplane[4],
                            GLfloat lightpos[4]);

#endif /* defined(__sceneGraph__shadow__) */
