#include <stdio.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "affichage.h"
#include "bouton.h"



color fabriqueCouleur(int r,int v,int b)
{
	color col;
	col.r=r;
	col.v=v;
	col.b=b;
	
	return col;
}
