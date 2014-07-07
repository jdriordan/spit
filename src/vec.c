#include <string.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>

#include "vec.h"

    // |double m0[9]={1,0,0,0,2,0,0,0,3};
    // |double * m = malloc(9*sizeof(double));
    // |#include <string.h>
    // |m=matrix2array(invert(array2matrix(m0)));
    // |matrix_print(m);
    // solveAxy(m0,v3,x);


vec vec_add(vec a, vec b){
    return (vec){a.x+b.x,a.y+b.y,a.z+b.z};
}

vec vec_neg(vec a){
    return (vec){-a.x,-a.y,-a.z};
}

double dot(vec a, vec b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

vec cross(vec a, vec b){
	return (vec){
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x};
}

vec scale(double d, vec v){
    return (vec){d*v.x,d*v.y,d*v.z};
}

gsl_matrix * array2matrix(double * a){
	//gsl_matrix_view m  = gsl_matrix_view_array (a, 3,3);
	int n = 3;
	gsl_matrix * m = gsl_matrix_alloc (n, n);
	memcpy(m->data,a,n*n*sizeof(double));
	return m;
}

// you can save memory here
double * matrix2array(gsl_matrix * m){
	int n=3;
	double * matrix = malloc(n*n*sizeof(double));
	memcpy(matrix,m->data,n*n*sizeof(double));
	return matrix;
}

gsl_matrix * invert(gsl_matrix * m)
{
	// Define the dimension n of the matrix
	// and the signum s (for LU decomposition)
	int n = 3;
	int s;
    
	// Define all the used matrices
	
	gsl_matrix * inverse = gsl_matrix_alloc (n, n);
	gsl_permutation * perm = gsl_permutation_alloc (n);
    
    
	// Make LU decomposition of matrix m
	gsl_linalg_LU_decomp (m, perm, &s);
    
	// Invert the matrix m
	gsl_linalg_LU_invert (m, perm, inverse);

	// maybe free manually and don't guess about GC
	return inverse;
}

// solve the 3D equation Ax=y for vector x, given
// vector y and matrix A, returning an array of the solution
void solveAxy(double * A, vec y, double * x){
	int n=3;
	
	gsl_vector *gx = gsl_vector_alloc (n);
	gsl_matrix *gA = array2matrix(A);

	gsl_vector * gy = gsl_vector_alloc(n);
	memcpy(gy->data,&y,n*sizeof(double));

	int sign;
	gsl_permutation * p = gsl_permutation_alloc (n);
	gsl_linalg_LU_decomp (gA, p, &sign);
	gsl_linalg_LU_solve(gA, p, gy, gx);
	//gsl_vector_fprintf (stdout, gx, "%g");
	memcpy(x,gx->data,n*sizeof(double));
}

void matrix_print(double * m){
    printf("\n\
/%f %f %f\\\n\
|%f %f %f|\n\
\\%f %f %f/\n",
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
