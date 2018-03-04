#ifndef gfx_h
#define gfx_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 75

SDL_Window *window;
SDL_Renderer *renderer;

int initialize_gfx();
int clear();
int set_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect, int flip);
void present();
void destroy_gfx();

#endif
