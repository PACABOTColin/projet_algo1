#include <stdio.h>
#include <string.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "bouton.h"

bouton initialiseB(char image1[], char image2[], int etatEnfonce)
{
	bouton button;
	button.image1=lisBMPRGB(image1);
	if(button.image1 == NULL)
	{
		printf("le fichier ne peut être charger : %s\n", image1);
	}
	button.image2=lisBMPRGB(image2);
	if(button.image2 == NULL)
	{
		printf("le fichier ne peut être charger: %s\n", image2);
	}
	button.etat = 0;
	button.etatEnfonce = etatEnfonce;
	button.ancienEtat = 0;
	return button;
}

void initialiseBoutons(bouton button[])
{
	button[0] = initialiseB("images/Boutons/playButton.bmp","images/Boutons/pauseButton.bmp", 1);
	button[1] = initialiseB("images/Boutons/stopButton.bmp","images/Boutons/stopButton.bmp", 0);
	button[2] = initialiseB("images/Boutons/resetButton.bmp","images/Boutons/resetButton_Appuis.bmp", 0);
	button[3] = initialiseB("images/Boutons/LoopButton.bmp","images/Boutons/LoopButton_Appuis.bmp", 1);
	button[4] = initialiseB("images/Boutons/repeatButton.bmp","images/Boutons/repeatButton_Appuis.bmp", 1);
	button[5] = initialiseB("images/Boutons/editButton.bmp","images/Boutons/editButton.bmp", 1);
	
	button[6] = initialiseB("images/Boutons/Debut_Saisie.bmp","images/Boutons/Fin_Saisie.bmp", 1);
	
	button[7] = initialiseB("images/Boutons/affiche_Courbe.bmp","images/Boutons/affiche_Courbe_Appuis.bmp", 1);
	button[8] = initialiseB("images/Boutons/Lagrange.bmp","images/Boutons/Lagrange_Appuis.bmp", 1);
	button[9] = initialiseB("images/Boutons/Newton.bmp","images/Boutons/Newton_Appuis.bmp", 1);
	button[10] = initialiseB("images/Boutons/Ligne_Brisee.bmp","images/Boutons/Ligne_Brisee_Appuis.bmp", 1);
	button[11] = initialiseB("images/sprites/oiseauRouge3.bmp","images/sprites/oiseauRouge8.bmp", 1);
	button[12] = initialiseB("images/sprites/oiseauRouge3.bmp","images/sprites/oiseauRouge8.bmp", 1);
	button[13] = initialiseB("images/sprites/oiseauRouge3.bmp","images/sprites/oiseauRouge8.bmp", 1);
	button[14] = initialiseB("images/Boutons/off_Button.bmp","images/Boutons/off_Appuis.bmp", 1);
	
	button[0].etat=1;
	
}

bouton coordonnee (bouton button,int xmin,int ymin,int xmax,int ymax)
{
	button.xmin= xmin < xmax ? xmin : xmax;
	button.ymin= ymin < ymax ? ymin : ymax;
	button.xmax= xmin > xmax ? xmin : xmax;
	button.ymax= ymin > ymax ? ymin : ymax;;

	return button;
}
void redimensionne (bouton button[])
{
	//Initialize controls button
	
	button[0]=coordonnee(button[0],     largeurFenetre()/30,hauteurFenetre()/35,4 * largeurFenetre()/30,3 * hauteurFenetre()/35);
	button[1]=coordonnee(button[1],5  * largeurFenetre()/30,hauteurFenetre()/35,8 * largeurFenetre()/30,3 * hauteurFenetre()/35);
	button[2]=coordonnee(button[2],9  * largeurFenetre()/30,hauteurFenetre()/35,12 * largeurFenetre()/30,3 * hauteurFenetre()/35);
	button[3]=coordonnee(button[3],13 * largeurFenetre()/30,hauteurFenetre()/35,16 * largeurFenetre()/30,3 * hauteurFenetre()/35);
	button[4]=coordonnee(button[4],17 * largeurFenetre()/30,hauteurFenetre()/35,20 * largeurFenetre()/30,3 * hauteurFenetre()/35);
	button[5]=coordonnee(button[5],21 * largeurFenetre()/30,hauteurFenetre()/35,25 * largeurFenetre()/30,3 * hauteurFenetre()/35);

	//Initialize parameters button
	
	button[6]=	coordonnee(button[6], 26 * 	largeurFenetre()/30,		hauteurFenetre()/35,29 * largeurFenetre()/30,3  * 	hauteurFenetre()/35);
	button[7]=	coordonnee(button[7],26 * 	largeurFenetre()/30,6  * 	hauteurFenetre()/35,29 * largeurFenetre()/30,8 * 	hauteurFenetre()/35);
	button[8]=	coordonnee(button[8],26 *	largeurFenetre()/30,9 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,11 * 	hauteurFenetre()/35);
	button[9]=	coordonnee(button[9],26 *	largeurFenetre()/30,12 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,14 * 	hauteurFenetre()/35);

	button[10]=	coordonnee(button[10],26 * largeurFenetre()/30,15 * 	hauteurFenetre()/35,29.5 * largeurFenetre()/30,17  * 	hauteurFenetre()/35);
	button[11]=	coordonnee(button[11],26.5 *largeurFenetre()/30,18 * 	hauteurFenetre()/35,29.5 * largeurFenetre()/30,21 * 	hauteurFenetre()/35);
	button[12]=	coordonnee(button[12],26.5 *largeurFenetre()/30,22 * 	hauteurFenetre()/35,29.5 * largeurFenetre()/30,25 * 	hauteurFenetre()/35);
	button[13]=	coordonnee(button[13],26.5 *largeurFenetre()/30,26 * 	hauteurFenetre()/35,29.5 * largeurFenetre()/30,29 * 	hauteurFenetre()/35);
	button[14]=	coordonnee(button[14],26 *	largeurFenetre()/30,31 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,34 * 	hauteurFenetre()/35);
	
}

