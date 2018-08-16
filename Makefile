CC=gcc
SRC=src

# Includes
INCLUDE_SDL=/usr/include/SDL2
INCLUDE_LOCAL_LIB=/home/chuck/.local/lib
INCLUDE_DARRAY=/home/chuck/.local/lib/darray
INCLUDE_DBG=/home/chuck/.local/lib/dbg
INCLUDE_LIST=/home/chuck/.local/lib/list
INCLUDE_BEZIER=/home/chuck/.local/lib/bezier
INCLUDES=-I$(INCLUDE_DBG) -I$(INCLUDE_LIST) -I$(INCLUDE_DARRAY) -I$(INCLUDE_BEZIER) -I$(INCLUDE_SDL)
LIB_DIRS=-L$(INCLUDE_DBG) -L$(INCLUDE_LOCAL_LIB)

# Libs
LIB_SDL=SDL2
LIB_SDL_IMAGE=SDL2_image
LIB_DBG=dbg
LIB_LIST=list
LIB_DARRAY=darray
LIB_BEZIER=bezier
LIBS=-l$(LIB_SDL) -l$(LIB_SDL_IMAGE) -l$(LIB_DBG) -l$(LIB_LIST) -l$(LIB_DARRAY) -l$(LIB_BEZIER) -lm

CFLAGS=$(INCLUDES) $(LIBS) $(LIB_DIRS) -ggdb

TARGET=bin/spacegame

SOURCES=$(wildcard $(SRC)/**/*.c $(SRC)/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: build $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

build:
	@mkdir -p bin build

clean:
	rm -rf *.o build $(OBJECTS)
