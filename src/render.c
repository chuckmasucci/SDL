#include <SDL2/SDL.h>
#include <list.h>
#include <stdio.h>
#include "gfx.h"
#include "dbg.h"
#include "player.h"

Node *renderQueue = NULL;
Node *currentIndex = NULL;
Sprite *renderItem = NULL;

void addToRender(Sprite *sprite, char *name)
{
    List_push(&renderQueue, sprite, name);
}

int curr_secs;
int prev_secs;
int distance = 100;
int time = 100;
int speed;
void render(float timeDelta)
{
    SDL_Rect *mask;
    int ms = SDL_GetTicks();
    int frameDelay = 100;
    int frame;

    speed = distance / time;

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
            int seconds = (ms / 1);
            curr_secs = seconds;
            if(curr_secs > prev_secs) {
                debug("delta: %f", 1 / timeDelta);
                renderItem->size->y -= 1;
            }
            prev_secs = curr_secs;
        }

        setTexture(renderer, renderItem->texture, mask, renderItem->size);
        currentIndex = currentIndex->next;
    }
    present();
}
