#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dbg.h>
#include "background.h"
#include "enemy.h"
#include "gfx.h"
#include "player.h"
#include "render.h"

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

    // Initialize Render
    initializeRender();

    // Initialize player
    initializePlayer();

    // Initialize enemy
    Vector2 p0_0 = { .x = 290, .y = 40 };
    Vector2 p0_1 = { .x = 490, .y = 40 };
    Vector2 p0_2 = { .x = 470, .y = 150 };
    Vector2 p0_3 = { .x = 390, .y = 210 };
    Vector2 points0[4];
    points0[0] = p0_0;
    points0[1] = p0_1;
    points0[2] = p0_2;
    points0[3] = p0_3;
    addEnemy(points0);

    Vector2 p1_0 = { .x = 340, .y = 40 };
    Vector2 p1_1 = { .x = 540, .y = 40 };
    Vector2 p1_2 = { .x = 520, .y = 150 };
    Vector2 p1_3 = { .x = 430, .y = 210 };
    Vector2 points1[4];
    points1[0] = p1_0;
    points1[1] = p1_1;
    points1[2] = p1_2;
    points1[3] = p1_3;
    addEnemy(points1);

    // Generate the background data
    initializeBackground();

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
    destroyGfx();
    atexit(SDL_Quit);
    return 0;
}
