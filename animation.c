#include <string.h>
#include "animation.h"

static int step = 0;

int lectureImageAttitude(DonneesImageRGB* attitude[])
{
	char str[50]; // this varaiable will contain the name of the file who will be load
	for (int i = 0; i < NB_ATTITUDES; ++i)
	{
		sprintf(str, "sprites/oiseauRouge%d.bmp",i+1)
		attitude[i] = lisBMPRGB(str);
	}
	return 0;
}

int creeAnimation(instant animation[])
{
	int  step = NB_ATTITUDES / NB_INSTANTS;
	for (int i = 0; i < NB_INSTANTS; ++i)
	{
		/* code */
	}
	return 0;
}

void afficheAnimation (DonneesImageRGB* attitude[])
{
	ecrisImage((largeurFenetre()-attitude[step]->largeurImage)/2, (hauteurFenetre()-attitude[step]->hauteurImage)/2, attitude[step]->largeurImage, attitude[step]->hauteurImage, attitude[step]->donneesRGB);
}

void lectureAnimation()
{
	i++;
	i = i % NB_ATTITUDES;
}