#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "GfxLib.h" 
#include "polynome.h"
#include "polygraph.h"
#include "BmpLib.h"
#include "ESLib.h"

courbe initialiseCourbe(polynome P)
{
	courbe C;
	int j=0;
	C.nb=largeurFenetre();
	exprimePolynome(P, C.expression);

	for (j=0;j<=C.nb;j++)
	{
		C.trace[j].x=j;
		C.trace[j].y=evaluePolynome(j,P);
	}
	
	return C;
}

void afficheCourbePoint(courbe C)
{
	int i;

	couleurCourante(255, 0, 0);
	epaisseurDeTrait(2);
	for(i=0;i<C.nb - 1;i++)
	{
		if(C.trace[i].y < hauteurFenetre() && C.trace[i].y > 93)
		{
			point(C.trace[i].x, C.trace[i].y);
		}

	}
	epaisseurDeTrait(1);
	afficheChaine(C.expression,14 ,20,hauteurFenetre() - 20);
}


