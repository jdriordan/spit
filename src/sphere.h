#pragma once

#include "rays.h"

typedef struct sphere {vec centre; double radius;} sphere;

photon sphere_scatter(photon g, sphere s,double d);
double sphere_distance(photon g, sphere s);
