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
#include <dbg.h>
#include "animate.h"
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

    Animation missleAnimation;
    missleAnimation.type = TO_FROM;
    missleAnimation.isAnimating = 0;

    AnimationToFrom *animation;
    animation = malloc(sizeof(AnimationToFrom));
    check_mem(animation);
    animation->fromX = player->x + (player->w / 2) - 3;
    animation->toX = animation->fromX;
    animation->fromY = player->y;
    animation->toY = 10;
    animation->anim = missleAnimation;

    // Missle
    Sprite *missleSprite = NULL;
    char *spriteName;

    spriteid++;

    spriteName = malloc(10 * sizeof(char));
    check_mem(spriteName);
    sprintf(spriteName, "Missle%d", spriteid);
    missle.x = missle.x + 10;

    missleSprite = createSprite(spriteName, MISSLE_SPRITE, 0, 1, size, NULL, animation);
    missleSprite->flags |= FLAG_ANIMATING;
    addToRender(missleSprite, Z_RENDER_1);

    return;

error:
    log_err("Error while shooting");
}
