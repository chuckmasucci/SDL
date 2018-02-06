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

SDL_Rect *player_mask;

int initialize_player() {
    player = malloc(sizeof(SDL_Rect));
    check_mem(player);
    player->x = (WINDOW_WIDTH / 2) - (SHIP_WIDTH / 2);
    player->y = WINDOW_HEIGHT - SHIP_HEIGHT - 20;
    player->w = SHIP_WIDTH;
    player->h = SHIP_HEIGHT;

    player_mask = malloc(sizeof(SDL_Rect));
    check_mem(player_mask);
    player_mask->x = 0;
    player_mask->y = 0;
    player_mask->w = SHIP_WIDTH;
    player_mask->h = SHIP_HEIGHT;

    char *player_name = malloc(10 * sizeof(char));
    check_mem(player_name);
    strncpy(player_name, "Player", 10);
    Sprite *player_sprite = create_sprite(player_name, SHIP_SPRITE, 4, player, player_mask, NULL);
    add_to_render(player_sprite, Z_RENDER_0);

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


