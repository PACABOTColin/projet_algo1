#include <stdio.h>
#include <string.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "affichage.h"
#include "bouton.h"

bouton initialiseB(couleur couleurBouton1,couleur couleurBouton2,couleur couleurText1, couleur couleurText2, char str[],char image[])
{
	bouton button;
	
	button.couleurBouton1= couleurBouton1;
	button.couleurBouton2= couleurBouton2;
	button.couleurText1= couleurText1;
	button.couleurText2= couleurText2;
	strcpy(button.str,str);
	button.image=lisBMPRGB(image);
	
	return button;
}

couleur fabriqueCouleur(r,v,b)
{
	couleur col;
	col.r=r;
	col.v=v;
	col.b=b;
	
	return col;
}

void initialiseBoutons(bouton button[])
{
	button[play] = initialiseB(fabriqueCouleur((120,100,250),fabriqueCouleur(250,100,120),fabriqueCouleur(255,255,255),fabriqueCouleur()
}

void afficheBouton(bouton button[NB_BOUTON])
{
	int i;
	float taille=tailleChaine(button[i].str,TAILLE_TEXTE);
	for (i=0;i<NB_BOUTON;i++)
	{
		if (button.etat==1)
		{
			couleurCourante(button[i].couleurBouton1.r,button[i].couleurBouton1.v,button[i].couleurBouton1.b);
		}
		else
		{
			couleurCourante(button[i].couleurBouton2.r,button[i].couleurBouton2.v,button[i].couleurBouton2.b);
		}
		rectangle(button[i].xmin,button[i].ymin,button[i].xmax,button[i].ymax);
		
		if (button.etat==1)
		{
			couleurCourante(button[i].couleurText1.r,button[i].couleurText1.v,button[i].couleurText1.b);
		}
		else
		{
			couleurCourante(button[i].couleurText2.r,button[i].couleurText2.v,button[i].couleurText2.b);
		}
		
		afficheChaine(button[i].str,TAILLE_TEXTE,(button[i].xmin+button[i].xmax+taille)/2,((button[i].ymin+button[i].ymax)-taille)/2);

		if (button[i].image != NULL)
		{
			ecrisImage(((button[i].xmax-button[i].xmin)-button[i].image->largeurImage)/2,((button[i].ymax-button[i].ymin)-button[i].image->hauteurImage)/2,button[i].image->donneesRGB);
		}
	}
}
