test:
	make build;
	./game;

build:
	gcc -I"/usr/include/SDL2" -c game.c;
	gcc game.o -lSDL2 -o game;

clean:
	-rm game.o;
	-rm game;
