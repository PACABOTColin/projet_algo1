#include <stdio.h>
#include <string.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "bouton.h"
#include "imageSF.h"

bouton initialiseB(char image1[], char image2[], int etatEnfonce)
{
	bouton button;
	button.image1=lisBMPRGB(image1); //load image for the button in state 0
	if(button.image1 == NULL) // chec if the file can be load
	{
		printf("le fichier ne peut être charger : %s\n", image1);
	}
	button.image2=lisBMPRGB(image2);//load image for the button in state 0
	if(button.image2 == NULL)// chec if the file can be load
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
	// initialise all the button
	button[0] = initialiseB("images/Boutons/playButton_Relache.bmp","images/Boutons/pauseButton_Appuis.bmp", 1);
	button[1] = initialiseB("images/Boutons/stopButton_Relache.bmp","images/Boutons/stopButton_Appuis.bmp", 0);
	button[2] = initialiseB("images/Boutons/resetButton_Relache.bmp","images/Boutons/resetButton_Appuis.bmp", 0);
	button[3] = initialiseB("images/Boutons/loopButton_Relache.bmp","images/Boutons/LoopButton_Appuis.bmp", 1);
	button[4] = initialiseB("images/Boutons/repeatButton_Relache.bmp","images/Boutons/repeatButton_Appuis.bmp", 1);
	button[5] = initialiseB("images/Boutons/editButton_Relache.bmp","images/Boutons/editButton_Appuis.bmp", 1);
	button[6] = initialiseB("images/Boutons/offButton_Relache.bmp","images/Boutons/offButton_Appuis.bmp", 1);
	
	button[7] = initialiseB("images/Boutons/StartInputButton_Relache.bmp","images/Boutons/EndInputButton_Appuis.bmp", 1);
	
	button[8] = initialiseB("images/Boutons/Curves_Display_Relache.bmp","images/Boutons/Curves_Display_Appuis.bmp", 1);
	button[9] = initialiseB("images/Boutons/NewtonButton_Relache.bmp","images/Boutons/NewtonButton_Appuis.bmp", 1);
	button[10] = initialiseB("images/Boutons/LagrangeButton_Relache.bmp","images/Boutons/LagrangeButton_Appuis.bmp", 1);
	button[11] = initialiseB("images/Boutons/BrokenLineButton_Relache.bmp","images/Boutons/BrokenLineButton_Appuis.bmp", 1);
	button[12] = initialiseB("images/Boutons/Bird1Button_Relache.bmp","images/Boutons/Bird1Button_Appuis.bmp", 1);
	button[13] = initialiseB("images/Boutons/Bird2Button_Relache.bmp","images/Boutons/Bird2Button_Appuis.bmp", 1);
	button[14] = initialiseB("images/Boutons/Bird3Button_Relache.bmp","images/Boutons/Bird3Button_Appuis.bmp", 1);
	button[15] = initialiseB("images/Boutons/offButton_Relache.bmp","images/Boutons/offButton_Appuis.bmp", 1);
	
	
	button[0].etat=1;
	
}

bouton coordonnee (bouton button,int xmin,int ymin,int xmax,int ymax)
{
	// for initialise the button position
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
	button[6]=	coordonnee(button[6], 26 * 	largeurFenetre()/30,		hauteurFenetre()/35,29 * largeurFenetre()/30,3  * 	hauteurFenetre()/35);
	
	//Initialize parameters button
	
	button[7]=	coordonnee(button[7], 26 * 	largeurFenetre()/30,		hauteurFenetre()/35,29 * largeurFenetre()/30,3  * 	hauteurFenetre()/35);
	button[8]=	coordonnee(button[8],26 * largeurFenetre()/30,6  * 	hauteurFenetre()/35,29 * largeurFenetre()/30,8 * 	hauteurFenetre()/35);
	button[9]=	coordonnee(button[9],26 * largeurFenetre()/30,9 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,11 * 	hauteurFenetre()/35);
	button[10]=	coordonnee(button[10],26 *largeurFenetre()/30,12 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,14 * 	hauteurFenetre()/35);

	button[11]=	coordonnee(button[11],26 * largeurFenetre()/30,15 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,17  * 	hauteurFenetre()/35);
	button[12]=	coordonnee(button[12],26 * largeurFenetre()/30,19 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,22 * 	hauteurFenetre()/35);
	button[13]=	coordonnee(button[13],26 * largeurFenetre()/30,23 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,26 * 	hauteurFenetre()/35);
	button[14]=	coordonnee(button[14],26 * largeurFenetre()/30,27 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,30 * 	hauteurFenetre()/35);
	button[15]=	coordonnee(button[15],26 * largeurFenetre()/30,31 * 	hauteurFenetre()/35,29 * largeurFenetre()/30,34 * 	hauteurFenetre()/35);
	
	
}

void afficheBouton(bouton button[],int tailleTableau)
{
	int i;
	
	couleur col;
	col.r=0;
	col.v=255;
	col.b=0;
	for (i=0;i<tailleTableau;i++)
	{
		if (button[i].etat==0)// print the first picture if the state is 0
		{
			ecrisImageSansFond(button[i].xmin, button[i].ymin , button[i].image1->largeurImage, button[i].image1->hauteurImage, button[i].image1->donneesRGB,col);
		}	
		else // prins the secon pitur else
		{
			ecrisImageSansFond(button[i].xmin, button[i].ymin , button[i].image2->largeurImage, button[i].image2->hauteurImage, button[i].image2->donneesRGB,col);
		}
	}
}

void bouton_clic(bouton button[],int tailleTableau)
{
	for (int i = 0; i < tailleTableau; ++i)
	{
		button[i].ancienEtat = button[i].etat;
		if(etatBoutonSouris() == GaucheAppuye
			&& abscisseSouris() > button[i].xmin && abscisseSouris() < button[i].xmax 
			&& ordonneeSouris() > button[i].ymin && ordonneeSouris() < button[i].ymax) // if the button is cliked
		{
			if(button[i].etatEnfonce == 1) // if it's a two-stable button change the state
			{
				button[i].etat = !button[i].etat;
			}
			else//else is a push button, put the state to 1
			{
				button[i].etat = 1;
			}
		}
		else
		{
			if (button[i].etatEnfonce == 0) // if the button is not cliked and it's a push button put state to 0
			{
				button[i].etat = 0;
			}
		}
	}
}

slideBar slideBarInit(int xmin, int xmax, int y, int valMin, int valMax)
{ // initialyse a slidebar struct
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
{ // for change the value printed by the slideBar
	slide.value = value;
	return slide;
}

void printSlideBar(slideBar slide)
{
	//print the slidebar
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
		&& abscisseSouris() > slide.xmin && abscisseSouris() < slide.xmax) // if the slidebar is cliked, update value
	{
		slide.value = (abscisseSouris() - slide.xmin) * (slide.valMax - slide.valMin) / (slide.xmax - slide.xmin) + slide.valMin;
	}
	return slide;
}
