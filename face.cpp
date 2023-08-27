#include "face.h"
using namespace std;
int signe(double x){
	return (x>0)?1:-1;
}


face::face(){
	est_visible=false;
	flag=false;
}

void face::set(vecteur_3 x,vecteur_3 y,vecteur_3 z,vecteur_3 t){

	point[0]=x;
	point[1]=y;
	point[2]=z;
	point[3]=t;
	barycentre.val[0]=0.25*(x.val[0]+y.val[0]+z.val[0]+t.val[0]);
	barycentre.val[1]=0.25*(x.val[1]+y.val[1]+z.val[1]+t.val[1]);
	barycentre.val[2]=0.25*(x.val[2]+y.val[2]+z.val[2]+t.val[2]);

}


bool face::point_appartient(double u,double v){
	vecteur_2 x(u,v);
	vecteur_2 a=projeter(point[0]);
	vecteur_2 b=projeter(point[1]);	
	vecteur_2 c=projeter(point[2]);
	vecteur_2 d=projeter(point[3]);
	vecteur_2 ax=x-a;
	vecteur_2 cx=x-c;
	vecteur_2 ad=d-a;
	vecteur_2 ab=b-a;
	vecteur_2 cb=b-c;
	vecteur_2 cd=d-c;
	bool e_0=signe(det(ax,ab))==signe(det(ad,ab));
	bool e_1=signe(det(ax,ad))==signe(det(ab,ad));
	bool e_2=signe(det(cx,cd))==signe(det(cb,cd));	
	bool e_3=signe(det(cx,cb))==signe(det(cd,cb));		
	return e_0 and e_1 and e_2 and e_3;
}


void face::afficher(GLuint * texture){		

	if(est_visible){
		if(not(flag)){
			if(est_select)
				glBindTexture(GL_TEXTURE_2D, texture[5]);
			else
				glBindTexture(GL_TEXTURE_2D, texture[0]);
		}
		else{
			if(est_select)
				glBindTexture(GL_TEXTURE_2D, texture[9]);
			else
				glBindTexture(GL_TEXTURE_2D, texture[8]);
		}

		glBegin(GL_QUADS);
		glTexCoord2d(0,1);  gl_jaco(point[3]);
		glTexCoord2d(0,0);  gl_jaco(point[0]);
		glTexCoord2d(1,0);  gl_jaco(point[1]);
		glTexCoord2d(1,1);  gl_jaco(point[2]);
		glEnd();
	}			

}
