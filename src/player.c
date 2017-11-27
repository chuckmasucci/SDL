#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"
#include "render.h"

#define MOVEMENT_SPEED 200

SDL_Rect player = {
    .x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2),
    .y = WINDOW_HEIGHT - SHIP_HEIGHT - 20,
    .w = SHIP_WIDTH,
    .h = SHIP_HEIGHT
};

SDL_Rect bullet = {
    .x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2),
    .y = WINDOW_HEIGHT - SHIP_HEIGHT - 20,
    .w = SHIP_WIDTH,
    .h = SHIP_HEIGHT
};

SDL_Rect playerMask;
SDL_Rect bulletMask;

Sprite playerSprite;
Sprite bulletSprite;

void initializePlayer() {

    // Ship
    createSprite(&playerSprite, SHIP_SPRITE, 0, 1, &player, &playerMask);
    debug("size x: %d", playerSprite.size->x);
    addToRender(&playerSprite, "Player");

    // Bullet
    bulletMask.x = player.x + (player.w / 2) + 3;
    bulletMask.y = player.y + player.h - 4;
    bulletMask.w = 10;
    bulletMask.h = 20;

    /*bulletSprite = createSprite(BULLET_SPRITE, 4, 1, &bullet, &bulletMask);*/
    /*addToRender(bulletSprite, "Bullet");*/
}

void move(int direction, float delta) {
    // -1 = left, 1 = right
    float speed = MOVEMENT_SPEED * delta;
    if(direction < 0) {
        if(player.x > 0) {
            player.x -= (int)speed;
        } else {
            player.x = 0;
        }
    } else if(direction > 0) {
        if(player.x < WINDOW_WIDTH - player.w) {
            player.x += (int)speed;
        } else {
            player.x = WINDOW_WIDTH - player.w;
        }
    }
}
