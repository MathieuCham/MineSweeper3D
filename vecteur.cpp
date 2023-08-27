#include "vecteur.h"
using namespace std;

matrice_3::matrice_3(){
		val=new double[9];
	for(int i=0;i<9;i++)
		val[i]=0;
	(*this)(0,0)=1;
	(*this)(1,1)=1;
	(*this)(2,2)=1;
}


double & matrice_3::operator()(int i,int j)const{
	return(val[3*i+j]);
}

matrice_3 operator *(matrice_3  A,matrice_3  B){

	matrice_3 C;

	
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				C(i,j)=0;
				for(int k=0;k<3;k++)
					C(i,j)+=A(i,k)*B(k,j);
			}
		}
		

	return C;
}

matrice_3 & matrice_3::operator=(const matrice_3 & c){

		for(int i=0;i<9;i++)
			val[i]=c.val[i];
		return *this;
}

vecteur_3 & vecteur_3::operator=(const vecteur_3 & D){
	for(int i=0;i<3;i++){val[i]=D.val[i];};return *this;}
	
	
vecteur_3 operator*(const matrice_3 & A,const vecteur_3 & B){

	vecteur_3 C;
	for(int i=0;i<3;i++){
			C.val[i]=0;
		for(int j=0;j<3;j++)
			C.val[i]+=A(i,j)*B.val[j];
	}
	return C;
}	

vecteur_3::vecteur_3(){
	val =new double[3];
	for(int i=0;i<3;i++)
		val[i]=0;
}

void gl_jaco(vecteur_3 & v){
	glVertex3d(v.val[0],v.val[1],v.val[2]);
}



vecteur_3::vecteur_3(double x,double y,double z){
	val=new double[3];
	val[0]=x;
	val[1]=y;
	val[2]=z;

}
void vecteur_3::afficher(){

	fprintf(stderr,"(%f,%f,%f) \n",val[0],val[1],val[2]);
}


void matrice_3::afficher(){
	fprintf(stderr,"\n");
	for(int i=0;i<3;i++){
		fprintf(stderr,"(%f,%f,%f) \n",(*this)(i,0),(*this)(i,1),(*this)(i,2));
	}
}


vecteur_2::vecteur_2(){
	val=new double[2];
	for(int i=0;i<2;i++)
		val[i]=0;
}

vecteur_2::vecteur_2(double x, double y){
		val=new double[2];
		val[0]=x;
		val[1]=y;
}


double det(vecteur_2 a,vecteur_2 b){
	return a.val[0]*b.val[1]-a.val[1]*b.val[0];
}


vecteur_2 operator-(vecteur_2 a,vecteur_2 b){
	vecteur_2 c;
	c.val[0]=a.val[0]-b.val[0];
	c.val[1]=a.val[1]-b.val[1];
	return c;
}

vecteur_2 operator+(vecteur_2 a,vecteur_2 b){
	vecteur_2 c;
	c.val[0]=a.val[0]+b.val[0];
	c.val[1]=a.val[1]+b.val[1];
	return c;
}

vecteur_3 operator-(vecteur_3 a,vecteur_3 b){
	vecteur_3 c;
	c.val[0]=a.val[0]-b.val[0];
	c.val[1]=a.val[1]-b.val[1];
	c.val[2]=a.val[2]-b.val[2];	
	return c;
}

vecteur_3 operator+(vecteur_3 a,vecteur_3 b){
	vecteur_3 c;
	c.val[0]=a.val[0]+b.val[0];
	c.val[1]=a.val[1]+b.val[1];
	c.val[2]=a.val[2]+b.val[2];	
	return c;
}

vecteur_3::vecteur_3(const vecteur_3 & y){
	val=new double[3];
	for(int i=0;i<3;i++)
		val[i]=y.val[i];
}

vecteur_2::vecteur_2(const vecteur_2 & y){
	val=new double[2];
	for(int i=0;i<2;i++)
		val[i]=y.val[i];
}

matrice_3::matrice_3(const matrice_3 & g){
	val=new double[9];
	for(int i=0;i<9;i++)
		val[i]=g.val[i];
}

vecteur_2 projeter(vecteur_3 a){
	GLdouble X,Y,Z;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
	int r=gluProject(a.val[0],a.val[1],a.val[2],modelview,projection,viewport, &X, &Y, &Z);
	vecteur_2 b(X,Y);
	return b;
}

double norm(vecteur_3 v){

	return sqrt(pow(v.val[0],2)+pow(v.val[1],2)+pow(v.val[2],2));
}
vecteur_3 operator*(double a,vecteur_3 b){
	vecteur_3 c(a*b.val[0],a*b.val[1],a*b.val[2]);
	return c;
}
