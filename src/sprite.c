#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "animate.h"
#include "dbg.h"
#include "sprite.h"
#include "gfx.h"

Sprite *createSprite(char *id, char *path, int frames, float alpha, int visible, SDL_Rect *size, SDL_Rect *mask, void *animation) {
    Sprite *sprite = malloc(sizeof(Sprite));
    sprite->id = id;
    sprite->alpha = 1.0;
    sprite->frames = frames;
    sprite->path = path;
    sprite->visible = 1;
    sprite->size = size;
    sprite->mask = mask;
    sprite->texture = createSpriteTexture(renderer, path, alpha);
    sprite->isAnimating = 0;
    sprite->animation = animation;
    sprite->flags = 0;
    return sprite;
}

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath, int alpha)
{
    SDL_Surface *spriteSurface = IMG_Load(imgPath);
    check(spriteSurface, "Could not load image: %s, error = %s", imgPath, SDL_GetError())

    SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    check(spriteTexture, "Could not create texture: %s", SDL_GetError());

    debug("alpha: %d", alpha);
    /*SDL_SetTextureAlphaMod(spriteTexture, alpha);*/

    SDL_FreeSurface(spriteSurface);

    return spriteTexture;

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
            debug("bezier");
        }
    }

    free(sprite);
}
