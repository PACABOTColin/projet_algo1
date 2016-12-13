#include "GfxLib.h"
#include "nuage.h"

nuage ajoutPoint(nuage cloud, int x_min, int y_min, int x_max, int y_max)
{
	if(cloud.nb < DIM // if the arraw is not full
	 	&& abscisseSouris() > x_min && abscisseSouris() < x_max  // and if the mouse is inside the graphical zone
	 	&& ordonneeSouris() > y_min && ordonneeSouris() < y_max)
	{
		// save the coordinate of mouse
		cloud.x[cloud.nb] = abscisseSouris();
		cloud.y[cloud.nb] = ordonneeSouris();
		cloud.nb++; // increase the number of dote in cloude
	}
	return cloud; // return the cloud with new dote
}

void dessineNuage(nuage cloud)
{
	epaisseurDeTrait(4);
	couleurCourante(255, 255, 0);
	for(int i = 0; i < cloud.nb; i++) 
	{
		point(cloud.x[i], cloud.y[i]);
	}
}
