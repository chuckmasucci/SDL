#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window *window;
SDL_Renderer *renderer;

int initializeGfx();
SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath);
void clear();
void setTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect);
void present();
