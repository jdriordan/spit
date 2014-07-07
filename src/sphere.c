#include <stdio.h>
#include <math.h>

#include "sphere.h"

photon sphere_scatter(photon g, sphere s,double d){
    // no absorption
    g.pos = vec_add(g.pos, scale(d,g.dir));
    // normal reflection
    g.dir = vec_add(g.pos, vec_neg(s.centre));
    return g;
}


double sphere_distance(photon g, sphere s){
    // (centre-x)^2=radius^2
    // x=pos+l*dir
    // solve this quadratic system for l, the path length to intersection
    
    double a = dot(g.dir,g.dir); //for clarity, will optimise away
    double b = 2*dot(g.dir,vec_add(g.pos,vec_neg(s.centre)));
    double c = dot(s.centre,s.centre) - s.radius*s.radius - 2*dot(g.pos,s.centre);
    
    double discriminant = b*b-4*a*c;
    
    printf("sphere distance dis=%e\n",discriminant);
    
    // if the ray doesn't intersect the object the system has no real solution
    if (discriminant<0) return 0;
    
    puts("hit sphere!");
    
    // if there is a solution we want the smallest positive root
    // for the moment assume we are not inside (otherwise pick the other root)
    return (-b-sqrt(discriminant))/(2*a);
}
