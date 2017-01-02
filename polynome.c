#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animation.h"
#include "polynome.h"
#include "nuage.h"

 int pgcd(int a, int b)
{
  int r;
  while (b != 0)
    {
      r = a%b;
      a = b;
      b = r;
    }
  return a;
}

quotien simplifiQuotien (quotien a)
{
	// simplify the sine
	if(a.den < 0) 
	{
		a.den = abs(a.den);
		a.num = 0 - a.num;
	}
	// simplyfy the number of quotien
	int d = pgcd(a.num, a.den);
	a.num = a.num / d;
	a.den = a.den / d;
	return a;
}

quotien additionQuotien(quotien a, quotien b)
{
	quotien rv;
	rv.num = a.den * b.num + b.den * a.num;
	rv.den = a.den * b.den;
	rv = simplifiQuotien(rv);
	return rv;
}

quotien multipliQuotien(quotien a, quotien b)
{
	quotien rv;
	rv.num = a.num * b.num;
	rv.den = a.den * b.den;
	rv = simplifiQuotien(rv);
	return rv;
}

void exprimePolynome(polynome P, char expression[LCH])
{
    char signe,null,chaine[LCH];
    int i,vanum,vaden;
    expression[0]='\0';
    null='0';
    for(i = P.degre; i >= 0; i--)
    {
        if(P.coef[i].num != 0)
        {
            vanum = P.coef[i].num < 0 ? -P.coef[i].num : P.coef[i].num;
            vaden = P.coef[i].den;
            signe = P.coef[i].num > 0 ? '+' : '-' ;
            if(i == P.degre)
            {
                if(P.coef[i].num < 0)
                    sprintf(chaine,"%c (%d/%d)x^%d ",signe,vanum,vaden,i);
                if(P.coef[i].num > 0)
                    sprintf(chaine,"(%d/%d)x^%d ",vanum,vaden,i);
            }
            sprintf(chaine,"%c(%d/%d)x^%d ",signe,vanum,vaden,i);
            if(i == 1 && i != P.degre)
                sprintf(chaine,"%c(%d/%d)x",signe,vanum,vaden);
            if(i == 0 && i != P.degre)
                sprintf(chaine,"%c(%d/%d)",signe,vanum,vaden);
            if(i == 1 && i == P.degre)
                sprintf(chaine,"(%d/%d)x",vanum,vaden);
            if(i == 0 && i == P.degre)
                sprintf(chaine,"%d/%d",vanum,vaden);
            if(vaden == 1)
                sprintf(chaine,"%c%dx^%d",signe,vanum,i);
 
            if(vaden == 1 && i == P.degre && vanum != 1)
                sprintf(chaine,"%dx^%d ",vanum,i);
            if(vaden == 1 && i == P.degre && vanum == 1)
                sprintf(chaine,"x^%d ",i);
            if(vaden == 1 && i == 0 && i != P.degre)
                sprintf(chaine,"%c%d ",signe,vanum);
            if(vaden == 1 && i == 1 && i != P.degre)
                sprintf(chaine,"%c%d*x ",signe,vanum);
            if(vaden == 1 && i == 0 && i == P.degre)
                sprintf(chaine,"%d ",vanum);
            if(vaden == 1 && i == 1 && i == P.degre)
                sprintf(chaine,"%d*x ",vanum);
            strcat(expression,chaine);
        }
    }
    if(P.degre == -1)
        sprintf(expression,"%c",null);
}

void affichePolynome(polynome P)
{
	char expression [LCH];

	exprimePolynome(P,expression);
	printf(" %s\n",expression);
}

polynome derivePolynome(polynome P)
{
	polynome Pderive;
	int i;

	Pderive.degre = (P.degre ==0)?0:P.degre-1;
	for(i=1;i<= P.degre;i++)
	{
		Pderive.coef[i-1].num=P.coef[i].num*i;
		Pderive.coef[i-1].den= P.coef[i].den;
	}
	return Pderive;
}

polynome integrePolynome(polynome P)
{
	polynome Pintegre;
	int i;
    
	Pintegre.degre = P.degre + 1;
	for(i=Pintegre.degre;i>=0;i--)
	{
		Pintegre.coef[i+1].num=P.coef[i].num;
		Pintegre.coef[i+1].den= P.coef[i].den*(i+1);
	}
	Pintegre.coef[0].num=0;
    Pintegre.coef[0].den=1;

	return Pintegre;
}

float evaluePolynome (float x, polynome P)
{
	float v=0.0;
	int i;
	
	for(i = P.degre; i >= 0; i--)
	{
		v=v*x+(P.coef[i].num/P.coef[i].den);
	}
	return v;
}

