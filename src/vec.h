#pragma once

#include <gsl/gsl_matrix.h>


// perhaps double[3] would be better here
typedef struct vec {double x; double y; double z;} vec;

vec vec_add(vec a, vec b);
vec vec_neg(vec a);
vec scale(double d, vec v);
double dot(vec a, vec b);
vec cross(vec a, vec b);

gsl_matrix * array2matrix(double * a);
double * matrix2array(gsl_matrix * m);

gsl_matrix * invert(gsl_matrix * m);
void solveAxy(double * A, vec y, double * x);
void matrix_print(double *);
