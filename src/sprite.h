#ifndef sprite_h
#define sprite_h

#include <SDL2/SDL.h>

typedef struct Sprite {
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
    int is_animating;
} Sprite;

SDL_Texture *create_sprite_texture(SDL_Renderer *renderer, char *imgPath, int alpha);
Sprite *create_sprite(char *id, char *path, int frames, float alpha, int visible, SDL_Rect *size, SDL_Rect *mask, void *animation);
void destroySprite(Sprite *sprite);

#endif
