#define DEGREMAX 20
#define LCH 100

#include "nuage.h"
#include "animation.h"

// this structurre contain the numerator and the denominator of one quotien
typedef struct quotien
{
	unsigned int num; // contain the numerateur of the fraction
	unsigned int den; // contain the denominateur on the fraction
}quotien;

// This structure contain the degre and the coefiten of one polynome 
typedef struct polynome 
{
	int degre; // contain the degre of the polynomial
	quotien coef[DEGREMAX]; // contain the polynomial coefitien
	
}polynome;


polynome saisitPolynome(void); // Whith this function,user can enter value of degre, numerator and denominator of the polynomial

float evaluePolynome(float x, polynome P); // This function calculates the value of a polynomial

polynome derivePolynome(polynome P); // This function calculates the derivative value of polynomial

polynome integrePolynome(polynome P); // this function calculates the integer value of polynomial

polynome lagrange(nuage cloud); // interpolation de lagrange 

animation creeAnimationLigneBrisee(nuage cloud, sprite attitude); // create trajectory in broken line

void exprimePolynome(polynome P, char expression[LCH]); //print the polynomal expretion in str