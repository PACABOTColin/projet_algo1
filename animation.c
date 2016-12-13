#include <stdio.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files

#include "animation.h"

#define X_MAX_ANIMATION 620

int lectureImageAttitude(DonneesImageRGB* attitude[], char nameFormat[])
{
	char str[50]; // this varaiable will contain the name of the file who will be load
	int i = 0;
	do
	{
		sprintf(str, nameFormat,i+1);
		attitude[i] = lisBMPRGB(str);
		i++;
	}while(attitude[i-1] != NULL);
	return 0;
}

animation creeAnimation(nuage points, DonneesImageRGB* attitude[], int mode)
{
	animation anim;
	int u = 0;
	for(int i = 0; i < NB_INSTANTS; ++i)
	{
		anim.param[i].nAttitude = i % NB_ATTITUDES;
		anim.param[i].x = (i * X_MAX_ANIMATION) / NB_INSTANTS;
		anim.param[i].y = hauteurFenetre() / 2;
		if(attitude[u] == NULL)
		{
			u = 0;
		}
		anim.param[i].attitude = attitude[u];
		u++;
	}
	anim.current_state = 0;
 	return anim ;
}

void afficheAnimation(animation anim)
{
	ecrisImage(anim.param[anim.current_state].x, anim.param[anim.current_state].y,
				anim.param[anim.current_state].attitude->largeurImage,
				anim.param[anim.current_state].attitude->hauteurImage,
				anim.param[anim.current_state].attitude->donneesRGB);
}

animation lectureAnimation(animation anim)
{
	anim.current_state++;
	anim.current_state = anim.current_state % NB_INSTANTS;
	printf("pas : %d\n", anim.current_state);
	return anim;
}

void freeImages(animation anim)
{
	for (int i = 0; i < NB_ATTITUDES; ++i)
	{
		libereDonneesImageRGB(&anim.param[i].attitude);
	}
}