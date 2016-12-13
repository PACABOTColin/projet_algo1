#include "nuage.h"
#include "GfxLib.h"

nuage initialiseNuage(nuage cloud) {
	if(cloud.nb < DIM) {
		cloud.nb++;
		
		cloud.x[cloud.nb-1] = abscisseSouris();
		cloud.y[cloud.nb-1] = ordonneeSouris();
	}

	return cloud;
}

void dessineNuage(nuage cloud) {
	epaisseurDeTrait(4);
	couleurCourante(255, 255, 0);
	for(int i = 0; i < cloud.nb; i++) {
		point(cloud.x[i], cloud.y[i]);
	}
}
