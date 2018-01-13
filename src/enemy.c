/*
 * =====================================================================================
 *
 *       Filename:  enemy.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/11/2018 10:56:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chuck Masucci, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dbg.h>
#include <bezier.h>
#include "animate.h"
#include "enemy.h"
#include "flags.h"
#include "gfx.h"
#include "render.h"
#include "sprite.h"


int addEnemy(Vector2 *animationPoints)
{
    SDL_Rect *enemy;
    // Create enemy rect
    enemy = malloc(sizeof(SDL_Rect));
    check_mem(enemy);
    enemy->x = 20;
    enemy->y = 20;
    enemy->w = ENEMY_WIDTH;
    enemy->h = ENEMY_HEIGHT;

    // Create enemy mask
    SDL_Rect *enemyMask;
    enemyMask = malloc(sizeof(SDL_Rect));
    check_mem(enemyMask);
    enemyMask->x = 0;
    enemyMask->y = 0;
    enemyMask->w = ENEMY_WIDTH;
    enemyMask->h = ENEMY_HEIGHT;

    // Create animation struct
    Animation enemyAnimation;
    enemyAnimation.type = BEZIER;
    enemyAnimation.isAnimating = 0;

    // Create animation bezier struct
    AnimationBezier *animation;
    animation = malloc(sizeof(AnimationBezier));
    check_mem(animation);
    animation->anim = enemyAnimation;
    animation->currentPoint = 0;
 
    // Set the Vector2 animation control points
    Vector2 p0 = animationPoints[0];
    Vector2 p1 = animationPoints[1];
    Vector2 p2 = animationPoints[2];
    Vector2 p3 = animationPoints[3];

    // Convert the control points to the bezier points
    for(int i = 0; i <= BEZIER_STEPS; i++) {
        float t = (float)i / (float)BEZIER_STEPS;
        Vector2 point = getCubicBezierPoint(t, p0, p1, p2, p3);
        animation->points[i] = point;
    }

    // Create the sprite id string
    char *enemyName = malloc(10 * sizeof(char));
    check_mem(enemyName);
    strncpy(enemyName, "Enemy", 10);

    // Create the sprite
    Sprite *enemySprite = createSprite(enemyName, ENEMY_SPRITE, 0, 1, enemy, enemyMask, animation);
 
    // Set flags
    enemySprite->flags |= FLAG_ANIMATING;
    enemySprite->flags |= FLAG_FLIPPED;

    // Add the sprite to the first renderer linked list
    addToRender(enemySprite, Z_RENDER_0);

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing player: Shutdown");
    return -1;
}
