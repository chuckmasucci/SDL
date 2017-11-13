test:
	make build;
	./spacegame;

build:
	rm -rf spacegame;
	~/.config/nvim/plugged/clang_complete/bin/cc_args.py gcc -c -B `sdl2-config --cflags` *.c;
	gcc *.o `sdl2-config --libs` -lSDL2_image -o spacegame;

clean:
	-rm *.o;
	-rm spacegame;
	make
