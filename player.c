#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"
#include "sprite.h"

#define MOVEMENT_SPEED 200

SDL_Rect ship;
SDL_Rect bullet;
SDL_Texture *shipSprite;
SDL_Texture *bulletSprite;
SDL_Rect shipMask;
SDL_Rect bulletMask;

void initializePlayer() {
    // Ship
    shipSprite = createSpriteTexture(renderer, SHIP_SPRITE);
    ship.x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2);
    ship.y = WINDOW_HEIGHT - SHIP_HEIGHT - 20;
    ship.w = SHIP_WIDTH;
    ship.h = SHIP_HEIGHT;

    // Bullet
    bulletSprite = createSpriteTexture(renderer, BULLET_SPRITE);
    SDL_QueryTexture(bulletSprite, NULL, NULL, &bullet.w, &bullet.h);

    bulletMask.x = 0;
    bulletMask.y = 60;
    bulletMask.w = 10;
    bulletMask.h = 20;

    bullet.x = ship.x + (ship.w / 2) + 3;
    bullet.y = ship.y + ship.h - 4;
    bullet.w = 10;
    bullet.h = 20;
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

void render() {
    int frames = 4;
    int frameDelay = 100;
    int frame = (SDL_GetTicks() / frameDelay) % frames;

    bulletMask.y = frame * 20;

    clear();
    setTexture(renderer, shipSprite, NULL, &ship);
    setTexture(renderer, bulletSprite, &bulletMask, &bullet);
    present();
}
