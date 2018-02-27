#include <stdio.h>
#include <SDL2/SDL.h>
#include <bezier.h>
#include <darray.h>
#include <dbg.h>
#include <list.h>
#include "animate.h"
#include "background.h"
#include "event.h"
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

int speed2 = 10;

int get_total_animation_duration(Node *animations);

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
    /*debug("queue: %p", queue);*/
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

                /*if(strstr(render_sprite->id, "Background") != NULL) {*/
                    /*update_background(render_sprite->size);*/
                /*}*/

                // Animation
                int animation_count = List_count(render_sprite->animations);
                if(animation_count > 0) {
                    animate(render_sprite);
                }
                /*if(render_sprite->frames > 0 || render_sprite->flags & FLAG_ANIMATING && render_sprite->animation) {*/
                    /*animate(render_sprite);*/
                /*}*/

                // Cleanup
                if(render_sprite->flags & FLAG_REMOVE) {
                    updated_node = cleanup_sprite(render_sprite, &renderer_current, current_node->id);
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
                    set_texture(renderer, render_sprite->texture, render_sprite->mask, render_sprite->size, flip_texture);
                }
            }
        }
    }
    present();
}

void animate_default(Sprite *sprite)
{
}

void animate_sprite_frames(Sprite *sprite)
{
    check(sprite != NULL, "Invalid sprite");

    SDL_Rect *mask = (SDL_RectEmpty(sprite->mask)) ? NULL : sprite->mask;
    int frame = (SDL_GetTicks() / SPRITE_FRAME_DELAY) % sprite->frames;
    mask->y = frame * mask->h;

error:
    return;
}

void animate(Sprite *sprite)
{
    // Get animation list
    Node *animations = (Node *)sprite->animations;
    Node *current_node = animations;
    Node *next_node = NULL;

    // Do sprite frame animation
    if(sprite->frames > 0) {
        animate_sprite_frames(sprite);
    }
    Animation2 *animation = NULL;
    int animation_count = List_count(animations);
    int duration_total = get_total_animation_duration(animations);

    for(int i = 0; i < animation_count; i++) {
        animation = current_node->data;

        if(animation->current_step < animation->steps_total) {
            animation->current_step++;
        }

        switch(animation->type) {
            case ATTR_X:
                /*debug("%s: x delay: %d, to: %d, from: %d, value: %d, current_step: %d", sprite->id, animation->delay, animation->to, animation->from, animation->steps[animation->current_step], animation->current_step);*/
                sprite->size->x = animation->steps[animation->current_step];
                break;
            case ATTR_Y:
                /*debug("%s: y delay: %d, to: %d, from: %d, value: %d, current_step: %d", sprite->id, animation->delay, animation->to, animation->from, animation->steps[animation->current_step], animation->current_step);*/
                sprite->size->y = animation->steps[animation->current_step];
                debug("y: %d", sprite->size->y);
                break;
        }

        if(animation->time_start == 0 && animation->time_end == 0) {
            animation->time_start = SDL_GetTicks();
            animation->time_end = animation->delay + animation->time_start + animation->time;
        }

        next_node = current_node->next;

        if(SDL_GetTicks() >= animation->time_end) {
            next_node = List_remove(&sprite->animations, current_node->id);
            if(!next_node) {
                sprite->animations = NULL;
                debug("dispatch event");
                dispatch_event(sprite->id);
                break;
            }
        }

        current_node = next_node;
    }
}

int get_total_animation_duration(Node *animations)
{
    int animation_count = List_count(animations);
    Node *current_animation = animations;
    int max = 0;

    for(int i = 0; i < animation_count; i++) {
        Animation2 *animation = ((Animation2 *)current_animation->data);
        int current_duration = animation->delay + animation->time;

        if(current_duration > max) {
            max = current_duration;
        }
        current_animation = animations->next;
    }

    return max;
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
                destroy_sprite(render_sprite);
                current_node = List_remove(&renderer_current, current_node->id);
            }
        }
    }
}
