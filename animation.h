#ifndef ANIMATION_H
#define ANIMATiON_H //this is for make shure don't make multiple inclusion on this file

#define NB_ATTITUDES 14
#define NB_INSTANTS 100000

typedef struct instant
{
	int nAttitude;
	int x,y;
}instant;

int lectureImageAttitude (DonneesImageRGB* attitude[]);
int creeAnimation (instant animation[]);
void lectureAnimation();
void afficheAnimation (instant animation[], DonneesImageRGB* attitude[]);
void freeImages(DonneesImageRGB* attitude[]);

#endif
