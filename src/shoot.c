/*
 * =====================================================================================
 *
 *       Filename:  shoot.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/11/2018 11:27:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <bezier.h>
#include <dbg.h>
#include "animate.h"
#include "easing.h"
#include "event.h"
#include "flags.h"
#include "gfx.h"
#include "render.h"
#include "shoot.h"
#include "sprite.h"
#include "player.h"

int spriteid = 0;

SDL_Rect missle = {
    .x = (WINDOW_WIDTH / 2) - (MISSLE_WIDTH / 2),
    .y = WINDOW_HEIGHT - 200,
    .w = MISSLE_WIDTH,
    .h = MISSLE_HEIGHT
};

void animation_complete(Sprite *sprite);

void shoot()
{
    SDL_Rect *size = malloc(sizeof(SDL_Rect));
    check_mem(size);
    size->x = 20 * spriteid;
    size->y = 20;
    size->w = MISSLE_WIDTH;
    size->h = MISSLE_HEIGHT;

    void *ease_func = QuadraticEaseOut;

    int *steps_x = get_linear_points(player->x + (player->w / 2) - 3, player->x + (player->w / 2) - 3, 1000, ease_func);
    Animation2 *animation_x = add_animation_attrs(
            ATTR_X, // Attribute type
            0, // Delay
            steps_x,
            1000, // Duration
            0 // Loop
    );

    int *steps_y = get_linear_points(player->y, 10, 1000, ease_func);
    Animation2 *animation_y = add_animation_attrs(
            ATTR_Y, // Attribute type
            0, // delay
            steps_y,
            1000, // Duration
            0 // Loop
    );

    // Missle id
    Sprite *missle_sprite = NULL;
    char *sprite_name = malloc(10 * sizeof(char));
    check_mem(sprite_name);
    sprintf(sprite_name, "Missle%d", spriteid);

    // Increment id
    spriteid++;

    // Create the sprite and add it to the render
    missle_sprite = create_sprite(sprite_name, MISSLE_SPRITE, 0, size, NULL, NULL);
    missle_sprite->flags |= FLAG_ANIMATING;
    add_to_render(missle_sprite, Z_RENDER_1);

    // Add animations to the sprite
    add_animation(missle_sprite, animation_x);
    add_animation(missle_sprite, animation_y);

    void *complete_func = animation_complete;
    add_event_listener(sprite_name, complete_func, ((void *)missle_sprite));

    return;

error:
    log_err("Error while shooting");
}

void animation_complete(Sprite *sprite) {
    sprite->flags |= FLAG_REMOVE;
}
