#include <SDL2/SDL.h>
#include <list.h>
#include <stdio.h>
#include "gfx.h"
#include "dbg.h"
#include "player.h"
#include "sprite.h"
#include "flags.h"
#include "background.h"

Node *renderQueue = NULL;
Node *currentNode = NULL;
Sprite *renderSprite = NULL;
int speed1 = 5;
int speed2 = 10;

void addToRender(Sprite *sprite)
{
    check(sprite != NULL, "Bad sprite added to render queue");
    List_push(&renderQueue, sprite);

error:
    return;
}

void render(float timeDelta)
{
    SDL_Rect *mask;
    int ms = SDL_GetTicks();
    int frameDelay = 100;
    int frame;
    int shouldRender = 1;
    int removed = 0;
    Node *updatedNode;

    if(currentNode == NULL) {
        currentNode = renderQueue;
    }

    renderBackground();

    int renderAmt = List_count(renderQueue);
    for(int i = 0; i < renderAmt; i++) {
        renderSprite = (Sprite*)currentNode->data;

        mask = (SDL_RectEmpty(renderSprite->mask)) ? NULL  : renderSprite->mask;
        if(renderSprite->frames > 0) {
            frame = (SDL_GetTicks() / frameDelay) % renderSprite->frames;
            mask->y = frame * mask->h;
        }
        if(renderSprite->animation && renderSprite->flags) {
            if(*(renderSprite)->flags & FLAG_ANIMATING) {
                if(!renderSprite->animation->isAnimating) {
                    renderSprite->size->x = renderSprite->animation->fromX;
                    renderSprite->size->y = renderSprite->animation->fromY;
                    renderSprite->animation->isAnimating = 1;
                } else {
                    if(renderSprite->size->y > renderSprite->animation->toY) {
                        renderSprite->size->y -= speed2;
                    } else {
                        *(renderSprite)->flags |= FLAG_REMOVE;
                    }
                }
            }
        }

        setTexture(renderer, renderSprite->texture, mask, renderSprite->size);

        if(renderSprite->flags) {
            if(*(renderSprite)->flags & FLAG_REMOVE) {
                *(renderSprite)->flags &= ~(FLAG_REMOVE);
                removed = 1;
                updatedNode = List_remove(&renderQueue, renderSprite);
            }
        }
        if(!removed) {
            currentNode = currentNode->next;
        } else {
            currentNode = updatedNode;
            removed = 0;
        }
    }

    present();
}

void destroyRenderQueue()
{
    List_destroy(&renderQueue);
}
