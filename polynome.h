#define DEGREMAX 20
#define LCH 100

#include "nuage.h"
#include "animation.h"
// This structure contain the degre , the numerator and the denominator of the polynomial 
typedef struct polynome 
{
	int degre; // contain the degre of the polynomial
	int num[DEGREMAX+1]; // contain the numerator of the polynomial
	int den[DEGREMAX+1]; // contain the denominator of the polynomial
	
}polynome;


polynome saisitPolynome(void); // Whith this function,user can enter value of degre, numerator and denominator of the polynomial

float evaluePolynome(float x, polynome P); // This function calculates the value of a polynomial

polynome derivePolynome(polynome P); // This function calculates the derivative value of polynomial

polynome integrePolynome(polynome P); // this function calculates the integer value of polynomial

polynome lagrange(nuage cloud); // interpolation de lagrange 

animation creeAnimationLigneBrisee(nuage cloud); // create trajectory in broken line