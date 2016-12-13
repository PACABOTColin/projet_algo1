#define DIM 100

typedef struct nuage {
	int nb;
	float x[DIM], y[DIM];
} nuage;

typedef struct statistiques {
	float xmoy, ymoy, sx2, sxy;
} statistiques;

typedef struct droite {
	float xmin, xmax, b1, b0;
} droite;

nuage initialiseNuage(nuage cloud);
void dessineNuage(nuage cloud);

statistiques initialiseStat(nuage cloud);
droite initialiseDroite(statistiques s, nuage cloud);
void dessineDroite(droite D);
