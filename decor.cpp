#include "decor.h"

void decor(GLuint * texture){
int a=600;
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	
	glBegin(GL_QUADS);
	
	glTexCoord2d(0.3333333333333,1);  glVertex3d(a,-a,-a);
	glTexCoord2d(0.3333333333333,0.75);  glVertex3d(a,-a,a);
	glTexCoord2d(0.6666666666666,0.75);  glVertex3d(a,a,a);
	glTexCoord2d(0.6666666666666,1);  glVertex3d(a,a,-a);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0.3333333333333,0.25);  glVertex3d(-a,-a,-a);
	glTexCoord2d(0.3333333333333,0.5);  glVertex3d(-a,-a,a);
	glTexCoord2d(0.6666666666666,0.5);  glVertex3d(-a,a,a);
	glTexCoord2d(0.6666666666666,0.25);  glVertex3d(-a,a,-a);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0.6666666666666,0.25);  glVertex3d(-a,a,-a);
	glTexCoord2d(0.6666666666666,0.5);  glVertex3d(-a,a,a);
	glTexCoord2d(1,0.5);  glVertex3d(a,a,a);
	glTexCoord2d(1,0.25);  glVertex3d(a,a,-a);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0.3333333333333,0.25);  glVertex3d(-a,-a,-a);
	glTexCoord2d(0.3333333333333,0.5);  glVertex3d(-a,-a,a);
	glTexCoord2d(0,0.5);  glVertex3d(a,-a,a);
	glTexCoord2d(0,0.25);  glVertex3d(a,-a,-a);
	glEnd();
	glBegin(GL_QUADS);	
	glTexCoord2d(0.3333333333333,0.5);  glVertex3d(-a,-a,a);
	glTexCoord2d(0.6666666666666,0.5);  glVertex3d(-a,a,a);
	glTexCoord2d(0.6666666666666,0.75);  glVertex3d(a,a,a);
	glTexCoord2d(0.3333333333333,0.75);  glVertex3d(a,-a,a);
	glEnd();
	glBegin(GL_QUADS);	
	glTexCoord2d(0.3333333333333,0.25);  glVertex3d(-a,-a,-a);
	glTexCoord2d(0.3333333333333,0);  glVertex3d(-a,a,-a);
	glTexCoord2d(0.6666666666666,0);  glVertex3d(a,a,-a);
	glTexCoord2d(0.6666666666666,0.25);  glVertex3d(a,-a,-a);
	glEnd();

	
	
	glBindTexture(GL_TEXTURE_2D,texture[10]);
	glBegin(GL_QUADS);
	glTexCoord2d(0,10);  glVertex3d(-a,-a,-10);
	glTexCoord2d(0,0);  glVertex3d(-a,a,-10);
	glTexCoord2d(10,0);  glVertex3d(a,a,-10);
	glTexCoord2d(10,10);  glVertex3d(a,-a,-10);
	glEnd();	







	
}
