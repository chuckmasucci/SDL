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
#include <bezier.h>
#include <dbg.h>
#include "animate.h"
#include "enemy.h"
#include "easing.h"
#include "flags.h"
#include "gfx.h"
#include "render.h"
#include "sprite.h"
#include "event.h"

int enemyid = 0;
int column = 0;
int row = 0;

Vector2 p0 = { .x = 0, .y = -375 };
Vector2 p1 = { .x = 100, .y = -225 };
Vector2 p2 = { .x = -125, .y = -275 };
Vector2 p3 = { .x = 0, .y = 0 };

int addEnemy(Vector2 *animationPoints)
{
    int centerX = (WINDOW_WIDTH / 2) - (ENEMY_WIDTH / 2);
    int gutter = (ENEMY_WIDTH / 2) + 100;
    int enemyPosition = centerX + (enemyid * gutter);
    int columnPosition = enemyid % ENEMY_COLUMNS;
    int positionX = -(((ENEMY_COLUMNS - 1) * gutter) / 2) + (columnPosition * gutter) + centerX;

    if(columnPosition == 0) {
        column++;
        row++;
    }

    int positionY = ((column - 1) * ENEMY_HEIGHT) + ((row - 1) * 100);

    Vector2 enemyP0;
    enemyP0.x = p0.x + positionX;
    enemyP0.y = p0.y + positionY;

    Vector2 enemyP1;
    enemyP1.x = p1.x + positionX;
    enemyP1.y = p1.y + positionY;

    Vector2 enemyP2;
    enemyP2.x = p2.x + positionX;
    enemyP2.y = p2.y + positionY;

    Vector2 enemyP3;
    enemyP3.x = p3.x + positionX;
    enemyP3.y = p3.y + positionY;

    // Create enemy rect
    SDL_Rect *enemy;
    enemy = malloc(sizeof(SDL_Rect));
    check_mem(enemy);
    enemy->x = (int)enemyP1.x;
    enemy->y = (int)enemyP1.y;
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
    enemyAnimation.delay = enemyid * 100;

    // Create animation bezier struct
    AnimationBezier *animation;
    animation = malloc(sizeof(AnimationBezier));
    check_mem(animation);
    animation->anim = enemyAnimation;
    animation->currentPoint = 0;
 
    // Convert the control points to the bezier points
    for(int i = 0; i <= BEZIER_STEPS; i++) {
        float t = (float)i / (float)BEZIER_STEPS;
        AHFloat p = CubicEaseInOut(t);
        Vector2 point = getCubicBezierPoint(p, enemyP0, enemyP1, enemyP2, enemyP3);
        animation->points[i] = point;
    }

    // Create the sprite id string
    char *enemyName = malloc(10 * sizeof(char));
    check_mem(enemyName);
    sprintf(enemyName, "Enemy%d", enemyid++);

    // Create the sprite
    Sprite *enemySprite = createSprite(enemyName, ENEMY_SPRITE, 0, 255, 1, enemy, enemyMask, animation);
 
    // Set flags
    enemySprite->flags |= FLAG_ANIMATING;
    enemySprite->flags |= FLAG_FLIPPED;

    // Add the sprite to the first renderer linked list
    addToRender(enemySprite, Z_RENDER_2);

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing player: Shutdown");
    return -1;
}

void positionEnemies(/*Node **enemyHead*/)
{
    for (int i = 0; i < ENEMY_COUNT; ++i) {
        addEnemy(NULL);
    }
}

