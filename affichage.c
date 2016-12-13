#include <stdio.h>

#include "GfxLib.h" // Only this "#include" is needed to use graphic
#include "BmpLib.h" // with this "#include" we can treat BMP's files
#include "affichage.h"
#include "bouton.h"

void affichage(bouton button[NB_BOUTON])
{
	afficheBouton(button);
}
