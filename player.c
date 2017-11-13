#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"

SDL_Rect ship;
SDL_Texture *shipSprite;

void initializePlayer() {
    ship.x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2),  ship.y = WINDOW_HEIGHT - SHIP_HEIGHT - 20,
    ship.w = SHIP_WIDTH, ship.h = SHIP_HEIGHT;

    SDL_RenderClear(renderer);

    shipSprite = createSpriteTexture(renderer, SHIP_SPRITE);
    setTexture(renderer, shipSprite, ship);
}

void move(int direction) {
    // -1 = left, 1 = right
    if(direction < 0) {
        if(ship.x > 0) {
            ship.x -= 1;
        } else {
            ship.x = 0;
        }
    } else if(direction > 0) {
        if(ship.x < WINDOW_WIDTH - ship.w) {
            ship.x += 1;
        } else {
            ship.x = WINDOW_WIDTH - ship.w;
        }
    }
    setTexture(renderer, shipSprite, ship);
}


SDL_Texture *shoot() {
    SDL_Texture *bulletSprite = createSpriteTexture(renderer, BULLET_SPRITE);
    SDL_Rect bullet;
    bullet.x = 0;
    bullet.y = 0;

    SDL_QueryTexture(bulletSprite, NULL, NULL, &bullet.w, &bullet.h);
    bullet.w /= 4; // TODO: make this a const
    debug("bullet.w: %d", bullet.w);
    debug("bullet.h: %d", bullet.h);

    return bulletSprite;
}
