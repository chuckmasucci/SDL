#include <stdlib.h>
#include <time.h>
#include "background.h"
#include "dbg.h"
#include "gfx.h"
#include "player.h"
#include "sprite.h"
#include "render.h"
#include "flags.h"
#include "animate.h"

#define BACKGROUND_SPRITE "gfx/sprites/background.proto4.jpg"
#define BACKGROUND_WIDTH 1024
#define BACKGROUND_HEIGHT 1024
#define BACKGROUND_SPEED 1

float tile_amount_x;
float tile_amount_y;

int initialize_background()
{
    tile_amount_x = ceil((float)WINDOW_WIDTH / (float)BACKGROUND_WIDTH);
    tile_amount_y = ceil((float)WINDOW_HEIGHT / (float)BACKGROUND_HEIGHT) + 1;
    int tile_total = (int)tile_amount_x * (int)tile_amount_y;

    int x, y = 0;
    for(x = 0; x < tile_total; x++) {
        int tile_pos_x = x % (int)tile_amount_x;
        if(tile_pos_x == 0 && x > 0) {
            y++;
        }
        int tile_pos_y = y;

        Animation animation_parent;
        animation_parent.type = CONTINUOUS;
        animation_parent.is_animating = 0;

        AnimationContinuous *background_animation;
        background_animation = malloc(sizeof(AnimationToFrom));
        check_mem(background_animation);
        background_animation->speed = BACKGROUND_SPEED;
        background_animation->anim = animation_parent;

        SDL_Rect *background_size;
        background_size = malloc(sizeof(SDL_Rect));
        check_mem(background_size);
        background_size->x = tile_pos_x * BACKGROUND_WIDTH;
        background_size->y = tile_pos_y * BACKGROUND_HEIGHT;
        background_size->w = BACKGROUND_WIDTH;
        background_size->h = BACKGROUND_HEIGHT;

        char *background_name;
        background_name = malloc(20 * sizeof(char));
        check_mem(background_name);
        sprintf(background_name, "Background%d", x);

        Sprite *background_sprite = create_sprite(background_name, BACKGROUND_SPRITE, 0, 100, 1, background_size, NULL, background_animation);
        background_sprite->flags |= FLAG_ANIMATING;
        add_to_render(background_sprite, Z_RENDER_0);
    }

    return 0;

error:
    SDL_Quit();
    log_err("Error while initializing background: Shutdown");
    return -1;
}

void update_background(SDL_Rect *bg_rect)
{
    if(bg_rect->y >= WINDOW_HEIGHT) {
        bg_rect->y -= tile_amount_y * BACKGROUND_HEIGHT;
    }
}
