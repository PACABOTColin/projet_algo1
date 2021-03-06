#ifndef NUAGE_H
#define NUAGE_H//this is for make shure don't make multiple inclusion on this file

/* 
 * $Date:        13. December 2016
 * $Revision: 	V.0.1
 *
 * Project: 	algorithmic project
 * Title:	    nuage.h
 *
 * Description: this file contain the function for make animation of sprite
 */

#define DIM 8 // define the number max of dote in cloud

/* this structure contain the coordinate of the dotes and the how many dote are used*/
typedef struct nuage
{
	int nb; 				//contain how many dote ar used
	float x[DIM], y[DIM]; 	//contain the coordinate of the dote
} nuage;

nuage ajoutPoint(nuage cloud, int x_min, int y_min, int x_max, int y_max); //this function add dote in cloud if the the mouse is cliked in the zone defined in argument
void dessineNuage(nuage cloud); // this function displays in the zone the cloud
void afficheLigne (nuage cloud); // this function display line between dote

#endif // NUAGE_H