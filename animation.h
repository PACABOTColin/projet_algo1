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
#define NB_ATTITUDES 14 // NB_ATTITUDES define the number of sprite in one animation
#define NB_INSTANTS 100 // NB_INSTANTS define the number of step in the animation displayed


/* this structure contain the position and the number of the picture */
typedef struct instant
{
	int nAttitude; 				// contain the number of the sprite used
	int x,y;					// contain the positon to print the pixel
	DonneesImageRGB* attitude; 	// contain the image of the animation
}instant;

/*this structure conain all the information for one animation*/
typedef struct animation
{
	instant anim[NB_INSTANTS]; 		// contain the parametre of animation
	int current_state;				// contain the avancement of the animation
}animation;

/* lectureImageAttitude read the sprite and stor it in attitude */
int lectureImageAttitude(DonneesImageRGB* attitude[]);
/* creeAnimation make the animation output in array animation */
int creeAnimation(nuage points, animation anim[], int mode);
/* lectureAnimation forward the animation */
void lectureAnimation(animation anim);
/* afficheAnimation display the animation on the screen */
void afficheAnimation(animation anim[]);
/* freeImages free memory used by the image */
void freeImages(DonneesImageRGB* attitude[]);

#endif
