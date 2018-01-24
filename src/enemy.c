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

int add_enemy(Vector2 *animationPoints)
{
    int center_x = (WINDOW_WIDTH / 2) - (ENEMY_WIDTH / 2);
    int gutter = (ENEMY_WIDTH / 2) + 100;
    int enemy_position = center_x + (enemyid * gutter);
    int column_position = enemyid % ENEMY_COLUMNS;
    int position_x = -(((ENEMY_COLUMNS - 1) * gutter) / 2) + (column_position * gutter) + center_x;

    if(column_position == 0) {
        column++;
        row++;
    }

    int position_y = ((column - 1) * ENEMY_HEIGHT) + ((row - 1) * 100);

    Vector2 enemy_p0;
    enemy_p0.x = p0.x + position_x;
    enemy_p0.y = p0.y + position_y;

    Vector2 enemy_p1;
    enemy_p1.x = p1.x + position_x;
    enemy_p1.y = p1.y + position_y;

    Vector2 enemy_p2;
    enemy_p2.x = p2.x + position_x;
    enemy_p2.y = p2.y + position_y;

    Vector2 enemy_p3;
    enemy_p3.x = p3.x + position_x;
    enemy_p3.y = p3.y + position_y;

    // Create enemy rect
    SDL_Rect *enemy;
    enemy = malloc(sizeof(SDL_Rect));
    check_mem(enemy);
    enemy->x = (int)enemy_p1.x;
    enemy->y = (int)enemy_p1.y;
    enemy->w = ENEMY_WIDTH;
    enemy->h = ENEMY_HEIGHT;

    // Create enemy mask
    SDL_Rect *enemy_mask;
    enemy_mask = malloc(sizeof(SDL_Rect));
    check_mem(enemy_mask);
    enemy_mask->x = 0;
    enemy_mask->y = 0;
    enemy_mask->w = ENEMY_WIDTH;
    enemy_mask->h = ENEMY_HEIGHT;

    // Create animation struct
    Animation enemy_animation;
    enemy_animation.type = BEZIER;
    enemy_animation.is_animating = 0;
    enemy_animation.delay = enemyid * 100;

    // Create animation bezier struct
    AnimationBezier *animation;
    animation = malloc(sizeof(AnimationBezier));
    check_mem(animation);
    animation->anim = enemy_animation;
    animation->current_point = 0;
 
    // Convert the control points to the bezier points
    for(int i = 0; i <= BEZIER_STEPS; i++) {
        float t = (float)i / (float)BEZIER_STEPS;
        AHFloat p = CubicEaseInOut(t);
        Vector2 point = getCubicBezierPoint(p, enemy_p0, enemy_p1, enemy_p2, enemy_p3);
        animation->points[i] = point;
    }

    // Create the sprite id string
    char *enemy_name = malloc(10 * sizeof(char));
    check_mem(enemy_name);
    sprintf(enemy_name, "Enemy%d", enemyid++);

    // Create the sprite
    Sprite *enemy_sprite = create_sprite(enemy_name, ENEMY_SPRITE, 0, 255, 1, enemy, enemy_mask, animation);
 
    // Set flags
    enemy_sprite->flags |= FLAG_ANIMATING;
    enemy_sprite->flags |= FLAG_FLIPPED;

    // Add the sprite to the first renderer linked list
    add_to_render(enemy_sprite, Z_RENDER_2);

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing player: Shutdown");
    return -1;
}

void position_enemies(/*Node **enemyHead*/)
{
    for (int i = 0; i < ENEMY_COUNT; ++i) {
        add_enemy(NULL);
    }
}

