#ifndef sprite_h
#define sprite_h

#include <SDL2/SDL.h>

typedef struct sprite {
    char *id;
    float alpha;
    char *path;
    SDL_Rect *size;
    SDL_Rect *mask;
    int frames;
    int visible;
    SDL_Texture *texture;
    void *animation;
    int flags;
    int isAnimating;
} Sprite;

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath, int alpha);
Sprite *createSprite(char *id, char *path, int frames, float alpha, int visible, SDL_Rect *size, SDL_Rect *mask, void *animation);
void destroySprite(Sprite *sprite);

#endif
