#include <stdio.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files

#include "animation.h"
#include "polynome.h"
#include "imageSF.h"

#define X_MAX_ANIMATION 620

sprite lectureImageAttitude(char nameFormat[], char nameFormat2[])
{
	sprite rv;
	char str[50]; // this varaiable will contain the name of the file who will be load
	int i = 0;
	do
	{
		sprintf(str, nameFormat,i+1);
		rv.attitude[i] = lisBMPRGB(str);
		printf("loading : %s\n", str);
		i++;
	}while(rv.attitude[i-1] != NULL);
	i--;
	rv.nb = i;
	do
	{
		sprintf(str, nameFormat2,(i - rv.nb)+1);
		printf("loading : %s\n", str);
		rv.attitude[i] = lisBMPRGB(str);
		i++;
	}while(rv.attitude[i-1] != NULL);
	if (i - 1 !=(2 * rv.nb))
	{
		printf("erro during loading i : %d, rv : %d\n",i , rv.nb);
	}
	for (i = 0; i < rv.nb*2; ++i)
	{
		printf("rv.attitude[%d]=%p\n", i,rv.attitude[i]);
	}
	printf("nb de sprite charger 2X : %d\n", rv.nb);
	return rv;
}

animation creeAnimation(nuage points, sprite attitude, int mode)
{
	animation anim;
	int u = 0;
	if (points.nb < 2)
	{
		mode = 0;
	}
	printf("nombre de sprite : %d\n", attitude.nb);
	switch(mode)
	{
		case 1 :
			printf("creeAnimationLigneBrisee\n");
			anim = creeAnimationLigneBrisee(points, attitude);
			break;
		case 2 :
			printf("creeAnimationlagrange\n");
			anim = creeAnimationLagrange(points, attitude);
			break;
		default : 
			printf("default\n");
			for(int i = 0; i < NB_INSTANTS; ++i)
			{
				anim.param[i].x = (i * X_MAX_ANIMATION) / NB_INSTANTS;
				anim.param[i].y = hauteurFenetre() / 2;
				anim.param[i].attitude = attitude.attitude[u];
				u++;
				u = u % attitude.nb;
			}
	}
	anim.current_state = 0;
	return anim ;
}

void afficheAnimation(animation anim)
{
	couleur col;
	col.r=0;
	col.v=255;
	col.b=0;
	if (anim.type >=0)
	{
		ecrisImageSansFond(anim.param[anim.current_state].x, anim.param[anim.current_state].y,
				anim.param[anim.current_state].attitude->largeurImage,
				anim.param[anim.current_state].attitude->hauteurImage,
				anim.param[anim.current_state].attitude->donneesRGB,col);
	}
	
}

animation lectureAnimation(animation anim,int etat)
{
	
	if (anim.current_state <NB_INSTANTS-1)
	{
		anim.current_state++;
	}
	else if (etat == 1)
	{
		anim.current_state = 0;
	}
	
	return anim;
}