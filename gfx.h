#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *createSpriteTexture(SDL_Renderer *renderer, char *imgPath);
void setTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect scaledRect);
