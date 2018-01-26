#ifndef sprite_h
#define sprite_h

#include <SDL2/SDL.h>

typedef struct Sprite {
    int flags;
    int frames;
    int is_animating;
    int visible;
    float alpha;
    char *id;
    char *path;
    SDL_Rect *mask;
    SDL_Rect *size;
    SDL_Texture *texture;
    void *animation;
} Sprite;

SDL_Texture *create_sprite_texture(SDL_Renderer *renderer, char *imgPath, int alpha);
Sprite *create_sprite(char *id, char *path, int frames, float alpha, int visible, SDL_Rect *size, SDL_Rect *mask, void *animation);
void destroySprite(Sprite *sprite);

#endif
