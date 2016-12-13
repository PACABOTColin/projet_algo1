#ifndef BOUTON_H
#define BOUTON_H

#define LONGEUR_CHAINE_BOUTON 50
#define NB_BOUTON 15
#define TAILLE_TEXTE 12

typedef struct bouton
{
	float xmin,ymin,xmax,ymax;
	char str[LONGEUR_CHAINE_BOUTON];
	DonneesImageRGB* image;
	couleur couleurBouton1;
	couleur couleurBouton2;
	couleur couleurText1;
	couleur couleurText2;
	int etat;
}bouton;

void afficheBouton(bouton button[NB_BOUTON]);





#endif
