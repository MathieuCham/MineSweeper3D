#include "anim.h"
#include "particule.h"
void anim::start(Uint32 t){
	temps_debut=t;
	active=true;
}
void anim::stop(Uint32){

	active=false;
}

void lac::update(Uint32 t,GLuint * texture){


	vecteur_3 a_,b_,c_,d_;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(255,255,255,150); 
	glBindTexture(GL_TEXTURE_2D,texture[3]);
		
	glBegin(GL_QUADS);
	double x=0.01*sin(double(t)/50);
	double z=0.0005*(double(t)/50);
	
	vecteur_3 direction(0,0,x);
	a_=p1+direction;
	b_=p2+direction;
	c_=p3+direction;
	d_=p4+direction;
	
	glTexCoord2d(z,1);  gl_jaco(a_);
	glTexCoord2d(z,0);  gl_jaco(b_);
	glTexCoord2d(1+z,0);   gl_jaco(c_);
	glTexCoord2d(1+z,1);   gl_jaco(d_);
	glEnd();
	glDisable(GL_BLEND);


}

void lac::set(vecteur_3 p1_,vecteur_3 p2_,vecteur_3 p3_,vecteur_3 p4_){

	p1=p1_;
	p2=p2_;
	p3=p3_;
	p4=p4_;
}

void anim_sur_cube::set(cube_ * son_cube_,matrice_3 * orientation_){
	son_cube=son_cube_;
	orientation=orientation_;
	active=false;
}


void anim_sur_cube::update(Uint32 t,GLuint * texture){
	if((t-temps_debut)>durre)
		stop(t);
	if(active){
		vecteur_3 transla(son_cube->x,son_cube->y,son_cube->z);
		
		vecteur_3 po(0.5,0.5,0.5);
		transla=transla+po;
		transla=(*orientation)*transla;
		glTranslated(transla.val[0],transla.val[1],transla.val[2]);
		dessiner(t,texture);
		glTranslated(-transla.val[0],-transla.val[1],-transla.val[2]);	
		
	}
}

void transparence::dessiner(Uint32 t,GLuint * texture){
		face ses_face[6];
		double r=(durre-double(t)+temps_debut)/durre;
		double k=0.5;
		double q=-0.5;		
	
		vecteur_3 a(k,q,q);
		vecteur_3 b(k,k,q);
		vecteur_3 c(q,k,q);
		vecteur_3 d(q,q,q);
		vecteur_3 e(k,q,k);
		vecteur_3 f(k,k,k);
		vecteur_3 g(q,k,k);
		vecteur_3 h(q,q,k);
		a=((*orientation)*a);
		b=((*orientation)*b);	
		c=((*orientation)*c);
		d=((*orientation)*d);
		e=((*orientation)*e);	
		f=((*orientation)*f);	
		g=((*orientation)*g);
		h=((*orientation)*h);	
		ses_face[0].set(a,b,c,d);
		ses_face[1].set(c,g,f,b);
		ses_face[2].set(a,d,h,e);
		ses_face[3].set(a,b,f,e);
		ses_face[4].set(d,c,g,h);
		ses_face[5].set(e,f,g,h);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		int col=int(exp(r-1)*sin(r*2*3.14)*255);
		glColor4ub(255,255,255,col); 		
		for(int i=0;i<6;i++){
				ses_face[i].est_visible=true;
				ses_face[i].est_select=false;	
				ses_face[i].afficher(texture);}

		glDisable(GL_BLEND);


}

void transparence_shrink::dessiner(Uint32 t,GLuint * texture){
		face ses_face[6];
		double r=(double(t)-temps_debut)/durre;
		r=r/2;
		double k=0.5-r;
		double q=-0.5+r;		
		
		
		
		vecteur_3 a(k,q,q);
		vecteur_3 b(k,k,q);
		vecteur_3 c(q,k,q);
		vecteur_3 d(q,q,q);
		vecteur_3 e(k,q,k);
		vecteur_3 f(k,k,k);
		vecteur_3 g(q,k,k);
		vecteur_3 h(q,q,k);
		a=((*orientation)*a);
		b=((*orientation)*b);	
		c=((*orientation)*c);
		d=((*orientation)*d);
		e=((*orientation)*e);	
		f=((*orientation)*f);	
		g=((*orientation)*g);
		h=((*orientation)*h);	
		ses_face[0].set(a,b,c,d);
		ses_face[1].set(c,g,f,b);
		ses_face[2].set(a,d,h,e);
		ses_face[3].set(a,b,f,e);
		ses_face[4].set(d,c,g,h);
		ses_face[5].set(e,f,g,h);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		int col=255-int(exp(r-1)*sin(r*2*3.14)*255);
		glColor4ub(255,255,255,col); 		
		for(int i=0;i<6;i++){
				ses_face[i].est_visible=true;
				ses_face[i].est_select=false;	
				ses_face[i].afficher(texture);}

		glDisable(GL_BLEND);


}

void transparence_dilatation::dessiner(Uint32 t,GLuint * texture){
		face ses_face[6];
		double r=(double(t)-temps_debut)/durre;
		r=1-r;
		double k=1-1/r;
		double q=1/r;
		vecteur_3 a(k,q,q);
		vecteur_3 b(k,k,q);
		vecteur_3 c(q,k,q);
		vecteur_3 d(q,q,q);
		vecteur_3 e(k,q,k);
		vecteur_3 f(k,k,k);
		vecteur_3 g(q,k,k);
		vecteur_3 h(q,q,k);
		a=((*orientation)*a);
		b=((*orientation)*b);	
		c=((*orientation)*c);
		d=((*orientation)*d);
		e=((*orientation)*e);	
		f=((*orientation)*f);	
		g=((*orientation)*g);
		h=((*orientation)*h);	
		ses_face[0].set(a,b,c,d);
		ses_face[1].set(c,g,f,b);
		ses_face[2].set(a,d,h,e);
		ses_face[3].set(a,b,f,e);
		ses_face[4].set(d,c,g,h);
		ses_face[5].set(e,f,g,h);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		int col=int(exp(r-1)*sin(r*2*3.14)*255);
		glColor4ub(255,255,255,col); 		
		for(int i=0;i<6;i++){
				ses_face[i].est_visible=true;
				ses_face[i].est_select=false;	
				ses_face[i].afficher(texture);}

		glDisable(GL_BLEND);


}


void feu::dessiner(Uint32 t,GLuint * texture){
	for(int i=0;i<1000;i++){
		P[i].afficher(t,texture);
	}

}

void feu::start(Uint32 t){
	temps_debut=t;
	active=true;
		for(int i=0;i<1000;i++){
				P[i].durre=500;
				P[i].start(t,double(i)/100);
				P[i].X_0=double(rand())/RAND_MAX*0.5*unite_aleatoire();
			}

}
