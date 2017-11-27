#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"
#include "render.h"

#define MOVEMENT_SPEED 200

SDL_Rect ship = {
    .x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2),
    .y = WINDOW_HEIGHT - SHIP_HEIGHT - 20,
    .w = SHIP_WIDTH,
    .h = SHIP_HEIGHT
};
Sprite playerSprite;
SDL_Rect playerMask;

/*
 *SDL_Rect bullet;
 *SDL_Texture *bulletSprite;
 *SDL_Rect bulletMask;
 */

void initializePlayer() {

    // Ship
    playerSprite = createSprite(SHIP_SPRITE, 0, 1, &ship, NULL);
    addToRender(playerSprite);

    // Bullet
/*
 *    bulletSprite = createSpriteTexture(renderer, BULLET_SPRITE);
 *    SDL_QueryTexture(bulletSprite, NULL, NULL, &bullet.w, &bullet.h);
 *
 *    bulletMask.x = 0;
 *    bulletMask.y = 60;
 *    bulletMask.w = 10;
 *    bulletMask.h = 20;
 *
 *    bullet.x = ship.x + (ship.w / 2) + 3;
 *    bullet.y = ship.y + ship.h - 4;
 *    bullet.w = 10;
 *    bullet.h = 20;
 */
}

void move(int direction, float delta) {
    // -1 = left, 1 = right
    float speed = MOVEMENT_SPEED * delta;
    if(direction < 0) {
        if(ship.x > 0) {
            ship.x -= (int)speed;
        } else {
            ship.x = 0;
        }
    } else if(direction > 0) {
        if(ship.x < WINDOW_WIDTH - ship.w) {
            ship.x += (int)speed;
        } else {
            ship.x = WINDOW_WIDTH - ship.w;
        }
    }
}
