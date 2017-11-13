#include "dbg.h"
#include "gfx.h"

int initializeGfx() {
    int init = SDL_Init(SDL_INIT_VIDEO);
    check(init >= 0, "Could not initialize SDL: %s", SDL_GetError());

    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    check(window != NULL, "Could not create window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    check(renderer != NULL, "Could not create renderer: %s", SDL_GetError());

    return 0;

error:
    SDL_Quit();
    log_err("SDL Error: Shutdown");

    return -1;
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

void setTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect scaledRect)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &scaledRect);
    SDL_RenderPresent(renderer);
}
