#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"

SDL_Rect ship;
SDL_Texture *texture;

void initializePlayer() {
    ship.x = (WINDOW_WIDTH / 2) - (162 / 2),  ship.y = WINDOW_HEIGHT - 216 - 20,
    ship.w = 162, ship.h = 216;

    SDL_RenderClear(renderer);

    texture = createSpriteTexture(renderer, "gfx/F5S2.png");
    setTexture(renderer, texture, ship);
}

// -1 = left, 1 = right
void move(int direction) {
    if(direction < 0) {
        ship.x -= 10;
    } else if(direction > 0) {
        ship.x += 10;
    }

    setTexture(renderer, texture, ship);
}
