#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int init;
SDL_Window *window;
SDL_Renderer *renderer;

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

int main(int argc, char *argv[])
{
    SDL_Texture *texture;

    init = SDL_Init(SDL_INIT_VIDEO);
    check(init >= 0, "Could not initialize SDL: %s", SDL_GetError());

    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    check(window != NULL, "Could not create window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    check(renderer != NULL, "Could not create renderer: %s", SDL_GetError());

    SDL_Rect scaledRect;
    scaledRect.x = (WINDOW_WIDTH / 2) - (162 / 2),  scaledRect.y = WINDOW_HEIGHT - 216 - 20,
    scaledRect.w = 162, scaledRect.h = 216;

    SDL_RenderClear(renderer);

    texture = createSpriteTexture(renderer, "gfx/F5S2.png");
    setTexture(renderer, texture, scaledRect);

    int running = 1;
    while(running) {
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            scaledRect.x -= 10;
                            break;
                        case SDLK_RIGHT:
                            scaledRect.x += 10;
                            break;
                        case SDLK_ESCAPE:
                            debug("escape");
                            running = 0;
                            break;
                    }
                    break;
            }

            if(event.type == SDL_QUIT) {
                break;
            }

            setTexture(renderer, texture, scaledRect);
        }
    }

error:
    SDL_Quit();
    log_err("SDL Error: Shutdown");
}
