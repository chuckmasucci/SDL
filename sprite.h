#include <SDL2/SDL.h>
SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath);

typedef struct sprite {
    SDL_Rect size;
    SDL_Rect mask;
    int frames;
    int visible;
} Sprite;
