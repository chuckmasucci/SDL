/*
 * =====================================================================================
 *
 *       Filename:  enemy.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/11/2018 10:56:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#define ENEMY_SPRITE "gfx/sprites/enemy.proto1.png"
#define ENEMY_WIDTH 74
#define ENEMY_HEIGHT 95
#define BEZIER_STEPS 100

#include <bezier.h>

int addEnemy(Vector2 *animationPoints);
