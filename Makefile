CC=gcc
SRC=src
BUILD=build

# Includes
INCLUDE_SDL=/usr/include/SDL2
INCLUDE_DARRAY=/home/chuck/.local/lib/chuck/darray
INCLUDE_DBG=/home/chuck/.local/lib/chuck/dbg
INCLUDE_LIST=/home/chuck/.local/lib/chuck/list
INCLUDES=-I$(INCLUDE_DBG) -I$(INCLUDE_LIST) -I$(INCLUDE_SDL)
LIB_DIRS=-L$(INCLUDE_DBG) -L$(INCLUDE_LIST)

# Libs
LIB_SDL=SDL2
LIB_SDL_IMAGE=SDL2_image
LIB_DBG=dbg
LIB_LIST=list
LIBS=-l$(LIB_SDL) -l$(LIB_SDL_IMAGE) -l$(LIB_DBG) -l$(LIB_LIST)

CFLAGS=$(INCLUDES) $(LIBS) $(LIB_DIRS) -ggdb

TARGET=bin/spacegame

SOURCES=$(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: build $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@
export LD_LIBRARY_PATH=/home/chuck/.local/lib/chuck/dbg:/home/chuck/.local/lib/chuck/list

build:
	@mkdir -p bin build

clean:
	rm -rf *.o build $(OBJECTS)
