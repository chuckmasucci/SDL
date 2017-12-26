#ifndef render_h
#define render_h

#define Z_RENDER_0 0
#define Z_RENDER_1 1

#include "sprite.h"

int initializeRender();
void animateSpriteRects(Sprite *sprite);
void render();
void addToRender();
void destroyRenderQueue();

#endif
