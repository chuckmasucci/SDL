#include "dbg.h"
#include "gfx.h"

int initializeGfx() {
    int init = SDL_Init(SDL_INIT_VIDEO);
    check(init >= 0, "Could not initialize SDL: %s", SDL_GetError());

    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    check(window != NULL, "Could not create window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    check(renderer != NULL, "Could not create renderer: %s", SDL_GetError());

    return 0;

error:
    SDL_Quit();
    log_err("SDL Error: Shutdown");

    return -1;
}

void clear() {
    SDL_RenderClear(renderer);
}

void setTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect) {
    if(!SDL_RectEmpty(srcRect)) {
        debug("srcRect->x: %d", srcRect->x);
    }
    SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

void present() {
    SDL_RenderPresent(renderer);
}
