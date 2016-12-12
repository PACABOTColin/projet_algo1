#ifndef ANIMATION_H
#define ANIMATiON_H

#define NB_ATTITUDES 14
#define NB_INSTANTS 1000

typedef struct instant
{
	int nbAttitude;
	int X,Y;
}instant;

int lectureImageAttitude (DonneesImageRGB* attitude[]);
int creeAnimation (instant animation[]);
void lectureAnimation();
void afficheAnimation (DonneesImageRGB* attitude[]);

#endif
