#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "MATH3D.h"
#include <stdio.h>

struct camera {
    vec3 position;
    vec3 Front = {0.0, 0.0, 1.0};
    vec3 Up = {0.0, 1.0, 0.0};
    vec3 Right = {1.0, 0.0, 0.0};
    vec3 WorldUp = {0.0, 1.0, 0.0};
}

mat4 getCameraView()

#endif