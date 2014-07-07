#pragma once

#include "vec.h"

// make sure |dir|=1
typedef struct photon {vec pos; vec dir; double nu;} photon;

typedef struct obstacle {
    photon (*scatter)   (photon,double);
    double (*distance)  (photon);} obstacle;
