#include <stdio.h>
#include <math.h>
#include "polynome.h"
polynome multipliPolynome(polynome a, polynome b);
polynome additionPolynome (polynome a, polynome b);
quotien multipliQuotien(quotien a, quotien b);
int pgcd(int a, int b);

int main(int argc, char const *argv[])
{
	int i;
	polynome a, b;
	char str[100];
	for ( i = 0; i < 3; ++i)
	{
		a.coef[i].num = i;
		a.coef[i].den = 100;
	}
	a.degre = i-1;
	for (i = 0; i < 3; ++i)
	{
		b.coef[i].num = 5 - i;
		b.coef[i].den = 1;
	}
	b.degre = i - 1;
	exprimePolynome(a, str);
	printf("%s\n", str);
	exprimePolynome(b, str);
	printf("%s\n", str);
	a=multipliPolynome(b,a);
	exprimePolynome(a, str);
	printf("%s\n\n\n\n\n\n\n\n\n\n\n\n\n\n", str);

	nuage cloud;
	cloud.nb = 5;
	for (int i = 0; i < cloud.nb; ++i)
	{
		cloud.x[i] = i;
		cloud.y[i] = i*i*i*i + 3 * i + 5;
	}
/*	cloud.x[0] = 140;
	cloud.y[0] = 197;
	cloud.x[1] = 279;
	cloud.y[1] = 388;
	cloud.x[2] = 466;
	cloud.y[2] = 199;
*/
	a = lagrange(cloud);
	exprimePolynome(a, str);
	printf("%s\n", str);
	return 0;
}