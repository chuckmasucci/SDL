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
#include <list.h>
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

// TODO: Move to a config file
Vector2 p0 = {.x = 0, .y = -375};
Vector2 p1 = {.x = 100, .y = -225};
Vector2 p2 = {.x = -125, .y = -275};
Vector2 p3 = {.x = 0, .y = 0};

Vector2 enemy_p0;
Vector2 enemy_p1;
Vector2 enemy_p2;
Vector2 enemy_p3;

Vector2 get_position_offset();
void position_enemies(Sprite *enemy, int pos);

void initialize_enemies()
{
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		Sprite *enemy = add_enemy(NULL);
		position_enemies(enemy, i);
	}
}

void position_enemies(Sprite *enemy, int pos)
{
	Vector2 p_offset = get_position_offset(pos);

	// Bezier vectors
	enemy_p0.x = p0.x + p_offset.x;
	enemy_p0.y = p0.y + p_offset.y;

	enemy_p1.x = p1.x + p_offset.x;
	enemy_p1.y = p1.y + p_offset.y;

	enemy_p2.x = p2.x + p_offset.x;
	enemy_p2.y = p2.y + p_offset.y;

	enemy_p3.x = p3.x + p_offset.x;
	enemy_p3.y = p3.y + p_offset.y;

	enemy->size->x = (int)enemy_p3.x;
	enemy->size->y = (int)enemy_p3.y;
}

// Should be in the header
Vector2 get_position_offset(int pos)
{

	int center_x = (WINDOW_WIDTH / 2) - (ENEMY_WIDTH / 2);
	int gutter = (ENEMY_WIDTH / 2) + 100;
	int enemy_position = center_x + (pos * gutter);
	int column_position = pos % ENEMY_COLUMNS;

	if (column_position == 0) {
		column++;
		row++;
	}

	// The offsets
	int position_x = -(((ENEMY_COLUMNS - 1) * gutter) / 2)
			 + (column_position * gutter) + center_x;
	int position_y = (column * ENEMY_HEIGHT) + ((row - 1) * 100);

	// The return variable
	Vector2 position = {
		.x = position_x,
		.y = position_y,
	};

	return position;
}

Sprite *add_enemy(Vector2 *animation_points)
{
	// Create the sprite id string
	char *enemy_name = malloc(10 * sizeof(char));
	check_mem(enemy_name);
	sprintf(enemy_name, "Enemy%d", enemyid);
	enemyid++;

	// Animation
	CubicBezierPoints points = {
		.p0 = enemy_p0,
		.p1 = enemy_p1,
		.p2 = enemy_p2,
		.p3 = enemy_p3,
	};

	int *steps_x =
		get_bezier_points(points, 1000, QuadraticEaseOut, ATTR_X);

	int *steps_y =
		get_bezier_points(points, 1000, QuadraticEaseOut, ATTR_Y);

	debug("step x: %d", steps_x[40]);

	Animation2 *animation_x = add_animation_attrs(ATTR_X, // Attribute type
						      0,      // Delay
						      steps_x,
						      1000, // Duration
						      0     // Loop
	);

	Animation2 *animation_y = add_animation_attrs(ATTR_Y, // Attribute type
						      0,      // Delay
						      steps_y,
						      1000, // Duration
						      0     // Loop
	);

	// Create enemy rect
	SDL_Rect *enemy;
	enemy = malloc(sizeof(SDL_Rect));
	check_mem(enemy);
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

	// Create the sprite
	Sprite *enemy_sprite = create_sprite(enemy_name, ENEMY_SPRITE, 0, enemy,
					     enemy_mask, NULL);

	// Set flags
	enemy_sprite->flags |= FLAG_ANIMATING;
	enemy_sprite->flags |= FLAG_FLIPPED;

	// Add animations to the sprite
	// add_animation(enemy_sprite, animation_x);
	// add_animation(enemy_sprite, animation_y);

	// Add the sprite to the first renderer linked list
	add_to_render(enemy_sprite, Z_RENDER_2);

	return enemy_sprite;

error:
	SDL_Quit();
	log_err("Error while initializing player: Shutdown");
}
