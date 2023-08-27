jeu : obj/cube.o obj/sdlglutils.o obj/demineur.o obj/face.o obj/main.o obj/controle.o obj/vecteur.o obj/decor.o obj/anim.o obj/particule.o
	g++ obj/* -o jeu    -lSDL  -lGL -lGLU -lm -lSDL_image
obj/vecteur.o: vecteur.cpp vecteur.h
	g++ -c vecteur.cpp -o obj/vecteur.o 
obj/cube.o : cube.cpp cube.h 
	g++ -c cube.cpp -o obj/cube.o 
obj/sdlglutils.o : sdlglutils.cpp sdlglutils.h
	g++ -c sdlglutils.cpp -o obj/sdlglutils.o 
obj/demineur.o : demineur.cpp  demineur.h 
	g++ -c demineur.cpp -o obj/demineur.o 
obj/controle.o :demineur.h controle.cpp 
	g++ -c controle.cpp -o obj/controle.o
obj/main.o : main.cpp 
	g++ -c main.cpp -o obj/main.o
obj/face.o: face.cpp cube.cpp 
	g++ -c face.cpp -o obj/face.o 
obj/decor.o: decor.cpp decor.cpp 
	g++ -c decor.cpp -o obj/decor.o 
obj/anim.o: anim.cpp anim.h 
	g++ -c anim.cpp -o obj/anim.o 
obj/particule.o: particule.cpp particule.h 
	g++ -c particule.cpp -o obj/particule.o 	
clean:
	rm obj/*.o
install:
	mkdir ~/jeu
	cp -r texture ~/jeu/texture
	cp jeu ~/jeu/jeu
uninstall:
	rm -r ~/jeu
