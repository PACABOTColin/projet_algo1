#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "GfxLib.h" 
#include "polynome.h"
#include "polygraph.h"
#include "BmpLib.h"
#include "ESLib.h"

courbe initialiseCourbe(polynome P, float xmin,float xmax, int nbpts)
{
	courbe C;
	float pas,i;
	int j=0;

	C.ymin= C.ymax= evaluePolynome(xmin,P);
	C.xmin=xmin;
	C.xmax=xmax;
	C.nb=nbpts;
	pas=((xmax-xmin)/nbpts);
	
	for (i=xmin;i<xmax;i=i+pas)
	{
		C.trace[j].x=i;
		j++;		
	}

	for (j=0;j<=nbpts;j++)
	{
		C.trace[j].y=evaluePolynome(C.trace[j].x,P);
		if(C.trace[j].y < C.ymin)
		{
			C.ymin=C.trace[j].y;
		}

		if(C.trace[j].y > C.ymax)
		{
			C.ymax=C.trace[j].y;
		}	
	}
	
	return C;
}

void afficheCourbePoint(courbe C, mode M,float x0,float y0)
{
	float cy;
	int i;

	
	cy=hauteurFenetre()/(C.ymax-C.ymin);
	couleurCourante(M.rougeTrait,M.vertTrait,M.bleuTrait);
	epaisseurDeTrait(M.epaisseurTrait);
	for(i=0;i<C.nb-1;i++)
	{
		point((C.trace[i].x)+x0,(C.trace[i].y)*(cy)+y0);
	}
	couleurCourante(M.rougeTexte,M.vertTexte,M.bleuTexte);
	epaisseurDeTrait(M.epaisseurTexte);
	afficheChaine(C.expression,M.police,20,20);
}


