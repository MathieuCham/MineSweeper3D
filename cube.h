#ifndef cube
#define cube
#include "inclusion_graphisme.h"
#include "face.h"
#include <iostream>



class cube_{
	



	public :
		void dessiner(matrice_3 &,GLuint*,int,int);
		double x;
		double y;
		double z;
		bool creux;
		bool est_visible;
		bool mine;
		face ses_face[6];
		int indication;
		GLuint texture1;
		cube_();
		bool flag;
};


#endif
