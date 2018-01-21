#include <stdio.h>
#include <SDL2/SDL.h>
#include <bezier.h>
#include <darray.h>
#include <dbg.h>
#include <list.h>
#include "animate.h"
#include "background.h"
#include "flags.h"
#include "gfx.h"
#include "player.h"
#include "render.h"
#include "spacegame.h"
#include "sprite.h"

#define RENDERER_AMT 3

Node **renderers[RENDERER_AMT];
Node *renderIndex_1 = NULL;
Node *renderIndex_2 = NULL;
Node *renderIndex_3 = NULL;
Node *currentNode = NULL;

Sprite *renderSprite = NULL;

int speed1 = 5;
int speed2 = 10;

Node *cleanupSprite(Sprite *sprite, Node **renderIndex);

int initializeRender() {
    renderers[0] = &renderIndex_1;
    renderers[1] = &renderIndex_2;
    renderers[2] = &renderIndex_3;

    int len = sizeof(renderers) / sizeof(renderers[0]);

    return 0;
}

void addToRender(Sprite *sprite, int zIndex)
{
    Node **queue = renderers[zIndex];
    check(sprite != NULL, "Bad sprite added to render queue");
    check(queue != NULL, "Array index out of range");

    List_push(queue, sprite);

error:
    return;
}

void render()
{
    int i = 0;
    clear();
    for(i = 0; i < RENDERER_AMT; i++) {
        if(*renderers[i] != NULL) {
            Node *rendererCurrent = *renderers[i];
            Node *updatedNode = NULL;
            int j = 0;
            int queueCount = List_count(rendererCurrent);
            currentNode = rendererCurrent;
            for(j = 0; j < queueCount; j++) {
                renderSprite = (Sprite*)currentNode->data;

                if(strstr(renderSprite->id, "Background") != NULL) {
                    updateBackground(renderSprite->size);
                }

                // Animation
                if(renderSprite->frames > 0 || renderSprite->flags & FLAG_ANIMATING && renderSprite->animation) {
                    animateSpriteRects(renderSprite);
                }

                // Cleanup
                if(renderSprite->flags & FLAG_REMOVE) {
                    updatedNode = cleanupSprite(renderSprite, &rendererCurrent);
                    renderSprite = NULL;
                    if(queueCount == 1) {
                        *renderers[i] = NULL;
                        continue;
                    }
                }

                // Set the next current node
                if(!updatedNode) {
                    currentNode = currentNode->next;
                } else {
                    currentNode = updatedNode;
                }

                if(renderSprite) {
                    int flipTexture = (renderSprite->flags & FLAG_FLIPPED) ? 1 : 0;
                    setTexture(renderer, renderSprite->texture, renderSprite->mask, renderSprite->size, flipTexture);
                }
            }
        }
    }

    present();
}

void animateSpriteRects(Sprite *sprite)
{
    SDL_Rect *mask = (SDL_RectEmpty(sprite->mask)) ? NULL : sprite->mask;

    // Do sprite frame animation
    if(sprite->frames > 0) {
        int frameDelay = 100;
        int frame = (SDL_GetTicks() / frameDelay) % sprite->frames;
        mask->y = frame * mask->h;
    }

    // Do x,y animation
    if(sprite->flags & FLAG_ANIMATING && sprite->animation)  {
        Animation *animation = (Animation *)sprite->animation;
        if(animation->type == TO_FROM) {
            AnimationToFrom *animation = sprite->animation;
            if(!animation->anim.isAnimating) {
                // Start the animation
                sprite->size->x = animation->fromX;
                sprite->size->y = animation->fromY;
                animation->anim.isAnimating = 1;
            } else {
                // Continue the animation & add 'remove' flag when complete
                if(sprite->size->y > animation->toY) {
                    sprite->size->y -= speed2;
                } else {
                    sprite->flags |= FLAG_REMOVE;
                }
            }
        } else if(animation->type == CONTINUOUS) {
            AnimationContinuous *animation = sprite->animation;
            sprite->size->y += animation->speed;
        } else if(animation->type == BEZIER) {
            if(animation->delay <= msElapsed) {
                AnimationBezier *animation = sprite->animation;
                if(animation->currentPoint < BEZIER_STEPS) {
                    animation->currentPoint++;
                    sprite->size->x = (int)animation->points[animation->currentPoint].x;
                    sprite->size->y = (int)animation->points[animation->currentPoint].y;
                } else {
                    /*debug("x: %d", (int)animation->points[animation->currentPoint].x);*/
                    /*debug("y: %d", (int)animation->points[animation->currentPoint].y);*/
                }
            }
        }
    }
}

Node *cleanupSprite(Sprite *sprite, Node **renderIndex)
{
    Node *updatedNode;

    // Clean up the sprite
    if(sprite->flags & FLAG_REMOVE) {
        // Remove the flag
        sprite->flags &= ~(FLAG_REMOVE);

        // Destroy the sprite
        destroySprite(sprite);

        // Remove the node and get the next node
        updatedNode = List_remove(renderIndex, currentNode->id);

        return updatedNode;
    }

    return NULL;
}

void destroyRenderQueue()
{
    int i;
    for(i = 0; i < RENDERER_AMT; i++) {
        if(*renderers[i] != NULL) {
            Node *rendererCurrent = *renderers[i];
            int j = 0;
            int queueCount = List_count(rendererCurrent);
            currentNode = rendererCurrent;
            for(j = 0; j < queueCount; j++) {
                renderSprite = (Sprite*)currentNode->data;
                destroySprite(renderSprite);
                currentNode = List_remove(&rendererCurrent, currentNode->id);
            }
        }
    }
}
