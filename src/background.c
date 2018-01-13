#include <stdlib.h>
#include <time.h>
#include "background.h"
#include "dbg.h"
#include "gfx.h"
#include "player.h"
#include "sprite.h"
#include "render.h"
#include "flags.h"
#include "animate.h"

#define BACKGROUND_SPRITE "gfx/sprites/background.proto4.jpg"
#define BACKGROUND_WIDTH 1024
#define BACKGROUND_HEIGHT 1024
#define BACKGROUND_SPEED 1

float tileAmountX;
float tileAmountY;

int initializeBackground()
{
    tileAmountX = ceil((float)WINDOW_WIDTH / (float)BACKGROUND_WIDTH);
    tileAmountY = ceil((float)WINDOW_HEIGHT / (float)BACKGROUND_HEIGHT) + 1;
    int tileTotal = (int)tileAmountX * (int)tileAmountY;

    int x, y = 0;
    for(x = 0; x < tileTotal; x++) {
        int tilePosX = x % (int)tileAmountX;
        if(tilePosX == 0 && x > 0) {
            y++;
        }
        int tilePosY = y;

        Animation animationParent;
        animationParent.type = CONTINUOUS;
        animationParent.isAnimating = 0;

        AnimationContinuous *backgroundAnimation;
        backgroundAnimation = malloc(sizeof(AnimationToFrom));
        check_mem(backgroundAnimation);
        backgroundAnimation->speed = BACKGROUND_SPEED;
        backgroundAnimation->anim = animationParent;

        SDL_Rect *backgroundSize;
        backgroundSize = malloc(sizeof(SDL_Rect));
        check_mem(backgroundSize);
        backgroundSize->x = tilePosX * BACKGROUND_WIDTH;
        backgroundSize->y = tilePosY * BACKGROUND_HEIGHT;
        backgroundSize->w = BACKGROUND_WIDTH;
        backgroundSize->h = BACKGROUND_HEIGHT;

        char *backgroundName;
        backgroundName = malloc(20 * sizeof(char));
        check_mem(backgroundName);
        sprintf(backgroundName, "Background%d", x);

        Sprite *backgroundSprite = createSprite(backgroundName, BACKGROUND_SPRITE, 0, 1, backgroundSize, NULL, backgroundAnimation);
        backgroundSprite->flags |= FLAG_ANIMATING;
        addToRender(backgroundSprite, Z_RENDER_0);
    }

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing background: Shutdown");
    return -1;
}

void updateBackground(SDL_Rect *bgRect)
{
    if(bgRect->y >= WINDOW_HEIGHT) {
        bgRect->y -= tileAmountY * BACKGROUND_HEIGHT;
    }
}
