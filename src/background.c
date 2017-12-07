#include <stdlib.h>
#include <time.h>
#include "background.h"
#include "dbg.h"
#include "gfx.h"
#include "player.h"
#include "sprite.h"
#include "render.h"

int test = 50;
SDL_Point *points;
void *getGeneratedBackground()
{
    stars = 1000;
    points = malloc(stars * sizeof(SDL_Point));
    for (int i = 0; i < stars; ++i) {
        int x = rng(WINDOW_WIDTH);
        int y = rng(WINDOW_HEIGHT);
        SDL_Point point = {x, y};
        points[i] = point;
    }
}

SDL_Rect backgroundSize = {
    .x = 0,
    .y = 0,
    .w = 800,
    .h = 600
};
void setBitmapBackground() {
    Sprite *backgroundSprite = createSprite("background", "gfx/sprites/background.proto1.png", 0, 1, &backgroundSize, NULL, NULL);
    addToRender(backgroundSprite, "background");
}

void renderBackground()
{
    /*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);*/
    clear();
    /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);*/
    /*SDL_RenderDrawPoints(renderer, points, stars);*/
}

int rng(int limit)
{
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do {
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}
