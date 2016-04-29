#pragma once

#include <math.h>
#include <assert.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062f
#endif

// Pre-Done Math (PDM)
#define PDM_PI_DIV_180	0.0174532925199433f
#define PDM_180_DIV_PI	57.2957795130824f

#define ToRadian(x) ((x) * (float)PDM_PI_DIV_180)
#define ToDegree(x) ((x) * (float)PDM_180_DIV_PI)