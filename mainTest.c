#include <stdio.h>
#include <math.h>
#include "polynome.h"
polynome multipliPolynome(polynome a, polynome b);

int main(int argc, char const *argv[])
{
	int i;
	polynome a, b;
	char str[LCH];
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
	for (int u = 2; u < 18; ++u)
	{
		cloud.nb = u;
		for (int i = 0; i < cloud.nb; ++i)
		{
			cloud.x[i] = i;
			cloud.y[i] = i * i;
		}
		a = lagrange(cloud);
		exprimePolynome(a, str);
		printf("%s\n", str);
	}
	cloud.nb = 5;

	return 0;
}
