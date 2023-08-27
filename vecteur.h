#ifndef vecteur
#define vecteur
#include "inclusion_graphisme.h"
#include "sdlglutils.h"
#include <iostream>
#include <cmath>
class vecteur_2{
	public :
		double * val;
		vecteur_2();
		vecteur_2(double x,double y);
		vecteur_2 &operator=(const vecteur_2 &);
		vecteur_2(const vecteur_2 &);
		void afficher(){fprintf(stderr,"(%f,%f)\n",val[0],val[1]);}
		~vecteur_2(){delete val;}
};

class matrice_3{

	public:
		double * val;
		matrice_3();
		double & operator()(int,int)const;
		matrice_3 & operator=(const matrice_3 &);
		matrice_3(const matrice_3 &);
		~matrice_3(){delete val;}
		void afficher();
};

class vecteur_3{

	public :
		double * val ;
		vecteur_3 & operator=(const vecteur_3 & D);
		vecteur_3();
		vecteur_3(double,double,double);
		void afficher();
		vecteur_3(const vecteur_3 &);
		~vecteur_3(){delete val;}
		
};


matrice_3 operator*(matrice_3 ,matrice_3 );
vecteur_3 operator*(const matrice_3 &,const vecteur_3 &);
void gl_jaco(vecteur_3 & v);
vecteur_2 operator-(vecteur_2 a,vecteur_2 b);
vecteur_2 operator+(vecteur_2 a,vecteur_2 b);
vecteur_3 operator+(vecteur_3 a,vecteur_3 b);
vecteur_3 operator-(vecteur_3 a,vecteur_3 b);
vecteur_3 operator*(double a,vecteur_3 b);
vecteur_2 projeter(vecteur_3);
double norm(vecteur_3);
double det(vecteur_2 a,vecteur_2 b);

#endif
