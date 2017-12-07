#include <stdlib.h>
#include <time.h>
#include "background.h"
#include "dbg.h"
#include "gfx.h"
#include "player.h"

int test = 50;
SDL_Point *points;
void *getBackground()
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

void renderBackground()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    clear();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoints(renderer, points, stars);
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
