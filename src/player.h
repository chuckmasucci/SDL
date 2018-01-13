#ifndef player_h
#define player_h

#include <SDL2/SDL.h>

// Ship data
#define SHIP_SPRITE "gfx/sprites/ship.proto1.spritesheet.png"
#define SHIP_WIDTH 73
#define SHIP_HEIGHT 122


// Declarations
SDL_Rect *player;
int initializePlayer();
void move(int direction, float delta);
void shoot();

#endif
