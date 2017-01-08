#include <stdlib.h> // to use exit()
#include <stdio.h> // to use printf()
#include <math.h> // to use sin() and cos()
#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "ESLib.h" // to use "valeurAleatoire()"
#include "animation.h" // to use the animation functon
#include "bouton.h" // to use the button functon
#include "polynome.h" // to use the polynomial functon
#include "nuage.h" // to use the multi dote
#include "imageSF.h" // to use the multi dote 
#include "polygraph.h" //to print polynome on screen
#define NUMBER_OF_SPRIT 3 // define the numer of sprites how are load at the start of the program
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
	static DonneesImageRGB* background[2]; // contain the background picture
	static bouton button[NB_BOUTON]; //contain all the button
	static slideBar slideButton[2]; //contain the two slidebard
	static sprite attitude[NUMBER_OF_SPRIT]; //contain the different picture of differents sprite
	static animation anim[NUMBER_OF_SPRIT]; // contain the animation of diffetents sprite
	static nuage cloud; // contain the cloud of dote
	static int bird_index;

	static couleur col;
	col.r=0;
	col.v=255;
	col.b=0;
	
	static int animC=0; // contain if the animation is initial


	switch(evenement)
	{
		case Initialisation:

			// Configure the system to not generate a temposrisation message
			demandeTemporisation(-1);
			cloud.nb = 0; //initialyse cloud
			initialiseBoutons(button);// initialise button
			redimensionne(button); // finish the initialisation of button
			for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
			{
				anim[i].type = -1; // initialy all the animation
			}
			background[0] = lisBMPRGB("images/HMI_Animation.bmp"); //load background 1 picture
			background[1] = lisBMPRGB("images/HMI_Editor.bmp"); //load background 2 picture
			attitude[0] = lectureImageAttitude("images/sprites/oiseauRouge%d.bmp", "images/sprites/oiseauRouge%d_reverse.bmp"); // load 1 sprite pictures
			attitude[1] = lectureImageAttitude("images/sprites/oiseauBleu%d.bmp", "images/sprites/oiseauBleu%d_reverse.bmp"); // load 2 sprite pictures
			attitude[2] = lectureImageAttitude("images/sprites/fusee%d.bmp", "images/sprites/fusee%d_reverse.bmp"); // load 3 sprite pictures
			slideButton[0] = slideBarInit(2 * largeurFenetre() / 30, 23 * largeurFenetre() / 30, 4.5 * hauteurFenetre() / 35, 0, NB_INSTANTS);
			slideButton[1] = slideBarInit(26 * largeurFenetre() / 30, 29 * largeurFenetre() / 30, 4.5 * hauteurFenetre() / 35, 0, NB_INSTANTS); // initialyse the two slidebar
			break;
		
		case Temporisation:

			// we update the window
			for(int i = 0; i < NUMBER_OF_SPRIT; ++i)
			{
				anim[i].current_state = slideButton[0].value; // update the animation with the value of slidebar
				anim[i] = lectureAnimation(anim[i], button[4].etat); //update animation state
				if(animC==1)
				{
					slideButton[0].value = anim[i].current_state; //update the slidebar with the new value af the animation
				}
			}
			rafraichisFenetre(); 
			break;
			
		case Affichage:
			// The background color is white
			effaceFenetre(255, 255, 255); // clear window
			ecrisImage(0, 0,background[button[5].etat]->largeurImage,background[button[5].etat]->hauteurImage,background[button[5].etat]->donneesRGB); // print background
			afficheBouton(button,NB_BOUTON); // print button


			if(button[5].etat == 0) // "Debut saisie" / "Fin saisie Button"
			{
					
				effaceFenetre(255, 255, 255); // clear window
				ecrisImage(0, 0,background[button[5].etat]->largeurImage,background[button[5].etat]->hauteurImage,background[button[5].etat]->donneesRGB); // print background
				afficheBouton(button,7); // print button
				printSlideBar(slideButton[0]); //Display the player slidebar
				ecrisImageSansFond(26 *largeurFenetre()/30, hauteurFenetre()/35 , button[6].image1->largeurImage, button[6].image1->hauteurImage, button[6].image1->donneesRGB,col);
			
			
			}
			
			else if(button[5].etat == 1) // "Debut saisie" / "Fin saisie Button"
			{
			
				effaceFenetre(255, 255, 255); // clear window
				ecrisImage(0, 0,background[button[5].etat]->largeurImage,background[button[5].etat]->hauteurImage,background[button[5].etat]->donneesRGB); // print background
				afficheBouton(button,NB_BOUTON); // print button
				printSlideBar(slideButton[0]); //Display the player slidebar
				printSlideBar(slideButton[1]); //Display the player slidebar
				
			}
			
			if(animC==1) // if the aniamtion is initialised
			{
				for (int i = 0; i < NUMBER_OF_SPRIT; ++i)
				{
					afficheAnimation(anim[i]);// print aniamtion on window
				}
			}

			if(button[2].etat == 1 && button[0].etat == 0) // stop button 
			{
				for (int i = 0; i < NUMBER_OF_SPRIT; ++i) //reset the etat of button
				{
					anim[i].current_state=0; // update the animation at 0
					slideButton[0].value=anim[i].current_state; //update the slidebar with the new value af the animation
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
					
			if(button[7].etat == 1) // "Debut saisie" / "Fin saisie Button"
			{
				dessineNuage(cloud);// user can place points on the drawing area				
			}

			if(button[8].etat == 1) // "affiche courbe" button
			{
				switch (anim[bird_index].type)
				{
					case 0:
						afficheLigne(cloud);
						break;
					case 2:
						afficheCourbePoint(initialiseCourbe(lagrange(cloud)));
						break;
					case 3:
						afficheCourbePoint(initialiseCourbe(newton(cloud)));
						break;
					default:
						break;
				}
			}
					
			break;
			
		case Clavier: //For keybord interaction
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
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris: // for clicking interaction
			bouton_clic(button,NB_BOUTON);
			slideButton[0] = gereClicSlideBar(slideButton[0]);//update the player slidebar position
			slideButton[1] = gereClicSlideBar(slideButton[1]);//update the parametric slidebar position
		if(etatBoutonSouris() == GaucheAppuye)
			{
				if (button[12].etat == 1) 
				{
					bird_index = 0;
				}
				else if (button[13].etat == 1)
				{
					bird_index = 1;
				}
				else if (button[14].etat == 1)
				{
					bird_index = 2;
				}
				else
				{
					bird_index = -1;
				}
				// if the bird changed reset the cloud
				for (int i = 12; i <= 14; ++i)
				{
					if (button[i].etat != button[i].ancienEtat)
					{
						cloud.nb = 0;
					}
				}
				if(button[0].etat == 1 && button[0].ancienEtat == 0) // "pause" button
				{
					demandeTemporisation(-1);
				}
				else if(button[0].etat == 0 && button[0].ancienEtat == 1) // "play" button
				{
					demandeTemporisation(20);
				}
					
				if(button[1].etat == 1) // "pause" button and slidebar position update
				{
					demandeTemporisation(-1);
					animC=0;
					slideButton[0].value=0;
					for (int i = 0; i < NUMBER_OF_SPRIT; ++i) // slidebar position update
					{
						anim[i].current_state = slideButton[0].value; 
					}
					initialiseBoutons(button);
					redimensionne(button);
					cloud.nb=0;
				}

				if(button[4].etat == 1) // if "infinite loop" button is pushed , we can not push the "restart" button
				{
					button[2].etat=0;
				}
				if(button[5].etat == 0) // if "infinite loop" button is pushed , we can not push the "restart" button
				{
					
					button[7].etat=0;
					button[8].etat=0;
					button[9].etat=0;
					button[10].etat=0;
					button[11].etat=0;
					button[12].etat=0;
					button[13].etat=0;
					button[14].etat=0;
					button[15].etat=0;
					
					slideButton[1].value=0;
					
				}

				if(button[5].etat == 1) // if "infinite loop" button is pushed , we can not push the "restart" button
				{
					button[6].etat=0;
				}
				
				if (bird_index < 0 )
				{
					button[7].etat=0;
					button[8].etat=0;
					button[9].etat=0;
					button[10].etat=0;
					button[11].etat=0;

					slideButton[1].value=0;
				}
				if(button[7].etat == 1 ) // user can add points only in the drawable area
				{
					
					cloud = ajoutPoint(cloud, 0, 93, largeurFenetre() - 130, hauteurFenetre()); // points can not be placed on the button area
					int animationType;
					if(button[9].etat == 1) // "Lagrange" button
					{
						animationType = 3;
					}
					else if(button[10].etat == 1) // "Newton" button
					{
						animationType = 2;
					}
					else if (button[11].etat == 1) // "Ligne brisee" button
					{
						animationType = 1;
					}
					else // orizontal line
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
				
				if(button[9].etat == 1 && button[9].ancienEtat == 0) // if "Lagrange" button is pushed user can not pushed "Broken Line" or "Newton" buttons
				{
					button[10].etat = 0;
					button[11].etat = 0;
					animC=1;
				}
				else if(button[10].etat == 1 && button[10].ancienEtat == 0) // if "Newton" button is pushed user can not pushed "Broken Line" or "Lagrange" buttons
				{
					button[9].etat = 0; 
					button[11].etat = 0;
					animC=1;
				}

				else if(button[11].etat == 1 && button[11].ancienEtat == 0)// if "Broken Line" button is pushed user can not pushed "Newton" or "Lagrange" buttons
				{
					
					button[9].etat = 0;
					button[10].etat = 0;
					animC=1;
				}


				if(button[12].etat == 1 && button[12].ancienEtat == 0) // if "Bird 1" button is pushed user can not pushed "Bird 2" or "Bird 3" buttons
				{
					button[13].etat = 0;
					button[14].etat = 0;
					animC=1;
				}
				else if(button[13].etat == 1 && button[13].ancienEtat == 0) // if "Bird 2" button is pushed user can not pushed "Bird 1" or "Bird 3" buttons
				{
					button[12].etat = 0; 
					button[14].etat = 0;
					animC=1;
				}

				else if(button[14].etat ==1 && button[14].ancienEtat ==0)// if "Bird 3" button is pushed user can not pushed "Bird 1" or "Bird 2" buttons
				{
					
					button[12].etat = 0;
					button[13].etat = 0;
					animC=1;
				}

				if(button[15].etat == 1 || button[6].etat ==1) // "off" buttons for close the program
				{
					libereDonneesImageRGB(&background[0]);
					libereDonneesImageRGB(&background[1]); 
					termineBoucleEvenements();
				}

				if(button[3].etat == 1 && button[3].ancienEtat == 0 && button[11].etat == 1) // "close path" button pushed (creat the loop)
				{
					cloud.x[cloud.nb] = cloud.x[0];
					cloud.y[cloud.nb] = cloud.y[0];
					cloud.nb++;
					anim[bird_index] =creeAnimation(cloud, attitude[bird_index],1);
				}
				else if(button[3].etat == 0 && button[3].ancienEtat == 1 && button[11].etat == 1) // "close path" button unpushed (do not dispaly the loop)
				{
					cloud.nb--;
					anim[bird_index] = creeAnimation(cloud, attitude[bird_index], 1); // change the sprite animation
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
