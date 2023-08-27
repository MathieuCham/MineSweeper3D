#ifndef partic
#define partic
#include <cmath>
#include "inclusion_graphisme.h"
#include "vecteur.h"
#include "cube.h"
#include <iostream>
using namespace std;
class particule{
	public:
	vecteur_3 X_0;	
	vecteur_3 V_0;
	vecteur_3 X;
	vecteur_3 f;
	bool active;
	Uint32 durre;
	Uint32 temps_init;
	void afficher(Uint32 t,GLuint * texture);
	void start(Uint32 t,double);
};



bool in_N(double j);

vecteur_3 unite_aleatoire();
#endif
