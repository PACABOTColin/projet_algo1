#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GfxLib.h"
#include "animation.h"
#include "polynome.h"
#include "nuage.h"

 double pgcd(double a, double b)
{
	int r;
	// calculate the PGCD of two number
	if (a < 0) 
	{
		a = -a;
	}
	if (b < 0) 
	{
		b = -b;
	}
	while (b != 0)
	{
		r = fmod(a, b);
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
	if(a.num == 0)
	{
		a.den = 1;
	}
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
     if(strlen(expression) > LCH)
     {
     	printf("\nerror, str too big\n");
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
#ifdef debug
	char str[LCH];
	exprimePolynome(a, str);
	printf("[%s]\t+\t", str);
	exprimePolynome(b, str);
	printf("[%s]\t=\t", str);
#endif
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
#ifdef debug
	exprimePolynome(a, str);
	printf("[%s]\n", str);
#endif
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
#ifdef debug
	char str[LCH];
#endif
	rv = initialise_polynome(0);
	for (int i = 0; i <= a.degre; ++i)
	{
		for (int u = 0; u <= b.degre; ++u)
		{
			polynome tmp = initialise_polynome(0);
			tmp.degre = u + i;
			tmp.coef[tmp.degre] = multipliQuotien(a.coef[i], b.coef[u]); // multiply one term of the first polynome to the other polynome
			rv = additionPolynome(tmp, rv); // and addition the resuld to the return polynome
		}
	}
#ifdef debug
	exprimePolynome(a, str);
	printf("[%s]", str);
	exprimePolynome(b, str);
	printf("    [%s]", str);
	exprimePolynome(rv, str);
	printf("    = %s\n", str);
#endif
	return rv;
}

polynome lagrange (nuage cloud)
{
	polynome rv, tmp, tmp2;
	rv = initialise_polynome(0);
	for (int i = 0; i < cloud.nb; ++i) // sum of ly
	{
		tmp = initialise_polynome(1);
		for (int j = 0; j < cloud.nb; ++j) //li
		{
			//printf("i : %d\tj : %d\n", i, j); 
			//product of différent term of li
			if(i != j)
			{
				tmp2.degre = 1;
				tmp2.coef[0].num = -cloud.x[j];
				tmp2.coef[0].den = cloud.x[i] - cloud.x[j];
				tmp2.coef[1].den = cloud.x[i] - cloud.x[j];
				tmp2.coef[1].num = 1;
				tmp = multipliPolynome(tmp2, tmp);
				//affichePolynome(tmp);
			}
		}
		tmp2 = initialise_polynome(0);
		tmp2.degre = 0;
		tmp2.coef[0].num = cloud.y[i];
		tmp = multipliPolynome(tmp2, tmp);
		rv = additionPolynome(rv, tmp);
	}
#ifdef DEBUG
	affichePolynome(rv);
#endif
	return rv;
}

polynome newton(nuage cloud)
{
	quotien tmp, tmp2, tmp3;
	polynome rv;
	for(int i = 0; i < cloud.nb; i++)
	{
		tmp.den = 0;
		tmp.num = 1;
		for (int u = 0; u < i; ++u)
		{
			tmp2.den = cloud.x[u];
			tmp2.num = 1;
			for (int v = 0; v < i; ++v)
			{
				if (i != u && cloud.x[u] - cloud.x[v] != 0)
				{
					tmp3.num = 1;
					tmp3.den = cloud.x[u] - cloud.x[v];
					tmp2 = multipliQuotien(tmp2, tmp3);
				}
			}
			tmp = additionQuotien(tmp, tmp2);
		}
		rv.coef[i] = tmp;
	}
#ifdef DEBUG
	affichePolynome(rv);
#endif
	return rv;
}

animation creeAnimationLigneBrisee(nuage cloud, sprite attitude)
{
	animation rv;
	float total_lenght = 0;
	float step_lenght[DIM + 1] = {0};

	for (int i = 0; i < cloud.nb - 1; ++i) // calculate the x ditance of the curve
	{
		total_lenght += sqrtf(powf(cloud.x[i] - cloud.x[i + 1], 2) + powf(cloud.y[i] - cloud.y[i + 1], 2));
		step_lenght[i + 1]= total_lenght;
	}

	int i;
	int tmp = 0;
	int offset = 0;
	for (i = 0; i< NB_INSTANTS; i++)
	{
		if(i > 0 && (total_lenght * i) / NB_INSTANTS  > step_lenght[tmp + 1])
		{
			tmp++;
			if(cloud.x[tmp] < cloud.x[tmp + 1])
			{
				offset = 0;
			}
			else
			{
				offset = attitude.nb;
			}
		}
		rv.param[i].x = (((total_lenght * i) / NB_INSTANTS) - (step_lenght[tmp])) * (cloud.x[tmp + 1] - cloud.x[tmp]) / (step_lenght[tmp + 1] - step_lenght[tmp]) + cloud.x[tmp];
					//  (in 								- in_min)          * (out_max          - out_min)      / (in_max               - in_min)           + out_min
		rv.param[i].y = (((total_lenght * i) / NB_INSTANTS) - step_lenght[tmp]) * (cloud.y[tmp + 1] - cloud.y[tmp]) / (step_lenght[tmp + 1] - step_lenght[tmp]) + cloud.y[tmp];
		rv.param[i].attitude = attitude.attitude[(i%attitude.nb) + offset]; // set the picture of sprite
	}
	return rv;
}

animation creeAnimationLagrange (nuage points, sprite attitude)
{
	animation rv;
	rv.type = 2;
	rv.current_state = 0;
	for (int i = 0; i < points.nb; ++i)
	{
		printf("(%.0f,%.0f)\n", points.x[i], points.y[i]);
	}
	polynome poly = lagrange(points);
	for (int i = 0; i < NB_INSTANTS; ++i)
	{
		rv.param[i].x = (i * (largeurFenetre() - 130)) / NB_INSTANTS;
		rv.param[i].y = evaluePolynome(rv.param[i].x, poly);
		rv.param[i].y = rv.param[i].y < 93 ? 93 : rv.param[i].y;
		rv.param[i].attitude = attitude.attitude[i % attitude.nb];
		printf("step %d x:%d\t y:%d img n°:%d ->%p\n",i,  rv.param[i].x, rv.param[i].y, i % attitude.nb, rv.param[i].attitude);
	}
	return rv;
}

animation creeAnimationNewton (nuage points, sprite attitude)
{
	animation rv;
	rv.type = 2;
	rv.current_state = 0;
	for (int i = 0; i < points.nb; ++i)
	{
		printf("(%.0f,%.0f)\n", points.x[i], points.y[i]);
	}
	polynome poly = newton(points);
	for (int i = 0; i < NB_INSTANTS; ++i)
	{
		rv.param[i].x = (i * (largeurFenetre() - 130)) / NB_INSTANTS;
		rv.param[i].y = evaluePolynome(rv.param[i].x, poly);
		rv.param[i].y = rv.param[i].y < 93 ? 93 : rv.param[i].y;
		rv.param[i].attitude = attitude.attitude[i % attitude.nb];
		printf("step %d x:%d\t y:%d img n°:%d ->%p\n",i,  rv.param[i].x, rv.param[i].y, i % attitude.nb, rv.param[i].attitude);
	}
	return rv;
}
