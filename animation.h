#ifndef ANIMATION_H
#define ANIMATiON_H

#define NB_ATTITUDES 14
#define NB_INSTANTS 100

typedef struct instant
{
	int nAttitude;
	int x,y;
}instant;

int lectureImageAttitude (DonneesImageRGB* attitude[]);
int creeAnimation (instant animation[]);
void lectureAnimation();
void afficheAnimation (instant animation[], DonneesImageRGB* attitude[]);

#endif
