#define DIMCURVE 1000 //this define the dimension of the curve

// this structure create points
typedef struct points
{
		float x; //create the coordinate in x
		float y; //create the coordinate in y
}points;

// this structure create curves
typedef struct courbe
{
		int nb; //create the number of step
		float xmin,ymin,xmax,ymax; // this define the minimun and the maximun of the coordinate x and y
		char expression[LCH]; //create string of LCH
		points trace[DIMCURVE]; //trace the curve
}courbe; 

// this structure give information about graphic like color ...
typedef struct mode
{
	int rougeTrait,vertTrait,bleuTrait; //with this we can choose the color of the line
	int epaisseurTrait,police,epaisseurTexte; //with this we can choose the thickness of the line
	int rougeTexte,vertTexte,bleuTexte; //with this we can choose the color of the text
}mode;


courbe initialiseCourbe(polynome P, float xmin, float xmax, int nbpts); //this function initialize the curve
void afficheCourbePoint(courbe C, mode M,float x0,float y0); //this function display the point of the curve


