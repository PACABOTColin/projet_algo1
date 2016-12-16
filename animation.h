#ifndef ANIMATION_H
#define ANIMATION_H //this is for make shure don't make multiple inclusion on this file

/* 
 * $Date:        13. December 2016
 * $Revision: 	V.0.1
 *
 * Project: 	algorithmic project
 * Title:	    animation.h
 *
 * Description: this file contain the function for make animation of sprite
 */
#include "nuage.h"
#include "BmpLib.h"
#define NB_ATTITUDES 50 // NB_ATTITUDES define the number of sprite in one animation
#define NB_INSTANTS 100 // NB_INSTANTS define the number of step in the animation displayed


/* this structure contain the position and the number of the picture */
typedef struct instant
{
	int x,y;					// contain the positon to print the pixel
	DonneesImageRGB* attitude; 	// contain the image of the animation
}instant;

typedef struct sprite
{
	DonneesImageRGB* attitude[NB_ATTITUDES];
	int nb;
}sprite;

/*this structure conain all the information for one animation*/
typedef struct animation
{
	instant param[NB_INSTANTS]; 		// contain the parametre of animation
	int current_state;				// contain the avancement of the animation
	int type;						//conatain the type of the animation -1 for uninitilizes animation
									//									 0 for horoisontal animation
									//									 1 for the broken line antimatio
									//									 2 for the polinomial aproximation whith lagrange methode
									//									 3 for the polinomial aproximation whith newtown methode
}animation;

/* lectureImageAttitude read the sprite and stor it in attitude */
sprite lectureImageAttitude(char nameFormat[], char nameFormat2[]);
/* creeAnimation make the animation output in array animation */
/* lectureAnimation forward the animation */
animation creeAnimation(nuage points, sprite attitude, int mode);
/* afficheAnimation display the animation on the screen */
void afficheAnimation(animation anim);
/* this function made animation forwarde*/
animation lectureAnimation(animation anim,int etat);

#endif
