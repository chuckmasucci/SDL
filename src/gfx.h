#ifndef gfx_h
#define gfx_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

SDL_Window *window;
SDL_Renderer *renderer;

int initializeGfx();
int clear();
int setTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect, int flip);
void present();
void destroyGfx();

#endif
