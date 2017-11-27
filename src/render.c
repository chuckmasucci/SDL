#include <SDL2/SDL.h>
#include "gfx.h"
#include "dbg.h"
#include "libs/list.h"
#include "player.h"

Node *renderQueue = NULL;
Node *currentIndex = NULL;
Sprite *renderItem = NULL;

void addToRender(Sprite sprite)
{
    List_push(&renderQueue, &sprite);
}

void render()
{
    if(currentIndex == NULL) {
        currentIndex = renderQueue;
    }

    clear();
    for(int i = 0; i < List_count(renderQueue); i++) {
        renderItem = renderQueue->data;
        setTexture(renderer, playerSprite.texture, NULL, playerSprite.size);
        currentIndex = renderQueue->next;
    }
    present();
}
