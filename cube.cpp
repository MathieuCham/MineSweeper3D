#include "cube.h"

using namespace std;




void cube_::dessiner(matrice_3 & orien,GLuint * texture,int cur_x,int cur_y){

	if(est_visible){

		vecteur_3 a(1,0,0);
		vecteur_3 b(1,1,0);
		vecteur_3 c(0,1,0);
		vecteur_3 d(0,0,0);
		vecteur_3 e(1,0,1);
		vecteur_3 f(1,1,1);
		vecteur_3 g(0,1,1);
		vecteur_3 h(0,0,1);		
		vecteur_3 transla(x,y,z);
		transla=orien*transla;
		a=(orien*a)+transla;
		b=(orien*b)+transla;	
		c=(orien*c)+transla;
		d=(orien*d)+transla;
		e=(orien*e)+transla;	
		f=(orien*f)+transla;	
		g=(orien*g)+transla;
		h=(orien*h)+transla;		
		ses_face[0].set(a,b,c,d);
		ses_face[1].set(c,g,f,b);
		ses_face[2].set(a,d,h,e);
		ses_face[3].set(a,b,f,e);
		ses_face[4].set(d,c,g,h);
		ses_face[5].set(e,f,g,h);
		if(not(creux)){

			for(int i=0;i<6;i++){
				
				ses_face[i].afficher(texture);}

		}
		else{
			if((indication>0)and not(mine)){
				
				vecteur_3 po(0.5,0.5,0.5);
				po=orien*po;
				transla=transla+po;
				glTranslated(transla.val[0],transla.val[1],transla.val[2]);
					if(indication<10){
						glBindTexture(GL_TEXTURE_2D, texture[6]);
						glBegin(GL_QUADS);
						glTexCoord2d(indication*0.1,0);  glVertex3d(0.25,0,-0.25);
						glTexCoord2d(indication*0.1,1);   glVertex3d(0.25,0,0.25);
						glTexCoord2d((indication+1)*0.1,1);   glVertex3d(-0.25,0,0.25);
						glTexCoord2d((indication+1)*0.1,0);   glVertex3d(-0.25,0,-0.25);
						glEnd();
					}
					else{
						int d=indication/10;
						int u=indication%10;
						glBindTexture(GL_TEXTURE_2D, texture[7]);
						glBegin(GL_QUADS);
						glTexCoord2d(d*0.1,0);  glVertex3d(0.25,0,-0.25);
						glTexCoord2d(d*0.1,1);   glVertex3d(0.25,0,0.25);
						glTexCoord2d((d+0.5)*0.1,1);   glVertex3d(0,0,0.25);
						glTexCoord2d((d+0.5)*0.1,0);   glVertex3d(0,0,-0.25);
						glEnd();				

						glBegin(GL_QUADS);
						glTexCoord2d((u+0.5)*0.1,0);  glVertex3d(0,0,-0.25);
						glTexCoord2d((u+0.5)*0.1,1);   glVertex3d(0,0,0.25);
						glTexCoord2d((u+1)*0.1,1);   glVertex3d(-0.25,0,0.25);
						glTexCoord2d((u+1)*0.1,0);   glVertex3d(-0.25,0,-0.25);
						glEnd();				

					}
				
				//glDisable(GL_BLEND);
				glTranslated(-transla.val[0],-transla.val[1],-transla.val[2]);
			}
			else{
				if(mine){
				
					vecteur_3 po(0.5,0.5,0.5);
					po=orien*po;
					transla=transla+po;
					glBindTexture(GL_TEXTURE_2D, texture[4]);
					glTranslated(transla.val[0],transla.val[1],transla.val[2]);
					GLUquadric* params;
					params = gluNewQuadric();
					gluQuadricTexture(params,GL_TRUE);
					gluSphere(params,0.5,10,10);		
					glTranslated(-transla.val[0],-transla.val[1],-transla.val[2]);
				}
			}
		}
		
		
	}
}



cube_::cube_(){
	x=0;
	y=0;
	z=0;
	creux=false;
	est_visible=true;
	indication=0;
	mine=false;
	flag=false;
}


