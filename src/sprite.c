#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "dbg.h"
#include "sprite.h"
#include "gfx.h"

void createSprite(Sprite *sp, char *path, int frames, int visible, SDL_Rect *size, SDL_Rect *mask, int isAnimating, Animation *animation) {
    sp->frames = frames;
    sp->path = path;
    sp->visible = 1;
    sp->size = size;
    sp->mask = mask;
    sp->texture = createSpriteTexture(renderer, path);
    sp->isAnimating = isAnimating;
    sp->animation = animation;
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
