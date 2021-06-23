FLAGS = -Wall --ansi --pedantic -lm -g3 -O3 -std=gnu89 -Wextra 

exe: ml_main.c ml_lib.o ml_autoplay.o
	gcc ml_main.c ml_lib.o ml_autoplay.o -o ml_main $(FLAGS)
		
ml_lib.o: ml_lib.c ml_lib.h
	gcc -c ml_lib.c -o ml_lib.o $(FLAGS)

ml_autoplay.o: ml_lib.o ml_autoplay.c ml_autoplay.h
	gcc -c ml_autoplay.c -o ml_autoplay.o $(FLAGS)
		
clean: 
	rm *.o
	rm ml_main
	
