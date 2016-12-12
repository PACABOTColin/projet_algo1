#ifndef ANIMATION_H
#define ANIMATiON_H

typedef struct instant
{
	int nbAttitude;
	int X,Y;
}instant;

int lectureImageAttitude (DonneesImageRGB* attitude[]);
int creeAnimation (instant animation[]);

#endif
