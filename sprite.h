#include <SDL2/SDL.h>

typedef struct sprite {
    SDL_Rect size;
    SDL_Rect mask;
    int frames;
    int visible;
} Sprite;
