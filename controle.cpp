#include "demineur.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;
typedef map<SDLKey,bool> Keystates;
typedef map<std::string,SDLKey> KeyConf;

SDL_Event event;
Keystates keystates;
KeyConf keyconf;

Uint32 last_time,current_time,elapsed_time; //for time animation
Uint32 start_time,stop_time; //for frame limit
const Uint32 time_per_frame = 100;

void demineur::evenement(){
	while(SDL_PollEvent(&event))
        {
		switch(event.type){
			case SDL_QUIT:
				exit(0);
			case SDL_KEYDOWN:
				if(event.key.keysym.sym==SDLK_ESCAPE)
					exit(0);
				if(event.key.keysym.sym==SDLK_d){
					deminer();
					
				}
				if(event.key.keysym.sym==SDLK_f){
					flager();
				}
				if(event.key.keysym.sym==SDLK_g){
					fps=not(fps);
					if(fps){
						SDL_WM_GrabInput(SDL_GRAB_ON);
						SDL_ShowCursor(SDL_DISABLE);
					}
					else{

						hold =false;
						SDL_SetCursor(_hand1);
						SDL_WM_GrabInput(SDL_GRAB_OFF);
						SDL_ShowCursor(SDL_ENABLE);	
					}
						
				}
				OnKeyboard();
			break;
			case SDL_MOUSEMOTION:
				OnMouseMotion();
			case SDL_KEYUP:
				OnKeyboard();			
			break;
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButton();
		break;

		}

	}
	current_time = SDL_GetTicks();
	elapsed_time = current_time - last_time;
	last_time = current_time;
	animate(elapsed_time);


}

void init_event(){

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	SDL_WM_SetCaption("Le demineur du jaco", NULL);
	SDL_SetVideoMode(Tx, Ty, 32, SDL_OPENGL);
	start_time = SDL_GetTicks();
	keyconf["straff_gauche"] = SDLK_LEFT;
	keyconf["straff_droit"] = SDLK_RIGHT;
	keyconf["arriere"] = SDLK_DOWN;	
	keyconf["avant"] = SDLK_UP;

	
	
	keystates[keyconf["straff_droit"]] = false;
	keystates[keyconf["straff_gauche"]] = false;
	keystates[keyconf["arriere"]] = false;
	keystates[keyconf["avant"]] = false;
	
	
	
	
	SDL_WM_GrabInput(SDL_GRAB_OFF);



}

void demineur::OnMouseMotion(){
	if(not(fps)){
		if(hold){
			double dth_z=event.motion.xrel*0.01;
			double dth_x=-event.motion.yrel*0.01;
			matrice_3 R_z;
			matrice_3 R_x;
			if(abs(event.motion.xrel)>abs(event.motion.yrel)){
			R_z(0,0)=cos(dth_z);
			R_z(1,1)=cos(dth_z);
			R_z(0,1)=-sin(dth_z);
			R_z(1,0)=sin(dth_z);
			}
			if(abs(event.motion.xrel)<abs(event.motion.yrel)){
			R_x(1,1)=cos(dth_x);
			R_x(2,2)=cos(dth_x);
			R_x(1,2)=-sin(dth_x);
			R_x(2,1)=sin(dth_x);		
			}	
		
			orientation=R_z*orientation;
			orientation=R_x*orientation;

		}
			else{

			cur_x=event.motion.x;
			cur_y=Ty-event.motion.y;

			}
	}
	else{
		angle_z-=0.003*event.motion.xrel;
		angle_x-=0.003*event.motion.yrel;
	
	}	
}


void demineur::OnKeyboard(){
	for (Keystates::iterator it = keystates.begin();it != keystates.end();it++) {
		if (event.key.keysym.sym == it->first){
			it->second = (event.type == SDL_KEYDOWN);
		break; 
		}
	}
}

void demineur::animate(Uint32 timestep){

	if(not(fps)){
		if (keystates[keyconf["straff_gauche"]]){
			double dth_z=0.01;
			matrice_3 R_z;
			R_z(0,0)=cos(dth_z);
			R_z(1,1)=cos(dth_z);
			R_z(0,1)=-sin(dth_z);
			R_z(1,0)=sin(dth_z);
			orientation=R_z*orientation;
		}
		if (keystates[keyconf["straff_droit"]]){
			double dth_z=-0.01;
			matrice_3 R_z;
			R_z(0,0)=cos(dth_z);
			R_z(1,1)=cos(dth_z);
			R_z(0,1)=-sin(dth_z);
			R_z(1,0)=sin(dth_z);
			orientation=R_z*orientation;
		}
		if (keystates[keyconf["avant"]]){
			double dth_x=0.01;
			matrice_3 R_x;
			R_x(1,1)=cos(dth_x);
			R_x(2,2)=cos(dth_x);
			R_x(1,2)=-sin(dth_x);
			R_x(2,1)=sin(dth_x);
			orientation=R_x*orientation;
		}
		if (keystates[keyconf["arriere"]]){
			double dth_x=-0.01;
			matrice_3 R_x;
			R_x(1,1)=cos(dth_x);
			R_x(2,2)=cos(dth_x);
			R_x(1,2)=-sin(dth_x);
			R_x(2,1)=sin(dth_x);
			orientation=R_x*orientation;
		}
	}
	else{
		if (keystates[keyconf["straff_gauche"]]){
			pos_x-=xx;pos_y-=xy;pos_z-=xz;
		}
		if (keystates[keyconf["avant"]]){
			pos_x+=yx;pos_y+=yy;pos_z+=yz;
		}
		if (keystates[keyconf["straff_droit"]]){
			pos_x+=xx;pos_y+=xy;pos_z+=xz;
		}
		if (keystates[keyconf["arriere"]]){
			pos_x-=yx;pos_y-=yy;pos_z-=yz;
		}		
	}
}



void demineur::OnMouseButton()
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        if ((hold)and(event.type == SDL_MOUSEBUTTONUP))
        {
            hold = false;
            SDL_SetCursor(_hand1);
        }
        else if ((!hold)and(event.type == SDL_MOUSEBUTTONDOWN))
        {
            hold = true;
            SDL_SetCursor(_hand2);
        }
    }
}

