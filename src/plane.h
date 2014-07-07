#pragma once

#include "rays.h"

// a plane (segment) has a the following corners:
//    {x0, x0+dir1, x0+dir2, x0+dir1+dir2}
// maybe it would better be called a parallelogram

typedef struct plane {vec x0; vec dir1; vec dir2;} plane;

photon plane_scatter(photon g, plane p,double d);
double plane_distance(photon g, plane p);
