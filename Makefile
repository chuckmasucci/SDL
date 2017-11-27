CC=gcc
SRC=src
CFLAGS=-lSDL2 -lSDL2_image -I/usr/include/SDL2

LIB_TARGET=build/linkedlist.a
TARGET=bin/spacegame

SOURCES=$(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(TARGET)

$(LIB_TARGET): CFLAGS += -fPIC
$(LIB_TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(TARGET): build $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@
	./bin/spacegame

build:
	@mkdir -p bin

clean:
	rm -rf build $(OBJECTS)
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

