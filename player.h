#include <SDL2/SDL.h>

// Ship data
#define SHIP_SPRITE "gfx/sprites/ship.proto1.png"
#define SHIP_WIDTH 105
#define SHIP_HEIGHT 105

#define BULLET_SPRITE "gfx/sprites/bullet.proto1.png"
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 80

// Declarations
void initializePlayer();
void move();
void shoot();
void render();
