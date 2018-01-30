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
Node *render_index_1 = NULL;
Node *render_index_2 = NULL;
Node *render_index_3 = NULL;
Node *current_node = NULL;

Sprite *render_sprite = NULL;

int speed1 = 5;
int speed2 = 10;

Node *cleanup_sprite(Sprite *sprite, Node **render_index);

int initialize_render()
{
    renderers[0] = &render_index_1;
    renderers[1] = &render_index_2;
    renderers[2] = &render_index_3;

    int len = sizeof(renderers) / sizeof(renderers[0]);

    return 0;
}

Node *get_render_list(int index)
{
    return *renderers[index];
}

void add_to_render(Sprite *sprite, int z_index)
{
    Node **queue = renderers[z_index];
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
            Node *renderer_current = *renderers[i];
            Node *updated_node = NULL;
            int j = 0;
            int queue_count = List_count(renderer_current);
            current_node = renderer_current;
            for(j = 0; j < queue_count; j++) {
                render_sprite = (Sprite*)current_node->data;

                if(strstr(render_sprite->id, "Background") != NULL) {
                    update_background(render_sprite->size);
                }

                // Animation
                if(render_sprite->frames > 0 || render_sprite->flags & FLAG_ANIMATING && render_sprite->animation) {
                    animate_sprite_rects(render_sprite);
                }

                // Cleanup
                if(render_sprite->flags & FLAG_REMOVE) {
                    updated_node = cleanup_sprite(render_sprite, &renderer_current);
                    render_sprite = NULL;
                    if(queue_count == 1) {
                        *renderers[i] = NULL;
                        continue;
                    }
                }

                // Set the next current node
                if(!updated_node) {
                    current_node = current_node->next;
                } else {
                    current_node = updated_node;
                }

                if(render_sprite) {
                    int flip_texture = (render_sprite->flags & FLAG_FLIPPED) ? 1 : 0;
                    /*SDL_SetTextureAlphaMod(render_sprite->texture, 128);*/
                    set_texture(renderer, render_sprite->texture, render_sprite->mask, render_sprite->size, flip_texture);
                }
            }
        }
    }

    present();
}

void animate_sprite_rects(Sprite *sprite)
{
    SDL_Rect *mask = (SDL_RectEmpty(sprite->mask)) ? NULL : sprite->mask;

    // Do sprite frame animation
    if(sprite->frames > 0) {
        int frame_delay = 100;
        int frame = (SDL_GetTicks() / frame_delay) % sprite->frames;
        mask->y = frame * mask->h;
    }

    // Do x,y animation
    if(sprite->flags & FLAG_ANIMATING && sprite->animation)  {
        Animation *animation = (Animation *)sprite->animation;

        if(animation->delay <= ms_elapsed) {
            if(animation->steps_alpha[0] != -1) {
                int current_alpha = animation->steps_alpha[animation->current_step];
                if(animation->steps_alpha[animation->current_step] > -1 && animation->current_step < STEPS) {
                    SDL_SetTextureAlphaMod(sprite->texture, current_alpha);
                    animation->current_step++;
                }
            }
        }

        if(animation->type == TO_FROM) {
            AnimationToFrom *animation = sprite->animation;
            if(!animation->anim.is_animating) {
                // Start the animation
                sprite->size->x = animation->from_x;
                sprite->size->y = animation->from_y;
                animation->anim.is_animating = 1;
            } else {
                // Continue the animation & add 'remove' flag when complete
                if(sprite->size->y > animation->to_y) {
                    sprite->size->y -= speed2;
                } else {
                    sprite->flags |= FLAG_REMOVE;
                }
            }
        } else if(animation->type == CONTINUOUS) {
            AnimationContinuous *animation = sprite->animation;
            sprite->size->y += animation->speed;
        } else if(animation->type == BEZIER) {
            if(animation->delay <= ms_elapsed) {
                AnimationBezier *animation = (AnimationBezier *)sprite->animation;
                if(animation->current_point < STEPS-1) {
                    animation->current_point++;
                    sprite->size->x = (int)animation->points[animation->current_point].x;
                    sprite->size->y = (int)animation->points[animation->current_point].y;
                } else {
                    /*debug("x: %d: %d", animation->current_point, (int)animation->points[animation->current_point].x);*/
                    /*debug("y: %d: %d", animation->current_point, (int)animation->points[animation->current_point].y);*/
                }
            }
        }
    }
}

Node *cleanup_sprite(Sprite *sprite, Node **render_index)
{
    Node *updated_node;

    // Clean up the sprite
    if(sprite->flags & FLAG_REMOVE) {
        // Remove the flag
        sprite->flags &= ~(FLAG_REMOVE);

        // Destroy the sprite
        destroySprite(sprite);

        // Remove the node and get the next node
        updated_node = List_remove(render_index, current_node->id);

        return updated_node;
    }

    return NULL;
}

void destroy_render_queue()
{
    int i;
    for(i = 0; i < RENDERER_AMT; i++) {
        if(*renderers[i] != NULL) {
            Node *renderer_current = *renderers[i];
            int j = 0;
            int queue_count = List_count(renderer_current);
            current_node = renderer_current;
            for(j = 0; j < queue_count; j++) {
                render_sprite = (Sprite*)current_node->data;
                destroySprite(render_sprite);
                current_node = List_remove(&renderer_current, current_node->id);
            }
        }
    }
}
