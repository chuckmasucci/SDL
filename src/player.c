#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"
#include "sprite.h"
#include "flags.h"
#include "list.h"

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
    .h = 20
};

SDL_Rect missle = {
    .x = (WINDOW_WIDTH / 2) - (MISSLE_WIDTH / 2),
    .y = WINDOW_HEIGHT - 200,
    .w = MISSLE_WIDTH,
    .h = MISSLE_HEIGHT
};

SDL_Rect playerMask;
SDL_Rect missleMask;
SDL_Rect bulletMask = {
    .x = 0,
    .y = 0,
    .w = 10,
    .h = 20
};

int spriteid = 0;

void initializePlayer() {
    // Ship
    Sprite *playerSprite = createSprite("Player", SHIP_SPRITE, 0, 1, &player, &playerMask, NULL);
    addToRender(playerSprite, "Player");

    // Bullet
    Sprite *bulletSprite = createSprite("Bullet", BULLET_SPRITE, 4, 1, &bullet, &bulletMask, NULL);
    addToRender(bulletSprite, "Bullet");
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

void shoot() {
    SDL_Rect *s = malloc(sizeof(SDL_Rect));
    s->x = 20 * spriteid;
    s->y = 20;
    s->w = MISSLE_WIDTH;
    s->h = MISSLE_HEIGHT;

    Animation *animation;
    animation = malloc(sizeof(Animation));
    animation->toX += spriteid;
    animation->fromX = player.x + (player.w / 2) - 3;
    animation->toX = animation->fromX;
    animation->fromY = player.y;
    animation->toY = 10;

    // Missle
    Sprite *missleSprite = NULL;
    char *spriteName;

    spriteid++;

    spriteName = malloc(10 * sizeof(char));
    sprintf(spriteName, "Missle%d", spriteid);
    missle.x = missle.x + 10;

    missleSprite = createSprite(spriteName, MISSLE_SPRITE, 0, 1, s, NULL, animation);
    addToRender(missleSprite, spriteName);

    missleSprite->animation->isAnimating = 0;
    *(missleSprite->flags) |= FLAG_ANIMATING;
}

