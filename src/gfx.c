#include <dbg.h>
#include "gfx.h"

int initialize_gfx()
{
  int init = SDL_Init(SDL_INIT_VIDEO);
  check(init >= 0, "Could not initialize SDL: %s", SDL_GetError());

  IMG_Init(IMG_INIT_PNG);

  window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  check(window != NULL, "Could not create window: %s", SDL_GetError());

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  check(renderer != NULL, "Could not create renderer: %s", SDL_GetError());

  return 0;

error:
  SDL_Quit();
  log_err("SDL Error: Shutdown");

  return -1;
}

int clear()
{
  int render_clear = SDL_RenderClear(renderer);
  check(render_clear == 0, "Could not set texture: %s", SDL_GetError());

  return 0;

error:
  SDL_Quit();
  log_err("SDL Error: Shutdown");

  return -1;
}

int set_texture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect, int flip)
{
  int render_copy = (!flip) ? SDL_RenderCopy(renderer, texture, srcRect, destRect) : SDL_RenderCopyEx(renderer, texture, srcRect, destRect, 0, NULL, SDL_FLIP_VERTICAL);
  check(render_copy == 0, "Could not set texture: %s", SDL_GetError());

  return 0;

error:
  SDL_Quit();
  log_err("SDL Error: Shutdown");

  return -1;
}

void present()
{
  SDL_RenderPresent(renderer);
}

void destroy_gfx()
{
  SDL_DestroyWindow(window);
}
