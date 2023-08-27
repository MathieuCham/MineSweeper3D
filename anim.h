#ifndef anim_
#define anim_
#include <cmath>
#include "inclusion_graphisme.h"
#include "vecteur.h"
#include "cube.h"
#include "particule.h"
class anim{
	public:
		
		Uint32 temps_debut;
		bool active;
		virtual void start(Uint32);
		void stop(Uint32);
		virtual void update(Uint32,GLuint * texture)=0;
		particule * P;
		anim(){P=new particule[2000];}
};

class lac:public anim{
	public:
	void update(Uint32,GLuint * texture);
	void set(vecteur_3 p1,vecteur_3 p2,vecteur_3 p3,vecteur_3 p4);
	vecteur_3 p1;
	vecteur_3 p2;
	vecteur_3 p3;
	vecteur_3 p4;
};

class anim_sur_cube:public anim{

	public:
		cube_ * son_cube;
		matrice_3 * orientation;
		Uint32 durre;
		void set(cube_ * son_cube,matrice_3 * orientation);
		void update(Uint32,GLuint * texture);
		virtual void dessiner(Uint32,GLuint * texture)=0;
};


class transparence:public anim_sur_cube{
	void dessiner(Uint32,GLuint * texture);
};

class transparence_shrink:public anim_sur_cube{
	void dessiner(Uint32,GLuint * texture);
};

class transparence_dilatation:public anim_sur_cube{
	void dessiner(Uint32,GLuint * texture);
};

class feu:public anim_sur_cube{
	public :
	void dessiner(Uint32,GLuint * texture);
	void start(Uint32 t);


};

#endif
