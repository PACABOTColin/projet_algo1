#include <stdio.h>
#include <string.h>
#include "polynome.h"

polynome saisitPolynome(void)
{
	int i;
	polynome P;

	do
	{
		printf("Entrez le degré de votre polynome:  ");
		scanf("%d",&P.degre);
	}
	while(!(P.degre <= DEGREMAX && P.degre >=0));

	for (i=P.degre;i>=0;i--)
	{
		printf("Entrez le numérateur du degré %d:  ",i);
		scanf("%d",&P.num[i]);
		do
		{
			printf("Entrez le dénominateur du degré %d:  ",i);
			scanf("%d",&P.den[i]);
		}
		while(P.den[i] == 0);
	}
	for (i=0;i<=P.degre;i++)
	{
		printf("\nLa valeur de la case num[%d] est :   %d",i,P.num[i]);
		printf("\nLa valeur de la case den[%d] est :   %d\n",i,P.den[i]);
	}
	return P;
}


void exprimePolynome(polynome P, char expression[LCH])
{
    char signe,null,chaine[LCH];
    int i,vanum,vaden;
    expression[0]='\0';
    null='0';
    for(i = P.degre; i >= 0; i--)
    {
        if(P.num[i] != 0)
        {
            vanum=P.num[i]<0?-P.num[i]:P.num[i];
            vaden=P.den[i]<0?-P.den[i]:P.den[i];
            signe=P.num[i]*P.den[i]>0?'+':'-';
            if(i == P.degre)
            {
                if(P.num[i] < 0)
                    sprintf(chaine,"%c (%d/%d)x^%d ",signe,vanum,vaden,i);
                if(P.num[i] > 0)
                    sprintf(chaine,"(%d/%d)x^%d ",vanum,vaden,i);
            }
            else
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
		Pderive.num[i-1]=P.num[i]*i;
		Pderive.den[i-1]= P.den[i];
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
		Pintegre.num[i+1]=P.num[i];
		Pintegre.den[i+1]= P.den[i]*(i+1);
	}
	Pintegre.num[0]=0;
    Pintegre.den[0]=1;

	return Pintegre;
}

float evaluePolynome (float x, polynome P)
{
	float v=0.0;
	int i;
	
	for(i = P.degre; i >= 0; i--)
	{
		v=v*x+(P.num[i]*1.0/P.den[i]);
	}
	return v;
}


