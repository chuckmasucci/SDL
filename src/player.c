#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dbg.h"
#include "player.h"
#include "gfx.h"
#include "sprite.h"
#include "flags.h"
#include "render.h"
#include "animate.h"

#define MOVEMENT_SPEED 200

SDL_Rect *playerMask;

int initializePlayer() {
    player = malloc(sizeof(SDL_Rect));
    check_mem(player);
    player->x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2);
    player->y = WINDOW_HEIGHT - SHIP_HEIGHT - 20;
    player->w = SHIP_WIDTH;
    player->h = SHIP_HEIGHT;

    playerMask = malloc(sizeof(SDL_Rect));
    check_mem(playerMask);
    playerMask->x = 0;
    playerMask->y = 0;
    playerMask->w = SHIP_WIDTH;
    playerMask->h = SHIP_HEIGHT;

    char *playerName = malloc(10 * sizeof(char));
    check_mem(playerName);
    strncpy(playerName, "Player", 10);
    Sprite *playerSprite = createSprite(playerName, SHIP_SPRITE, 4, 255, 1, player, playerMask, NULL);
    addToRender(playerSprite, Z_RENDER_0);

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing player: Shutdown");
    return -1;
}

void move(int direction, float delta) {
    // -1 = left, 1 = right
    float speed = MOVEMENT_SPEED * delta;
    if(direction < 0) {
        if(player->x > 0) {
            player->x -= (int)speed;
        } else {
            player->x = 0;
        }
    } else if(direction > 0) {
        if(player->x < WINDOW_WIDTH - player->w) {
            player->x += (int)speed;
        } else {
            player->x = WINDOW_WIDTH - player->w;
        }
    }
}


