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
#define NUMBER_OF_SPRIT 3
// Picture default width and height
#define LargeurFenetre 807
#define HauteurFenetre 593

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
	
	for(index = 0; index < Pas; ++index) // for each sectors
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
	static DonneesImageRGB* background[2];
	static bouton button[NB_BOUTON];
	static slideBar slideButton[2];
	static sprite attitude[NUMBER_OF_SPRIT];
	static animation anim[NUMBER_OF_SPRIT];
	static nuage cloud;
	static int animC=0;


	switch(evenement)
	{
		case Initialisation:

			// Configure the system for generate a temposrisation message every 20 millisecond
			demandeTemporisation(-1);
			cloud.nb = 0; //initialyse cloud
			initialiseBoutons(button);
			redimensionne(button);
			for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
			{
				anim[i].type = -1;
			}
			background[0] = lisBMPRGB("images/IHM.bmp");
			background[1] = lisBMPRGB("images/IHM_edit.bmp");
			attitude[0] = lectureImageAttitude("images/sprites/oiseauRouge%d.bmp", "images/sprites/oiseauRouge%d_reverse.bmp");
			attitude[1] = lectureImageAttitude("images/sprites/aigle%d_reverse.bmp", "images/sprites/aigle%d.bmp");
			attitude[2] = lectureImageAttitude("images/sprites/fusee%d.bmp", "images/sprites/fusee%d_reverse.bmp");
			slideButton[0] = slideBarInit(2 * largeurFenetre() / 30, 23 * largeurFenetre() / 30, 4.5 * hauteurFenetre() / 35, 0, NB_INSTANTS);
			slideButton[1] = slideBarInit(26 * largeurFenetre() / 30, 29 * largeurFenetre() / 30, 4.5 * hauteurFenetre() / 35, 0, NB_INSTANTS);
			break;
		
		case Temporisation:

			// we update the window
			for(int i = 0; i < NUMBER_OF_SPRIT; ++i)
			{
				anim[i].current_state = slideButton[0].value;
				anim[i] = lectureAnimation(anim[i], button[4].etat);
				if(animC==1)
				{
					slideButton[0].value = anim[i].current_state;
				}
			}
			rafraichisFenetre();
			break;
			
		case Affichage:

			// The background color is white
			effaceFenetre(255, 255, 255);
			ecrisImage(0, 0,background[button[5].etat]->largeurImage,background[button[5].etat]->hauteurImage,background[button[5].etat]->donneesRGB);
			afficheBouton(button);

			if(animC==1)
			{
				for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
				{
				afficheAnimation(anim[i]);
				}
			}

			if(button[2].etat == 1 && button[0].etat == 0)
			{
				for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
				{
					anim[i].current_state=0;
					slideButton[0].value=anim[i].current_state;
				}
			}
				
			/*if(button[4].etat == 1 && button[0].etat == 0)
			{
				for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
				{
					anim[i].current_state=0;
					afficheAnimation(anim[i]);
				}
				printf("reset\n");
				slideButton[0].value = anim[0].current_state;
			}*/
					
			if(button[6].etat == 1)
			{
				dessineNuage(cloud);						
			}

			if(button[7].etat == 1)
			{
				afficheLigne(cloud);						
			}
					
			printSlideBar(slideButton[0]);
			//printSlideBar(slideButton[1]);
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch(caractereClavier())
			{
				case 'Q': /* to leave the program */
				case 'q':
					libereDonneesImageRGB(&background[0]);
					libereDonneesImageRGB(&background[1]); 
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Change the full screen mode
					if(pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure the system for generate a temposrisation message every 20 millisecond(fast)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure the system for generate a temposrisation message every 20 millisecond(slow)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure the system not to post a message of temposrisation
					demandeTemporisation(-1);
					break;
			}
			//rafraichisFenetre();
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			bouton_clic(button);
			slideButton[0] = gereClicSlideBar(slideButton[0]);
			slideButton[1] = gereClicSlideBar(slideButton[1]);
		if(etatBoutonSouris() == GaucheAppuye)
			{
				int bird_index;
				if (button[11].etat == 1)
				{
					bird_index = 0;
				}
				else if (button[12].etat == 1)
				{
					bird_index = 1;
				}
				else if (button[13].etat == 1)
				{
					bird_index = 2;
				}
				else
				{
					bird_index = -1;
				}
				// if the bird changed reset the cloud
				for (int i = 11; i <= 13; ++i)
				{
					if (button[i].etat != button[i].ancienEtat)
					{
						cloud.nb = 0;
					}
				}
				if(button[0].etat == 1 && button[0].ancienEtat == 0)
				{
					demandeTemporisation(-1);
				}
				else if(button[0].etat == 0 && button[0].ancienEtat == 1)
				{
					demandeTemporisation(20);
				}
					
				if(button[1].etat == 1)
				{
					demandeTemporisation(-1);
					animC=0;
					slideButton[0].value=0;
					for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
					{
						anim[i].current_state = slideButton[0].value;
					}
					initialiseBoutons(button);
					redimensionne(button);
					cloud.nb=0;
				}

				if(button[4].etat == 1)
				{
					button[2].etat=0;
				}
				if(button[6].etat == 1 )
				{
					
					cloud = ajoutPoint(cloud, 0, 93, largeurFenetre() - 130, hauteurFenetre());
					int animationType;
					if(button[8].etat == 1)
					{
						animationType = 3;
					}
					else if(button[9].etat == 1)
					{
						animationType = 2;
					}
					else if (button[10].etat == 1)
					{
						animationType = 1;
					}
					else 
					{
						animationType = 0;
					}
					printf("bird_index : %d\n", bird_index);
					if (bird_index > -1 && bird_index < NUMBER_OF_SPRIT)
					{
						printf("creeAnimation\n");
						anim[bird_index] = creeAnimation(cloud, attitude[bird_index], animationType);
					}

					
				}
				
				if(button[8].etat == 1 && button[8].ancienEtat == 0)
				{
					button[9].etat = 0;
					button[10].etat = 0;
					animC=1;
				}
				else if(button[9].etat ==1 && button[9].ancienEtat ==0)
				{
					button[8].etat = 0; 
					button[10].etat = 0;
					animC=1;
				}

				else if(button[10].etat ==1 && button[10].ancienEtat ==0)
				{
					animC=1;
					button[8].etat = 0;
					button[9].etat = 0;
				}

				if(button[14].etat == 1)
				{
					libereDonneesImageRGB(&background[0]);
					libereDonneesImageRGB(&background[1]); 
					termineBoucleEvenements();
				}

				if(button[3].etat == 1 && button[3].ancienEtat==0 && button[10].etat == 1)
				{
					cloud.x[cloud.nb] = cloud.x[0];
					cloud.y[cloud.nb] = cloud.y[0];
					cloud.nb++;
					anim[bird_index] =creeAnimation(cloud, attitude[bird_index],1);
				}
				else if(button[3].etat == 0 && button[3].ancienEtat == 1 && button[10].etat == 1)
				{
					cloud.nb--;
					anim[bird_index] =creeAnimation(cloud, attitude[bird_index],1);
				}
			}
			rafraichisFenetre();
			break;

		case Souris: // If the mouse is moved
			break;
		
		case Inactivite: // When a  message is not available 
			break;

		case Redimensionnement: 
			redimensionneFenetre(LargeurFenetre, HauteurFenetre);
			//rafraichisFenetre();
			break;
	}
}
