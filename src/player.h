#ifndef player_h
#define player_h

#include <SDL2/SDL.h>

// Ship data
#define SHIP_SPRITE "gfx/sprites/ship.proto1.spritesheet.png"
#define SHIP_WIDTH 73
#define SHIP_HEIGHT 122

#define BULLET_SPRITE "gfx/sprites/bullet.proto1.png"
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 80

#define MISSLE_SPRITE "gfx/sprites/missle.proto1.png"
#define MISSLE_WIDTH 10
#define MISSLE_HEIGHT 13

// Declarations
int initializePlayer();
void move(int direction, float delta);
void shoot();

#endif
