test:
	make build;
	./game2;

build:
	gcc -I"/usr/include/SDL2" -c game2.c;
	gcc game2.o -lSDL2 -o game2;

clean:
	-rm game2.o;
	-rm game2;
