#include <stdio.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files

#include "animation.h"

int step = 0;
int x = 0;

int lectureImageAttitude(DonneesImageRGB* attitude[])
{
	char str[50]; // this varaiable will contain the name of the file who will be load
	for (int i = 0; i < NB_ATTITUDES; ++i)
	{
		sprintf(str, "sprites/oiseauRouge%d.bmp",i+1);
		attitude[i] = lisBMPRGB(str);
	}
	return 0;
}

int creeAnimation(instant animation[])
{
	for (int i = 0; i < NB_INSTANTS; ++i)
	{
		animation[i].nAttitude = i % NB_ATTITUDES;
		animation[i].x = (i * largeurFenetre()) / NB_INSTANTS;
		animation[i].y = hauteurFenetre() / 2;

	}
 	return 0;
}

void afficheAnimation (instant animation[], DonneesImageRGB* attitude[])
{
	ecrisImage(animation[step].x, animation[step].y, attitude[animation[step].nAttitude]->largeurImage, attitude[animation[step].nAttitude]->hauteurImage, attitude[animation[step].nAttitude]->donneesRGB);
}

void lectureAnimation()
{
	step++;
	step = step % NB_INSTANTS;
}