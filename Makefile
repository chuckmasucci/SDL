test:
	make build;
	./game2;

build:
	rm -rf game2
	gcc -c `sdl2-config --cflags` game2.c;
	gcc game2.o `sdl2-config --libs` -lSDL2_image -o game2;

clean:
	-rm game2.o;
	-rm game2;
