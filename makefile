all : animation

animation: animation.o polygraph.o polynome.o bouton.o affichage.o main.o nuage.o libisentlib.a
	gcc -Wall animation.o polygraph.o polynome.o bouton.o affichage.o nuage.o main.o -o animation libisentlib.a -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exemple.o -o exemple libisentlib.a -lm -framework OpenGL -framework GLUT

animationTest: animation.o polygraph.o polynome.o bouton.o affichage.o mainTest.o libisentlib.a
	gcc -Wall animation.o polygraph.o polynome.o bouton.o affichage.o mainTest.o -o animationTest libisentlib.a -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exemple.o -o exemple libisentlib.a -lm -framework OpenGL -framework GLUT

exempleTortue: exempleTortue.o libisentlib.a
	gcc -Wall exempleTortue.o -o exempleTortue libisentlib.a -lm -lglut -lGL -lX11
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exempleTortue.o -o exempleTortue libisentlib.a -lm -framework OpenGL -framework GLU

nuage.o: nuage.c nuage.h GfxLib.h
	gcc -c -Wall nuage.c

polygraph.o: polygraph.c polygraph.h polynome.h
	gcc -c -Wall polygraph.c

polynome.o: polynome.c polynome.h
	gcc -c -Wall polynome.c

bouton.o: bouton.c bouton.h affichage.h
	gcc -c -Wall bouton.c

affichage.o: affichage.c affichage.h bouton.h
	gcc -c -Wall affichage.c

main.o: main.c animation.h
	gcc -c -Wall main.c

mainTest.o: mainTest.c animation.h bouton.h polynome.h
	gcc -c -Wall mainTest.c

animation.o: animation.c animation.h
	gcc -c -Wall animation.c





exempleTortue.o: exempleTortue.c GfxLib.h BmpLib.h ESLib.h TortueLib.h
	gcc -Wall -c exempleTortue.c


libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c

SocketLib.o: SocketLib.c SocketLib.h
	gcc -Wall -O2 -c SocketLib.c

ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c

TortueLib.o: TortueLib.c TortueLib.h GfxLib.h
	gcc -Wall -O2 -c TortueLib.c

VectorLib.o: VectorLib.c VectorLib.h
	gcc -Wall -O2 -c VectorLib.c -msse3

WavLib.o: WavLib.c WavLib.h OutilsLib.h
	gcc -Wall -O2 -c WavLib.c -Wno-unused-result
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c WavLib.c

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f animation animationTest exempleTortue libisentlib.a


