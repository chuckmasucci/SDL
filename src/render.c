#include <SDL2/SDL.h>
#include <list.h>
#include <stdio.h>
#include "gfx.h"
#include "dbg.h"
#include "player.h"
#include "sprite.h"

Node *renderQueue = NULL;
Node *currentIndex = NULL;
Sprite *renderItem = NULL;

void addToRender(Sprite *sprite, char *name)
{
    List_push(&renderQueue, sprite, name);
}

int time = 100;
int speed1 = 5;
int speed2 = 10;

void render(float timeDelta)
{
    SDL_Rect *mask;
    int ms = SDL_GetTicks();
    int frameDelay = 100;
    int frame;

    if(currentIndex == NULL) {
        currentIndex = renderQueue;
    }

    clear();
    for(int i = 0; i < List_count(renderQueue); i++) {
        renderItem = (Sprite*)currentIndex->data;

        if(SDL_RectEmpty(renderItem->mask)) {
            mask = NULL;
        } else {
            mask = renderItem->mask;
        }

        if(renderItem->frames > 0) {
            frame = (SDL_GetTicks() / frameDelay) % renderItem->frames;
            mask->y = frame * 20;
        }

        if(renderItem->isAnimating) {
            /*debug("delta: %f", 1 / timeDelta);*/
            renderItem->size->y -= speed2;
            debug("Anim from fromx: %d", renderItem->animation->fromX);
            debug("Anim from fromy: %d", renderItem->animation->fromY);
            debug("Anim from tox: %d", renderItem->animation->toX);
            debug("Anim from toy: %d", renderItem->animation->toY);
        }

        setTexture(renderer, renderItem->texture, mask, renderItem->size);
        currentIndex = currentIndex->next;
    }
    present();
}
