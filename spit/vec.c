//
//  vec.c
//  spit
//
//  Created by Danny Riordan on 06/07/2014.
//  Copyright (c) 2014 jdr. All rights reserved.
//

#include <string.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>


#include "vec.h"

vec vec_add(vec a, vec b){
    return (vec){a.x+b.x,a.y+b.y,a.z+b.z};
}

vec vec_neg(vec a){
    return (vec){-a.x,-a.y,-a.z};
}

double dot(vec a, vec b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

vec scale(double d, vec v){
    return (vec){d*v.x,d*v.y,d*v.z};
}


void invert(double *matrix)
{
	// Define the dimension n of the matrix
	// and the signum s (for LU decomposition)
	int n = 3;
	int s;
    
	// Define all the used matrices
	gsl_matrix * m = gsl_matrix_alloc (n, n);
	gsl_matrix * inverse = gsl_matrix_alloc (n, n);
	gsl_permutation * perm = gsl_permutation_alloc (n);
    
	memcpy(m->data,matrix,n*n*sizeof(double));
    
	// Make LU decomposition of matrix m
	gsl_linalg_LU_decomp (m, perm, &s);
    
	// Invert the matrix m
	gsl_linalg_LU_invert (m, perm, inverse);
    
    memcpy(matrix,inverse->data,n*n*sizeof(double));
}

void matrix_print(double * m){
    printf("\
[%f %f %f]\n\
[%f %f %f]\n\
[%f %f %f]\n",
           m[0],
           m[1],
           m[2],
           m[3],
           m[4],
           m[5],
           m[6],
           m[7],
           m[8]);
//mapM_ putStrLn $ ["m["++show i++"],"|i<-[0..8]]
           }