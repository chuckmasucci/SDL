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


SDL_Rect *backgroundSize;
int setBitmapBackground() {
    backgroundSize = malloc(sizeof(SDL_Rect));
    check_mem(backgroundSize);
    backgroundSize->x = 0;
    backgroundSize->y = 0;
    backgroundSize->w = 2560;
    backgroundSize->h = 1600;

    char *backgroundName = malloc(20 * sizeof(char));
    check_mem(backgroundName);
    strncpy(backgroundName, "background", 20);

    Sprite *backgroundSprite = createSprite(backgroundName, "gfx/sprites/background.proto3.jpg", 0, 1, backgroundSize, NULL, NULL);
    addToRender(backgroundSprite, Z_RENDER_0);

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing player: Shutdown");
    return -1;
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

void destroyBackground()
{
    free(points);
}
