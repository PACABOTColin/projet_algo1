#include <stdlib.h> // to use exit()
#include <stdio.h> // to use printf()
#include <math.h> // to use sin() and cos()
#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "ESLib.h" // to use "valeurAleatoire()"
#include "animation.h" // to use the animation functon
#include "bouton.h" // to use the button functon
#include "polynome.h" // to use the polynomial functon
#include "nuage.h"

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
			// We trace the sector with the help of triangle
	}
	
}


/* The "gestion des evenements" function is called by the system when an events appears */

void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static DonneesImageRGB* background;
	static bouton button[NB_BOUTON];
	static slideBar slideButton[2];
	static animation anim;
	
	switch (evenement)
	{
		case Initialisation:
 
			// Configure the system for generate a temposrisation message every 20 millisecond
			demandeTemporisation(20);
			initialiseBoutons(button);
			redimensionne(button);
			background = lisBMPRGB("sprites/IHM.bmp");
			DonneesImageRGB* attitude[20];
			lectureImageAttitude(attitude, "sprites/oiseauRouge%d.bmp");
			anim = creeAnimation((nuage){0,{0},{0}}, attitude, 0);
			slideButton[0] = slideBarInit(2 * largeurFenetre() / 30, 23 * largeurFenetre() / 30, 5 * hauteurFenetre() / 35, 0, NB_INSTANTS);
			slideButton[1] = slideBarInit(26 * largeurFenetre() / 30, 29 * largeurFenetre() / 30, 10 * hauteurFenetre() / 35, 0, NB_INSTANTS);
			break;
		
		case Temporisation:
			// we update the window
			anim.current_state = slideButton[0].value;
			anim = lectureAnimation(anim);
			slideButton[0].value = anim.current_state;
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			// The background color is white
			effaceFenetre (255, 255, 255);
			ecrisImage(0, 0,
						background->largeurImage,
						background->hauteurImage,
						background->donneesRGB);
			afficheBouton(button);
			afficheAnimation(anim);
			printSlideBar(slideButton[0]);
			printSlideBar(slideButton[1]);
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* to leave the program */
				case 'q':
					libereDonneesImageRGB(&background); 
					freeImages(anim);
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Change the full screen mode
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure the system for generate a temposrisation message every 20 millisecond (fast)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure the system for generate a temposrisation message every 20 millisecond (slow)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure the system not to post a message of temposrisation
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			bouton_clic(button);
			slideButton[0] = gereClicSlideBar(slideButton[0]);
			slideButton[1] = gereClicSlideBar(slideButton[1]);
			break;
		
		case Souris: // If the mouse is moved
			break;
		
		case Inactivite: // When a  message is not available 
			break;
		
		case Redimensionnement: 
			redimensionneFenetre(LargeurFenetre, HauteurFenetre);
			break;
	}
}
