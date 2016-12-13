#define DEGREMAX 20
#define LCH 100

typedef struct polynome
{
	int degre;
	int num[DEGREMAX+1];
	int den[DEGREMAX+1];
	
}polynome;


polynome saisitPolynome(void);

void exprimePolynome(polynome P, char expression[LCH]);

void affichePolynome(polynome P);

float evaluePolynome(float x, polynome P);

polynome derivePolynome(polynome P);

polynome integrePolynome(polynome P);

polynome lagrange(nuage cloud); // interpolation de lagrange 