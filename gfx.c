#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "gfx.h"

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath)
{
    SDL_Surface *spriteSurface = IMG_Load(imgPath);
    SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);

    SDL_FreeSurface(spriteSurface);

    return spriteTexture;
}

void setTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect scaledRect)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &scaledRect);
    SDL_RenderPresent(renderer);
}
