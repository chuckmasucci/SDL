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
    List_push(&renderQueue, &sprite, name);
    debug("Added sprite: %s", name);
    debug("List count: %d", List_count(renderQueue));
    debug("Sprite path: %s", (char*)sprite->path);
}

void render()
{
    if(currentIndex == NULL) {
        currentIndex = renderQueue;
    }

    clear();
    for(int i = 0; i < List_count(renderQueue); i++) {
        renderItem = (Sprite*)&renderQueue->data;
        /*debug("i: %d", i);*/
        debug("Path: %s", (char*)renderItem->path);
        /*debug("size w: %d", renderItem->size->w);*/
        /*setTexture(renderer, renderItem->texture, NULL, renderItem->size);*/
        /*currentIndex = currentIndex->next;*/
    }
    present();
}
