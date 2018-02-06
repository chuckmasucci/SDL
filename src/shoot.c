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

void shoot()
{
    SDL_Rect *size = malloc(sizeof(SDL_Rect));
    check_mem(size);
    size->x = 20 * spriteid;
    size->y = 20;
    size->w = MISSLE_WIDTH;
    size->h = MISSLE_HEIGHT;

    Animation2 *animation_x;
    animation_x = malloc(sizeof(Animation2));
    animation_x->type = ATTR_X;
    animation_x->from = player->x + (player->w / 2) - 3;
    animation_x->to = animation_x->from;
    animation_x->time = 2000;
    animation_x->delay = 0;
    animation_x->current_step = 0;

    Animation2 *animation_y;
    animation_y = malloc(sizeof(Animation2));
    animation_y->type = ATTR_Y;
    animation_y->from = player->y;
    animation_y->to = 10;
    animation_y->time = 2000;
    animation_y->delay = 0;
    animation_y->current_step = 0;

    int delta_x = animation_x->from - animation_x->to;
    int delta_y = animation_y->from - animation_y->to;
    int *steps_x = malloc(50 * sizeof(int));
    int *steps_y = malloc(50 * sizeof(int));
    int steps_total = FPS * (animation_x->time / 1000);
    debug("steps total: %d", steps_total);
    steps_x = realloc(steps_x, steps_total * sizeof(int));
    steps_y = realloc(steps_y, steps_total * sizeof(int));

    for(int i = 0; i <= steps_total; i++) {
        float ratio = (float)i / steps_total;
        AHFloat ease = CubicEaseInOut(ratio);
        int x = ((int)floor(delta_x) * ease) + animation_x->to;
        int y = ((int)floor(delta_y) * ease) + animation_y->to;
        steps_x[i] = x;
        steps_y[i] = y;
    }
    animation_x->steps = steps_x;
    animation_y->steps = steps_y;

    animation_x->steps_total = steps_total;
    animation_y->steps_total = steps_total;

    /*for(int i = 0; i <= STEPS_ANIM; i++) {*/
        /*debug("steps x: %d", steps_x[i]);*/
        /*debug("steps y: %d", steps_y[i]);*/
    /*}*/
    // Missle
    Sprite *missle_sprite = NULL;
    char *sprite_name;

    spriteid++;

    sprite_name = malloc(10 * sizeof(char));
    check_mem(sprite_name);
    sprintf(sprite_name, "Missle%d", spriteid);
    missle.x = missle.x + 10;

    missle_sprite = create_sprite(sprite_name, MISSLE_SPRITE, 0, size, NULL, NULL);
    missle_sprite->flags |= FLAG_ANIMATING;
    add_to_render(missle_sprite, Z_RENDER_1);

    add_animation(missle_sprite, animation_x);
    add_animation(missle_sprite, animation_y);

    return;

error:
    log_err("Error while shooting");
}
