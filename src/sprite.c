#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "animate.h"
#include "dbg.h"
#include "sprite.h"
#include "gfx.h"

Sprite *create_sprite(char *id, char *path, int frames, float alpha, int visible, SDL_Rect *size, SDL_Rect *mask, void *animation) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->id = id;
    sprite->alpha = 1.0;
    sprite->frames = frames;
    sprite->path = path;
    sprite->visible = 1;
    sprite->size = size;
    sprite->mask = mask;
    sprite->texture = create_sprite_texture(renderer, path, alpha);
    sprite->is_animating = 0;
    sprite->animation = animation;
    sprite->flags = 0;
    Animation *a = (Animation *)animation;
    if(strcmp(id, "Enemy0") == 0) {
        debug("sprite animation ptr: %p", a);
        /*debug("id: %s", a->id);*/
        /*debug("%s alpha step 10: %d", ((Animation *)animation)->id, ((Animation *)animation)->steps_alpha[10]);*/
        /*debug("%s to_alpha: %d", ((Animation *)animation)->id, ((Animation *)animation)->to_alpha);*/
        /*debug("alpha step 10: %d", a->steps_alpha[10]);*/
    }
    return sprite;
}

SDL_Texture *create_sprite_texture(SDL_Renderer *renderer, char *imgPath, int alpha)
{
    SDL_Surface *sprite_surface = IMG_Load(imgPath);
    check(sprite_surface, "Could not load image: %s, error = %s", imgPath, SDL_GetError())

    SDL_Texture *sprite_texture = SDL_CreateTextureFromSurface(renderer, sprite_surface);
    check(sprite_texture, "Could not create texture: %s", SDL_GetError());

    /*debug("alpha: %d", alpha);*/
    /*SDL_set_textureAlphaMod(sprite_texture, alpha);*/

    SDL_FreeSurface(sprite_surface);

    return sprite_texture;

error:
    SDL_Quit();
    log_err("SDL Error: Shutdown");

    return NULL;
}

void destroySprite(Sprite *sprite)
{
    if(sprite->id) {
        free(sprite->id);
    }

    if(sprite->size) {
        free(sprite->size);
    }

    if(sprite->mask) {
        free(sprite->mask);
    }

    if(sprite->animation) {
        free(sprite->animation);
        Animation *animation = (Animation *)sprite->animation;
        if(animation->type == BEZIER) {
            /*debug("bezier");*/
        }
    }

    free(sprite);
}
