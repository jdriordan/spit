#include <stdio.h>
#include <math.h>

#include "vec.h"
#include "sphere.h"
#include "plane.h"
#include "rays.h"

vec v0  = {0,0,0};
vec v   = {0,1,1};

// gcc insists on proper initialiser order!
sphere sphere0 = {.centre = {0,10,0}, .radius = 1};
photon scatter0(photon g, double d){

    return sphere_scatter(g, sphere0, d);
}
double distance0(photon g){
    return sphere_distance(g, sphere0);
}

plane plane1 = {.x0   = {0,5,0},
				.dir1 = {1,0,0},
				.dir2 = {0,0,1}};
photon scatter1(photon g, double d){

    return plane_scatter(g, plane1, d);
}
double distance1(photon g){
    return plane_distance(g, plane1);
}

obstacle obstacles[2]={	{&scatter0,&distance0},
						{&scatter1,&distance1} };


photon spit(photon g){
    int     nearest = -1; //
    double  nearest_d=INFINITY;
    for(int i=0;i<2 /*sizeof obstacles*/ ;i++){
        double d = obstacles[i].distance(g);
        if (d<nearest_d) {nearest=i;nearest_d=d;}
    }
    if (nearest==-1){ puts("photon got lost :(");}
    printf("scattering from %d",nearest);
    obstacles[nearest].scatter(g,nearest_d);
    return g;
}

int main(){
	
	photon g=spit((photon){v0,v,0});
    for (int i=0;i<3;i++){
    g=spit(g);
	}
    
    return 0;
}

