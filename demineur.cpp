#include "demineur.h"
#include <iostream>
#include <cmath>
#define vit_fl 100;

using namespace std;
lac le_lac;
demineur::demineur(int dx,int dy,int dz){
	perdre_=false;
	dim_x=dx;
	dim_y=dy;
	dim_z=dz;
	pos_x=0;
	pos_y=dim_y+2;
	pos_z=0;
	cube_visible=new int[dx*dy*dz];
	element_=new cube_[dim_x*dim_y*dim_z];
	nb_visible=0;
	for(int i=0;i<dim_x;i++){
		for(int j=0;j<dim_y;j++){
			for(int k=0;k<dim_z;k++){
			element(i,j,k).x=i-dim_x/2.;
			element(i,j,k).y=j-dim_y/2.;
			element(i,j,k).z=k-dim_z/2.;
			}
		}
	}
    const char *hand1[] =
        {
            /* width height num_colors chars_per_pixel */
            " 16 16 3 1 ",
            /* colors */
            "X c #000000",
            ". c #ffffff",
            "  c None",
            /* pixels */
            "       XX       ",
            "   XX X..XXX    ",
            "  X..XX..X..X   ",
            "  X..XX..X..X X ",
            "   X..X..X..XX.X",
            "   X..X..X..X..X",
            " XX X.......X..X",
            "X..XX..........X",
            "X...X.........X ",
            " X............X ",
            "  X...........X ",
            "  X..........X  ",
            "   X.........X  ",
            "    X.......X   ",
            "     X......X   ",
            "     X......X   ",
            "0,0"
        };
    const char *hand2[] =
        {
            /* width height num_colors chars_per_pixel */
            " 16 16 3 1 ",
            /* colors */
            "X c #000000",
            ". c #ffffff",
            "  c None",
            /* pixels */
            "                ",
            "                ",
            "                ",
            "                ",
            "    XX XX XX    ",
            "   X..X..X..XX  ",
            "   X........X.X ",
            "    X.........X ",
            "   XX.........X ",
            "  X...........X ",
            "  X...........X ",
            "  X..........X  ",
            "   X.........X  ",
            "    X.......X   ",
            "     X......X   ",
            "     X......X   ",
            "0,0"
        };
 	_hand1 = cursorFromXPM(hand1);
 	_hand2 = cursorFromXPM(hand2);
	hold =false;
	SDL_SetCursor(_hand1);
	fps=false;
	
	an=new transparence_shrink[dim_x*dim_y*dim_z];
	an_mine=new feu[dim_x*dim_y*dim_z];
	for(int i=0;i<dim_x;i++){
		for(int j=0;j<dim_y;j++){
			for(int k=0;k<dim_z;k++){
				anim(i,j,k).set(&(element(i,j,k)),&(orientation));
				anim_mine(i,j,k).set(&(element(i,j,k)),&(orientation));
			}
		}
	}	
	wx=Tx;
	wy=Ty;
}
demineur::~demineur(){
	delete element_;
	delete cube_visible;
}
void interface_graphique(){
	init_event();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);
	demineur A(5,5,5);
	A.placer_mine(10);
	int a=600;
	vecteur_3 p1(-a,-a,-1);
	vecteur_3 p2(-a,a,-1);
	vecteur_3 p3(a,a,-1);
	vecteur_3 p4(a,-a,-1);
	le_lac.set(p1,p2,p3,p4);	
	A.calculer_indication();
	GLuint *texture=new GLuint[20];	
	texture[0] = loadTexture("texture/bois.jpg");
	texture[1]= loadTexture("texture/skybox_Cube.jpg");
	texture[2]= loadTexture("texture/valid.png");
	texture[3]=loadTexture("texture/water.jpg");
	texture[4]=loadTexture("texture/metal.jpg");
	texture[5]=loadTexture("texture/bois_2.jpg");
	texture[6]=loadTexture("chiffre_texture/jaco_0.jpg");
	texture[7]=loadTexture("chiffre_texture/jacobis.jpg");
	texture[8]=loadTexture("texture/crack_caution.jpg");
	texture[9]=loadTexture("texture/crack_caution_bis.jpg");
	texture[10]=loadTexture("texture/sable.jpg");
	texture[11]=loadTexture("texture/feu.jpg");	
	glEnable(GL_TEXTURE_2D);
	A.up_date_visible();
	A.up_date_face_visible();
	A.dessiner(texture);
	for (;;){
			A.evenement();
			A.dessiner(texture);						
	
	}
}
void demineur::dessiner(GLuint * texture)
{
	gluPerspective(70,(double)wx/wy,1,3000);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	
	if(fps){
		gluLookAt(pos_x,pos_y,pos_z,pos_x+yx,pos_y+yy,pos_z+yz,zx,zy,zz);
		xx=cos(angle_z);
		xy=sin(angle_z)*cos(angle_x);
		xz=0;
		zx=sin(angle_z)*sin(angle_x);
		zy=-sin(angle_x)*cos(angle_z);
		zz=cos(angle_x);
		yx=zy*xz-xy*zz;
		yy=zz*xx-xz*zx;
		yz=zx*xy-xx*zy;	
	}
	else{
	gluLookAt(pos_x,pos_y,pos_z,0,0,0,0,0,1);
	
	}
	//decor(texture);
	if(not(perdre_)){
	for(int i=0;i<nb_visible;i++){		
		element_[cube_visible[i]].dessiner(orientation,texture,cur_x,cur_y);
		anim(indice(cube_visible[i]).i1,indice(cube_visible[i]).i2,indice(cube_visible[i]).i3).update(SDL_GetTicks(),texture);
		anim_mine(indice(cube_visible[i]).i1,indice(cube_visible[i]).i2,indice(cube_visible[i]).i3).update(SDL_GetTicks(),texture);		
	}
	}
	else{
		for(int i=0;i<dim_x;i++){
			for(int j=0;j<dim_y;j++){
				for(int k=0;k<dim_z;k++){
					if(not(element(i,j,k).mine))	
						anim(i,j,k).update(SDL_GetTicks(),texture);
					else
						anim_mine(i,j,k).update(SDL_GetTicks(),texture);
					element(i,j,k).dessiner(orientation,texture,cur_x,cur_y);
				}
			}
		}
	}
	selection_face();	
	le_lac.update(SDL_GetTicks(),texture);

	glFlush();
	SDL_GL_SwapBuffers();
}
cube_ & demineur::element(int i,int j,int k){
	return element_[i*dim_y*dim_z+j*dim_z+k];
}
void demineur::up_date_visible(){
	nb_visible=0;
	for(int i=0;i<dim_x;i++){
		for(int j=0;j<dim_y;j++){
			for(int k=0;k<dim_z;k++){	
				bool cache=true;
					for(int s=-1;s<=1;s++){
						if(((i+s)>=0)and((i+s)<dim_x))
							cache=cache and not(element(i+s,j,k).creux);
						else
							cache=false;
					}

					for(int s=-1;s<=1;s++){
						if(((j+s)>=0)and((j+s)<dim_y))
							cache=cache and not(element(i,j+s,k).creux);
						else
							cache=false;
					}
					for(int s=-1;s<=1;s++){
						if(((k+s)>=0)and((k+s)<dim_z))
							cache=cache and not(element(i,j,k+s).creux);
						else
							cache=false;
					}
				if(cache){
					element(i,j,k).est_visible=false;
				}
				else{
					cube_visible[nb_visible]=i*dim_y*dim_z+j*dim_z+k;
					nb_visible++;
					element(i,j,k).est_visible=true;
				}
			}
		}
	}

}

