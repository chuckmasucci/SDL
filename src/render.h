#ifndef render_h
#define render_h

#define Z_RENDER_0 0
#define Z_RENDER_1 1
#define Z_RENDER_2 2

#include <list.h>
#include "sprite.h"

int initialize_render();
Node *get_render_list(int index);
void animate(Sprite *sprite);
void render();
void add_to_render();
void destroy_render_queue();

#endif
