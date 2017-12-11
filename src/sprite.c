#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "dbg.h"
#include "sprite.h"
#include "gfx.h"
Sprite *createSprite(char *id, char *path, int frames, int visible, SDL_Rect *size, SDL_Rect *mask, Animation *animation) {
    Sprite *sprite = malloc(sizeof(Sprite));
    static int flagInt = 0;
    sprite->id = id;
    sprite->frames = frames;
    sprite->path = path;
    sprite->visible = 1;
    sprite->size = size;
    sprite->mask = mask;
    sprite->texture = createSpriteTexture(renderer, path);
    sprite->isAnimating = 0;
    sprite->animation = animation;
    sprite->flags = &flagInt;
    return sprite;
}

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath)
{
    SDL_Surface *spriteSurface = IMG_Load(imgPath);
    check(spriteSurface, "Could not load image: %s, error = %s", imgPath, SDL_GetError())

    SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    check(spriteTexture, "Could not create texture: %s", SDL_GetError());

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
    }

    free(sprite);
}
