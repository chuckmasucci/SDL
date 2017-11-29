CC=gcc
SRC=src
BUILD=build
LIBS_DIR=libs
CFLAGS=-lSDL2 -lSDL2_image -I/usr/include/SDL2 -Ilibs

TARGET=bin/spacegame
SO_TARGET=$(BUILD)/libList.so

SOURCES=$(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
LIBS=$(wildcard $(LIBS_DIR)/*.c)

all: build $(SO_TARGET) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@ $(LIBS)
	./bin/spacegame

$(SO_TARGET): $(LIBS)
	$(CC) -shared -fPIC -o $@ $(LIBS)

build:
	@mkdir -p bin build

clean:
	rm -rf *.o build $(OBJECTS)
