#ifndef sprite_h
#define sprite_h

#include <SDL2/SDL.h>
#include "animate.h"

typedef struct sprite {
    char *path;
    SDL_Rect *size;
    SDL_Rect *mask;
    int frames;
    int visible;
    SDL_Texture *texture;
    int isAnimating;
    Animation *animation;
} Sprite;

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath);
void createSprite(Sprite *sp, char *path, int frames, int visible, SDL_Rect *size, SDL_Rect *mask, int isAnimating, Animation *animation);
#endif
