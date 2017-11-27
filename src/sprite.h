#ifndef sprite_h
#define sprite_h
#endif

#include <SDL2/SDL.h>

typedef struct sprite {
    char *path;
    SDL_Rect *size;
    SDL_Rect *mask;
    int frames;
    int visible;
    SDL_Texture *texture;
} Sprite;

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath);
Sprite *createSprite(Sprite *sp, char *path, int frames, int visible, SDL_Rect *size, SDL_Rect *mask);