void afficheBouton(bouton button[NB_BOUTON])
{
	int i;
	for (i=0;i<NB_BOUTON;i++)
	{
		if (button[i].etat==0)
		{
			//ecrisImage(((button[i].xmax - button[i].xmin) - button[i].image1->largeurImage)/2, ((button[i].ymax - button[i].ymin) - button[i].image1->hauteurImage)/2, button[i].image1->largeurImage,	button[i].image1->hauteurImage, button[i].image1->donneesRGB);
			ecrisImage(button[i].xmin, button[i].ymin , button[i].image1->largeurImage, button[i].image1->hauteurImage, button[i].image1->donneesRGB);
		}
		else
		{
			//ecrisImage(((button[i].xmax-button[i].xmin) - button[i].image2->largeurImage)/2, ((button[i].ymax - button[i].ymin) - button[i].image2->hauteurImage)/2, button[i].image2->largeurImage, button[i].image2->hauteurImage, button[i].image2->donneesRGB);
			ecrisImage(button[i].xmin, button[i].ymin , button[i].image2->largeurImage, button[i].image2->hauteurImage, button[i].image2->donneesRGB);
		}
	}
}

void bouton_clic(bouton button[])
{
	for (int i = 0; i < NB_BOUTON; ++i)
	{
		button[i].ancienEtat = button[i].etat;
		if(etatBoutonSouris() == GaucheAppuye
			&& abscisseSouris() > button[i].xmin && abscisseSouris() < button[i].xmax 
			&& ordonneeSouris() > button[i].ymin && ordonneeSouris() < button[i].ymax)
		{
			if(button[i].etatEnfonce == 1)
			{
				button[i].etat = !button[i].etat;
			}
			else
			{
				button[i].etat = 1;
			}
		}
		else
		{
			if (button[i].etatEnfonce == 0)
			{
				button[i].etat = 0;
			}
		}
	}
}

slideBar slideBarInit(int xmin, int xmax, int y, int valMin, int valMax)
{
	slideBar rv;
	rv.xmin = xmin;
	rv.xmax = xmax;
	rv.y = y;
	rv.value = 0;
	rv.valMax = valMax;
	rv.valMin = valMin;
	return rv;
}

slideBar slideBarSetValue(slideBar slide, int value)
{
	slide.value = value;
	return slide;
}

void printSlideBar(slideBar slide)
{
	couleurCourante(50, 50, 50);
	epaisseurDeTrait(4);
	ligne(slide.xmin, slide.y, slide.xmax, slide.y);
	couleurCourante(0, 0, 0);
	int x = (slide.value - slide.valMin) * (slide.xmax - slide.xmin) / (slide.valMax - slide.valMin) + slide.xmin;
	rectangle(x - 4, slide.y - 4, x + 4, slide.y + 4);
}

slideBar gereClicSlideBar(slideBar slide)
{
	if( etatBoutonSouris() == GaucheAppuye
		&& ordonneeSouris() > slide.y - 4 && ordonneeSouris() < slide.y + 4
		&& abscisseSouris() > slide.xmin && abscisseSouris() < slide.xmax)
	{
		slide.value = (abscisseSouris() - slide.xmin) * (slide.valMax - slide.valMin) / (slide.xmax - slide.xmin) + slide.valMin;
	}
	return slide;
}
