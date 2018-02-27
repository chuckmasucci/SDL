#ifndef sprite_h
#define sprite_h

#define ALPHA_MIN 0
#define ALPHA_MAX 255

#include <SDL2/SDL.h>
#include <list.h>
#include "animate.h"

typedef struct Sprite {
    int flags;
    int frames;
    int is_animating;
    int visible;
    int alpha;
    char *id;
    char *path;
    SDL_Rect *mask;
    SDL_Rect *size;
    SDL_Texture *texture;
    void *animation;
    Node *animations;
} Sprite;

Sprite *create_sprite(char *id, char *path, int frames, SDL_Rect *size, SDL_Rect *mask, void *animation);
SDL_Texture *create_sprite_texture(SDL_Renderer *renderer, char *imgPath, int alpha);
void add_animation(Sprite *sprite, Animation2 *animation);
Node *cleanup_sprite(Sprite *sprite, Node **render_index, int node_id);
void destroy_sprite(Sprite *sprite);

#endif