void demineur::up_date_face_visible(){
	for(int i=0;i<nb_visible;i++){
		int gg=cube_visible[i];
		triple_indice hh=indice(gg);
		if(hh.i1==0) element_[cube_visible[i]].ses_face[4].est_visible=true;
		else element_[cube_visible[i]].ses_face[4].est_visible=element(hh.i1-1,hh.i2,hh.i3).creux;
		if(hh.i2==0) element_[cube_visible[i]].ses_face[2].est_visible=true;
		else element_[cube_visible[i]].ses_face[2].est_visible=element(hh.i1,hh.i2-1,hh.i3).creux;
		if(hh.i3==0) element_[cube_visible[i]].ses_face[0].est_visible=true;
		else element_[cube_visible[i]].ses_face[0].est_visible=element(hh.i1,hh.i2,hh.i3-1).creux;
		if(hh.i2==(dim_y-1)) element_[cube_visible[i]].ses_face[1].est_visible=true;	
		else element_[cube_visible[i]].ses_face[1].est_visible=element(hh.i1,hh.i2+1,hh.i3).creux;
		if(hh.i3==(dim_z-1)) element_[cube_visible[i]].ses_face[5].est_visible=true;
		else element_[cube_visible[i]].ses_face[5].est_visible=element(hh.i1,hh.i2,hh.i3+1).creux;
		if(hh.i1==(dim_x-1)) element_[cube_visible[i]].ses_face[3].est_visible=true;
		else element_[cube_visible[i]].ses_face[3].est_visible=element(hh.i1+1,hh.i2,hh.i3).creux;
	}
}

double norm(double x,double y,double z){
	double h=0;
	h=max(abs(x),max(abs(y),abs(z)));	
	return h;
}

triple_indice demineur::indice(int k){
	int i1;
	int i2;
	int i3;
	triple_indice gg;
	i3=k%dim_z;
	int k_prime=k/dim_z;
	i2=k_prime%dim_y;
	i1=k_prime/dim_y;
	gg.i1=i1;
	gg.i2=i2;
	gg.i3=i3;
	return gg;
}

