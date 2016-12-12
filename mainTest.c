#include <stdlib.h> // to use exit()
#include <stdio.h> // to use printf()
#include <math.h> // to use sin() and cos()
#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "ESLib.h" // to use "valeurAleatoire()"
#include "animation.h" // to use the animation functon

// Picture default width and height
#define LargeurFenetre 800
#define HauteurFenetre 600

// Circle trace function  
void cercle(float centreX, float centreY, float rayon);

/* the "gestion des evenements" function is call automaticly by the system when an event arrive */
void gestionEvenement(EvenementGfx evenement);


int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("Animation", LargeurFenetre, HauteurFenetre);
	
	/* Launch the loop wich directs events on the "gestionEvenement" function bellow, this function use "fonctionAffichage" */
	lanceBoucleEvenements();
	
	return 0;
}



/* Circle trace function */
void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Number of sectors to trace the circle
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // for each sectors
	{
		const double angle = 2.*M_PI*index/Pas; // We calculate the starting angle of the sector
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// We trace the sector with the help of On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static DonneesImageRGB *image = NULL; // L'image a afficher au centre de l'ecran
	static DonneesImageRGB* attitude[NB_ATTITUDES]; // will contain the sprites of animation

	/* On va aussi animer une balle traversant l'ecran */
	
	switch (evenement)
	{
		case Initialisation:

			demandeTemporisation(20);
			lectureImageAttitude(attitude);
			break;
		
		case Temporisation:
			lectureAnimation();
			rafraichisFenetre();
			break;
			
		case Affichage:
			afficheAnimation(attitude);
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
					libereDonneesImageRGB(&image); /* On libere la structure image,
					c'est plus propre, meme si on va sortir du programme juste apres */
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
			break;
	}
}
