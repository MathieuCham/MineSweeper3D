#include "particule.h"



void particule::afficher(Uint32 t,GLuint * texture){

	if(in_N(double(t-temps_init)/durre)){
		V_0=unite_aleatoire();
		
	}
	if(active){
		double tm=t-temps_init-durre*floor(double(t-temps_init)/durre);

		tm=double(tm)/1000;
		f.val[2]=3;
	
		X=(0.5*tm*tm)*f+tm*V_0+X_0;

		
	/*	vecteur_3 v1(0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX);
		vecteur_3 v2(0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX);
		vecteur_3 v3(0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX);
		vecteur_3 v4(0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX,0.05*double(rand())/RAND_MAX);
	*/
		double l=0.05;
		vecteur_3 v1(l,0,l);
		vecteur_3 v2(-l,0,l);
		vecteur_3 v3(-l,0,-l);
		vecteur_3 v4(l,0,-l);
		
		v1=X+v1;
		v2=X+v2;		
		v3=X+v3;
		v4=X+v4;
		glBindTexture(GL_TEXTURE_2D,texture[11]);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


		
		double j=tm*1000/durre;
//	glColor4ub(255,255,255,255-255*j); 
		glBegin(GL_QUADS);

		glTexCoord2d(j,1); gl_jaco(v1);
		glTexCoord2d(j,1); gl_jaco(v2);
		glTexCoord2d(j,1); gl_jaco(v3);
		glTexCoord2d(j,1); gl_jaco(v4);
		glEnd();
	//glDisable(GL_BLEND);
		
	}
}

void particule::start(Uint32 t,double id){
	active=true;
	Uint32 decal;
	decal=Uint32(durre*id);
	temps_init=t+decal;
}

bool in_N(double j){
	return floor(j)==j;
}

vecteur_3 unite_aleatoire(){

	double theta=double(rand())/RAND_MAX*2*3.14;
	double phi=double(rand())/RAND_MAX*2*3.14;
	vecteur_3 u(cos(theta)*sin(phi),sin(theta)*sin(phi),cos(phi));

	return u;
}