void demineur::selection_face(){
	int gg,bb;
	vecteur_3 bary_prec;
	vecteur_3 bary;
	bool deja_une=false;
	vecteur_3 pos(pos_x,pos_y,pos_z);
	for(int i=0;i<nb_visible;i++){

		if(not(element_[cube_visible[i]].creux)){
			for(int j=0;j<6;j++){
				element_[cube_visible[i]].ses_face[j].est_select=false;
				bool est_select=element_[cube_visible[i]].ses_face[j].point_appartient(cur_x,cur_y);
				if(est_select){
					if(not(deja_une)){
						bary=element_[cube_visible[i]].ses_face[j].barycentre;
						gg=cube_visible[i];
						bb=j;
						deja_une=true;
					}
					else{		
						bary_prec=element_[gg].ses_face[bb].barycentre;
						bary=element_[cube_visible[i]].ses_face[j].barycentre;
						if(norm(bary-pos)<norm(bary_prec-pos)){
							gg=cube_visible[i];
							bb=j;
						}
				
					}
				}
			
			}
		}
		
	}
	if(deja_une){
		for(int i=0;i<6;i++)
			element_[gg].ses_face[i].est_select=true;
		cube_selectionne=indice(gg);
		un_cube_select=true;
	}
	else
		un_cube_select=false;	
}



void demineur::calculer_indication(){
	for(int i=0;i<nb_mines;i++){
		element(les_mines[i].i1,les_mines[i].i2,les_mines[i].i3).mine=true;
		int i1=les_mines[i].i1;
		int i2=les_mines[i].i2;
		int i3=les_mines[i].i3;
		for(int s1=-1;s1<=1;s1++){					
			for(int s2=-1;s2<=1;s2++){
				for(int s3=-1;s3<=1;s3++){
					if(((i1+s1)>=0)and((i1+s1)<dim_x)and((i2+s2)>=0)and((i2+s2)<dim_y)and((i3+s3)>=0)and((i3+s3)<dim_z)){
						if((abs(s1)>0)or(abs(s2)>0)or(abs(s3)>0))
							element(i1+s1,i2+s2,i3+s3).indication++;
					}
				}
			}
		}

	}
	
}

void demineur::deminer(int i,int j,int k){
	if(element(i,j,k).mine){		
		perdre();
	}
	else{
		anim(i,j,k).start(SDL_GetTicks());
		anim(i,j,k).durre=1000;

	}
	element(i,j,k).creux=true;		
	if((element(i,j,k).indication==0)){
		for(int s1=-1;s1<=1;s1++){					
			for(int s2=-1;s2<=1;s2++){
				for(int s3=-1;s3<=1;s3++){
					if(((i+s1)>=0)and((i+s1)<dim_x)and((j+s2)>=0)and((j+s2)<dim_y)and((k+s3)>=0)and((k+s3)<dim_z)){
						if((abs(s1)>0)or(abs(s2)>0)or(abs(s3)>0)){
							if((element(i+s1,j+s2,k+s3).indication==0)and(element(i+s1,j+s2,k+s3).creux==false)and(element(i+s1,j+s2,k+s3).mine==false))
								deminer(i+s1,j+s2,k+s3);
							if((element(i+s1,j+s2,k+s3).indication>0)and(element(i+s1,j+s2,k+s3).creux==false)and(element(i+s1,j+s2,k+s3).mine==false))
								element(i+s1,j+s2,k+s3).creux=true;	
								
						}
					}
				}
			}

		}
	}

}

void demineur::placer_mine(int n){
	nb_mines=n;
	les_mines=new triple_indice[nb_mines];
	srand(1);
	int i1,i2,i3;
	i1=rand()%dim_x;
	i2=rand()%dim_y;
	i3=rand()%dim_z;
	element(i1,i2,i3).mine=true;
	les_mines[0].i1=i1;
	les_mines[0].i2=i2;
	les_mines[0].i3=i3;			
	for(int i=1;i<nb_mines;i++){
		i1=rand()%dim_x;
		i2=rand()%dim_y;
		i3=rand()%dim_z;
		while(element(i1,i2,i3).mine==true){
			i1=rand()%dim_x;
			i2=rand()%dim_y;
			i3=rand()%dim_z;
		}		
		element(i1,i2,i3).mine=true;
		les_mines[i].i1=i1;
		les_mines[i].i2=i2;
		les_mines[i].i3=i3;
	}
}

void demineur::deminer(){
	if(un_cube_select){
		deminer(cube_selectionne.i1,cube_selectionne.i2,cube_selectionne.i3);
		up_date_visible();
		up_date_face_visible();
		un_cube_select=false;	
	}
}

void demineur::flager(){
	if(un_cube_select){
		for(int i=0;i<6;i++)
			element(cube_selectionne.i1,cube_selectionne.i2,cube_selectionne.i3).ses_face[i].flag=not(element(cube_selectionne.i1,cube_selectionne.i2,cube_selectionne.i3).ses_face[i].flag);
		up_date_visible();
		up_date_face_visible();
		un_cube_select=false;	
	}
}

void demineur::perdre(){
	perdre_=true;
	for(int i=0;i<dim_x;i++){
		for(int j=0;j<dim_y;j++){
			for(int k=0;k<dim_z;k++){
				if(not(element(i,j,k).creux)){
					element(i,j,k).creux=true;
					if(element(i,j,k).mine){		
						anim_mine(i,j,k).start(SDL_GetTicks());
						anim_mine(i,j,k).durre=10000;
					}
					else{
						anim(i,j,k).start(SDL_GetTicks());
						anim(i,j,k).durre=100;
					}
				}		
			}
		}
	}

}
