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
    .x = 20,
    .y = 20,
    .w = BULLET_WIDTH,
    .h = BULLET_HEIGHT
};

SDL_Rect playerMask;
SDL_Rect bulletMask = {
    .x = 0,
    .y = 0,
    .w = BULLET_WIDTH,
    .h = BULLET_HEIGHT
};

Sprite playerSprite;
Sprite bulletSprite;

void initializePlayer() {

    // Ship
    createSprite(&playerSprite, SHIP_SPRITE, 0, 1, &player, &playerMask);
    addToRender(&playerSprite, "Player");

    // Bullet
    createSprite(&bulletSprite, BULLET_SPRITE, 0, 1, &bullet, &bulletMask);
    addToRender(&bulletSprite, "Bullet");
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
