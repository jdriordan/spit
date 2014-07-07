#include <stdio.h>
#include <math.h>
#include <string.h>

#include "plane.h"

photon plane_scatter(photon g, plane s,double d){
	puts("scattering from plane");
    // no absorption
    g.pos = vec_add(g.pos, scale(d,g.dir));
    // normal reflection
    // $$r = d - {2 d \cdot n\over \|n\|^2}n$$
    vec normal = cross(s.dir1,s.dir2);
    g.dir = vec_add(g.dir,
					scale(2*dot(g.dir,normal)/dot(normal,normal),
							vec_neg(normal)));
    return g;
}


double plane_distance(photon g, plane s){
    // x=pos+l*dir  (for both plane and ray)
    // solve this linear system for l, the path length to intesection
    printf("calculating for plane");
	int n = 3;
    double hit[n];
    double A[9] = {
	s.dir1.x,s.dir1.y,s.dir1.z,
	s.dir2.x,s.dir2.y,s.dir2.z,
	g.dir.x ,g.dir.y ,g.dir.z };


	matrix_print(A);
    solveAxy(A, vec_add(g.pos,vec_neg(s.x0)), hit);
    
    puts("hit plane!");
    
    // if there is a solution we want the smallest positive root
    // for the moment assume we are not inside (otherwise pick the other root)
    return hit[2];//(-b-sqrt(dis))/(2*a);
}
