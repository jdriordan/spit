//
//  vec.h
//  spit
//
//  Created by Danny Riordan on 06/07/2014.
//  Copyright (c) 2014 jdr. All rights reserved.
//

typedef struct vec {double x; double y; double z;} vec;

vec vec_add(vec a, vec b);
vec vec_neg(vec a);
vec scale(double d, vec v);
double dot(vec a, vec b);

void invert(double *);
void matrix_print(double *);