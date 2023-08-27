#ifndef face_
#define face_
#include "inclusion_graphisme.h"
#include "sdlglutils.h"
#include "vecteur.h"
#include <iostream>
class face{
	public :
		vecteur_3 point[4];
		vecteur_3 barycentre;
		bool est_select;
		bool est_visible;
		bool point_appartient(double x,double y);
		void set(vecteur_3,vecteur_3,vecteur_3,vecteur_3);
		face();
		void afficher(GLuint * texture);
		bool flag;

};


int signe(double a);

#endif
