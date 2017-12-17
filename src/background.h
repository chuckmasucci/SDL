#ifndef background_h
#define background_h

#include <SDL2/SDL.h>
int stars;
void *getGeneratedBackground();
int rng();
void renderBackground();
int setBitmapBackground();
void destroyBackground();
#endif
