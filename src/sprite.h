#ifndef sprite_h
#define sprite_h

#include <SDL2/SDL.h>
#include "animate.h"

typedef struct sprite {
    char *id;
    char *path;
    SDL_Rect *size;
    SDL_Rect *mask;
    int frames;
    int visible;
    SDL_Texture *texture;
    int isAnimating;
    Animation *animation;
    int *flags;
} Sprite;

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath);
Sprite *createSprite(char *id, char *path, int frames, int visible, SDL_Rect *size, SDL_Rect *mask, Animation *animation);
void destroySprite(Sprite *sprite);

#endif
