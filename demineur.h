#ifndef dem
#define dem
#include "cube.h"
#include "controle.h"
#include "decor.h"
#include "anim.h"
#define Tx 600
#define Ty 600
#include <cmath>

struct triple_indice{
	int i1;
	int i2;
	int i3;
};

class demineur{

	public :
		int dim_x;
		int dim_y;
		int dim_z;
		cube_* element_;
		demineur(int dx,int dy,int dz);
		~demineur();
		void dessiner(GLuint * texture);
		matrice_3 orientation;
		cube_ & element(int i,int j,int k);
		int * cube_visible;
		int nb_visible;
		void up_date_visible();
		void up_date_face_visible();
		void selection_face();
		bool hold;
		void evenement();
		void OnMouseMotion();
		void OnMouseButton();
		void OnKeyboard();
		void animate(Uint32 timestep);
		void dessiner_fixe(GLuint * texture);
		int cur_x;
		int cur_y;
		SDL_Cursor * _hand1;
		SDL_Cursor * _hand2;
		triple_indice indice(int);
		double pos_x;
		double pos_y;
		double pos_z;
		triple_indice cube_selectionne;
		bool un_cube_select;
		void calculer_indication();
		triple_indice *les_mines;
		int nb_mines;
		void deminer(int i,int j,int k);
		void placer_mine(int nb_mine);
		void deminer();
		void flager();
		int wx;
		int wy;
		bool fps;
		//Pour le mode fps
		double xx;
		double xy;
		double xz;
		double zx;
		double zy;
		double zz;
		double yx;
		double yy;
		double yz;
		double rx;
		double rz;
		double angle_z;
		double angle_x;
		// Le tuning
		anim_sur_cube * an;
		anim_sur_cube & anim(int i,int j,int k){return an[i*dim_y*dim_z+j*dim_z+k];}
		anim_sur_cube * an_mine;
		anim_sur_cube & anim_mine(int i,int j,int k){return an_mine[i*dim_y*dim_z+j*dim_z+k];}
		void perdre();
		bool perdre_;

};	

void interface_graphique();
void decor(GLuint * texture);
void init_event();
double norm(double x,double y,double z);
#endif