polynome additionPolynome (polynome a, polynome b)
{
	if (a.degre < b.degre) // make the polynoma a the whith the hies degres
	{
		polynome c = a;
		a = b;
		b = c;
	}
	for (int i = 0; i <= b.degre; ++i) // addition different quotient of the polinome
	{
		a.coef[i] = additionQuotien(a.coef[i], b.coef[i]);
	}
	return a;
}

polynome initialise_polynome(int c)
{
	polynome rv;
	for (int i = 0; i < DEGREMAX; ++i) // initialyse polynome with one constante in 
	{
		rv.coef[i].num = c;
		rv.coef[i].den = 1;
	}
	rv.degre = 0;
	return rv;
}

polynome multipliPolynome(polynome a, polynome b)
{
	polynome rv;
	char str[100];
	rv = initialise_polynome(0);
	for (int i = 0; i <= a.degre; ++i)
	{
		for (int u = 0; u <= b.degre; ++u)
		{
			polynome tmp = initialise_polynome(0);
			tmp.degre = u + i;
			tmp.coef[tmp.degre] = multipliQuotien(a.coef[i], b.coef[u]); // multiply one term of the first polynome to the other polynome
			rv = additionPolynome(tmp, rv); // and addition the resuld to the return polynome
			exprimePolynome(rv, str);
		}
	}
	rv.degre = a.degre + b.degre;
	return rv;
}

polynome lagrange (nuage cloud)
{
	char str[100];
	polynome rv, tmp, tmp2;
	rv = initialise_polynome(0);
	for (int i = 0; i < cloud.nb; ++i) // sum of ly
	{
		tmp = initialise_polynome(1);
		tmp.degre = 0;
		exprimePolynome(tmp, str);
		//printf("tmp : %s\n", str);
		for (int j = 0; j < cloud.nb; ++j) //li
		{
			//printf("i : %d\tj : %d\n", i, j); 
			//product of différent term of li
			if(i != j)
			{
				tmp2 = initialise_polynome(1);
				tmp2.degre = 1;
				tmp2.coef[0].num = -cloud.x[j];
				tmp2.coef[0].den = cloud.x[i] - cloud.x[j];
				tmp2.coef[1].den = cloud.x[i] - cloud.x[j];
				tmp2.coef[1].num = 1;
				tmp = multipliPolynome(tmp2, tmp);
				exprimePolynome(tmp2, str);
				//printf("tmp : %s, degre :%d \n", str, tmp.degre);
			}
		}
		tmp2 = initialise_polynome(0);
		tmp2.degre = 0;
		tmp2.coef[0].num = cloud.y[i];
		tmp = multipliPolynome(tmp2, tmp);
		rv = additionPolynome(rv, tmp);
		//exprimePolynome(rv, str);
		//printf("--------->rv : %s\n", str);
	}
	return rv;
}

polynome newton(nuage cloud)
{

}

animation creeAnimationLigneBrisee(nuage cloud, sprite attitude)
{
	animation rv;
	float lenght = 0;
	for (int i = 0; i < cloud.nb - 1; ++i) // calculate the x ditance of the curve
	{
		lenght += abs(cloud.x[i] - cloud.x[i + 1]);
	}
	int k = 0;
	float b = 0;
	int i;
	int offset = 0;
	int tmp = 0;
	for (i = 0; i< NB_INSTANTS; i++)
	{
		if(cloud.x[k] < cloud.x[k + 1])
		{
			rv.param[i].x = cloud.x[k] + ((i - tmp) * lenght) / NB_INSTANTS; // calculate new x prosition
			offset = 0; // to use the picture forwarde to right
		}
		else
		{
			rv.param[i].x = cloud.x[k] - ((i - tmp) * lenght) / NB_INSTANTS; // calculate new x prosition
			offset = attitude.nb; // to use the picture forwarde to left
		}
		if((rv.param[i].x >= cloud.x[k + 1] && cloud.x[k] < cloud.x[k + 1])
			|| (rv.param[i].x <= cloud.x[k + 1] && cloud.x[k] > cloud.x[k + 1])) // update the position in the dote cloud
		{
			k ++;
			tmp = i;
		}
		b = (cloud.y[k + 1] - cloud.y[k]) / (cloud.x[k + 1] - cloud.x[k]);
		rv.param[i].y = b * rv.param[i].x + cloud.y[k] - b * cloud.x[k]; // caculate the y position
		rv.param[i].attitude = attitude.attitude[(i%attitude.nb) + offset]; // set the picture of sprite
	}
	return rv;
}