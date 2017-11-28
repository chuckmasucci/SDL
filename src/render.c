#include <SDL2/SDL.h>
#include "gfx.h"
#include "dbg.h"
#include "libs/list.h"
#include "player.h"

Node *renderQueue = NULL;
Node *currentIndex = NULL;
Sprite *renderItem = NULL;

void addToRender(Sprite *sprite, char *name)
{
    List_push(&renderQueue, sprite, name);
}

void render()
{
    SDL_Rect *mask;

    if(currentIndex == NULL) {
        currentIndex = renderQueue;
    }

    clear();
    for(int i = 0; i < List_count(renderQueue); i++) {
        renderItem = (Sprite*)currentIndex->data;
        debug("current name: %s", currentIndex->name);

        if(SDL_RectEmpty(renderItem->mask)) {
            mask = NULL;
        } else {
            mask = renderItem->mask;
        }

        setTexture(renderer, renderItem->texture, mask, renderItem->size);
        currentIndex = currentIndex->next;
    }
    present();
}
