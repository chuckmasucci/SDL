#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dbg.h>
#include "player.h"
#include "gfx.h"
#include "render.h"
#include "background.h"

#define FRAMERATE 5

int main(int argc, char *argv[])
{
    int running = 1;

    // Initialize movement variables
    int isLeftKeyDown = 0;
    int isRightKeyDown = 0;
    int moveDirection = 0;

    // Initialize timing variables
    float freq;
    Uint64 now;
    Uint64 lastTime = SDL_GetPerformanceCounter();
    float delta;

    // Start graphics
    initializeGfx();

    // Initialize player
    initializePlayer();

    // Generate the background data
    /*getGeneratedBackground();*/
    /*setBitmapBackground();*/

    // The loop
    while(running) {
        // Timing variables
        freq = SDL_GetPerformanceFrequency();
        now = SDL_GetPerformanceCounter();
        delta = ((now - lastTime) / freq);

        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            isLeftKeyDown = 1;
                            moveDirection = -1;
                            break;
                        case SDLK_RIGHT:
                            isRightKeyDown = 1;
                            moveDirection = 1;
                            break;
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                        case SDLK_SPACE:
                            shoot();
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            isLeftKeyDown = 0;
                            break;
                        case SDLK_RIGHT:
                            isRightKeyDown = 0;
                            break;
                    }
                    break;
            }

            if(event.type == SDL_QUIT) {
                break;
            }
        }

        // Update the timing variable
        lastTime = now;

        // Determine if movement key is pressed and move the player
        if(isLeftKeyDown) {
            move(moveDirection, delta);
        } else if(isRightKeyDown) {
            move(moveDirection, delta);
        }

        render(delta);
    }

    destroyRenderQueue();
    destroyBackground();
    destroyGfx();
    atexit(SDL_Quit);
    return 0;
}
