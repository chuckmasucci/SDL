#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dbg.h>
#include "background.h"
#include "enemy.h"
#include "event.h"
#include "gfx.h"
#include "player.h"
#include "render.h"
#include "spacegame.h"

int main(int argc, char *argv[])
{
    int running = 1;

    // Initialize movement variables
    int is_left_key_down = 0;
    int is_right_key_down = 0;
    int move_direction = 0;

    // Start graphics
    initialize_gfx();

    // Initialize Render
    initialize_render();

    // Initialize player
    initialize_player();

    // Initialize enemy
    initialize_enemies();

    // Generate the background data
    initialize_background();

    // Initialize timing variables
    float delta;
    float freq;
    Uint64 now;
    Uint64 last_time = SDL_GetPerformanceCounter();

    // The loop
    while(running) {
        // Timing variables
        freq = SDL_GetPerformanceFrequency();
        now = SDL_GetPerformanceCounter();
        delta = ((now - last_time) / freq);

        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            is_left_key_down = 1;
                            move_direction = -1;
                            break;
                        case SDLK_RIGHT:
                            is_right_key_down = 1;
                            move_direction = 1;
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
                            is_left_key_down = 0;
                            break;
                        case SDLK_RIGHT:
                            is_right_key_down = 0;
                            break;
                    }
                    break;
            }

            if(event.type == SDL_QUIT) {
                break;
            }
        }

        // Calculations for FPS maintenance
        int fps = 1000/FPS;
        int delta_ms = (int)(delta * 1000);
        int delay = fps - delta_ms;
        if(delay > 0) {
            SDL_Delay(delay);
        }

        // Update the timing variable
        last_time = now;

        // Render
        render();

        // Determine if movement key is pressed and move the player
        if(is_left_key_down) {
            move(move_direction, delta);
        } else if(is_right_key_down) {
            move(move_direction, delta);
        }

    }

    destroy_render_queue();
    destroy_gfx();
    atexit(SDL_Quit);
    return 0;
}
