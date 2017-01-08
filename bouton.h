#ifndef BOUTON_H
#define BOUTON_H

#define LONGEUR_CHAINE_BOUTON 50 // this define contain the size of the string
#define NB_BOUTON 16 // this define contain the size of the string
#define TAILLE NB_BOUTON || NB_BOUTON1
#define TAILLE_TEXTE 12 // this define contain the size of the string


// This structure create color
typedef struct color 
{
	int r;
	int v;
	int b;
}color;


// this structure define button parameters

typedef struct bouton
{
	float xmin,ymin,xmax,ymax; // this define the minimun and the maximun of the coordinate x and y
	DonneesImageRGB* image1;// this define the image
	DonneesImageRGB* image2;// this define the image
	int etat;// this define the etat of the button
	int etatEnfonce;// this define the etat of a push button
	int ancienEtat;
}bouton;

typedef struct slideBar
{
	int value; // this variable will contain the value to display from valmin to valmax
	int y; // contain the position in y
	int xmin, xmax; //contain the position in x
	int valMin, valMax; // contain the exterm value how can be contain in value
}slideBar;


void afficheBouton(bouton button[],int tailleTableau); // this function display the buton
void bouton_clic(bouton button[],int tailleTableau); // this function make change state for all the button

bouton initialiseB(char image1[], char image2[], int etatEnfonce);/*this function
initializes one button*/

color fabriqueCouleur(int r,int v,int b);//With this function we can make color
void redimensionne (bouton button[]);
void initialiseBoutons(bouton button[]);// This fonction initializes all of the boutons
slideBar slideBarInit(int xmin, int xmax, int y, int valMin, int valMax); // this function will initialyse the slide bar
slideBar slideBarSetValue(slideBar slide, int value); // this function is for change the value displays 
void printSlideBar(slideBar slide); // this funtion print the slidebrad on the screen
slideBar gereClicSlideBar(slideBar slide);

#endif
