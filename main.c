//
//  main.c
//  spit
//
//  Created by Danny Riordan on 06/07/2014.
//  Copyright (c) 2014 jdr. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "vec.h"

vec v0  = {0,0,0};
vec v   = {0,0,1};

// make sure |dir|=1
typedef struct sphere {vec centre; double radius;} sphere;
typedef struct photon {vec pos; vec dir; double nu;} photon;
typedef struct obstacle {
    photon (*scatter)   (photon,double);
    double (*distance)  (photon);} obstacle;



double sphere_distance(photon g, sphere s){
    // (centre-x)^2=radius^2
    // x=pos+l*dir
    // solve this quadratic system for l, the path length to intesection
    
    double a = dot(g.dir,g.dir); //for clarity, will optimise away
    double b = 2*dot(g.dir,vec_add(g.pos,vec_neg(s.centre)));
    double c = dot(s.centre,s.centre) - s.radius*s.radius - 2*dot(g.pos,s.centre);
    
    double dis = b*b-4*a*c;
    
    printf("scattering dis=%e\n",dis);
    
    // if the ray doesn't intersect the object the system has no real solution
    if (dis<0) return 0;
    
    puts("hit!");
    
    // if there is a solution we want the smallest positive root
    // for the moment assume we are not inside (otherwise pick the other root)
    return (-b-sqrt(dis))/(2*a);
}

photon sphere_scatter(photon g, sphere s,double d){
    // no absorption
    g.pos = vec_add(g.pos, scale(d,g.dir));
    // normal reflection
    g.dir = vec_add(g.pos, vec_neg(s.centre));
    return g;
}

// gcc insists on proper initialiser order!
sphere sphere1 = {.centre = {0,10,0}, .radius = 1};
photon scatter1(photon g, double d){

    return sphere_scatter(g, sphere1, d);
}
double distance1(photon g){
    return sphere_distance(g, sphere1);
}

obstacle obstacles[1]={ {&scatter1,&distance1} };


void spit(photon g){
    int     nearest = -1; //
    double  nearest_d=INFINITY;
    for(int i=0;i<1 /*sizeof obstacles*/ ;i++){
        double d = obstacles[i].distance(g);
        if (d<nearest_d) {nearest=i;nearest_d=d;}
    }
    if (nearest==-1){ puts("photon got lost :(");}
    obstacles[nearest].scatter(g,nearest_d);
}

int main(int argc, const char * argv[]){
    
    spit((photon){v0,v,0});
    
    double m[9]={1,0,0,0,2,0,0,0,3};
    invert(m);
    matrix_print(m);
    

    printf("Hello, World!\n");
    return 0;
}

