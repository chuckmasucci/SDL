/*
 * =====================================================================================
 *
 *       Filename:  animation.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/2018 11:20:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <list.h>
#include "animate.h"
#include "easing.h"
#include "gfx.h"

Animation2 *add_animation_attrs(int type, int delay, int from, int to, int time, int loop)
{
    Animation2 *animation;
    animation = malloc(sizeof(Animation2));
    animation->delay = delay;
    animation->from = from;
    animation->to = to;
    animation->time = time;
    animation->type = type;
    animation->time_start = 0;
    animation->time_end = 0;

    animation->current_step = 0;
    animation->steps = 0;

    int delta = from - to;
    int steps_total = FPS * (time / 1000);
    int *steps = malloc(steps_total * sizeof(int));
    animation->steps = malloc(steps_total * sizeof(int));

    int reverse_ease = (from < to) ? 0 : 1;

    for(int i = 0; i <= steps_total; i++) {
        float ratio = (float)i / steps_total;
        // TODO: This needs to come from an argument - function pointer
        AHFloat ease = LinearInterpolation(ratio);
        int step = ((int)floor(delta) * (reverse_ease - ease)) + to;
        steps[i] = step;
    }
    animation->steps = steps;
    animation->steps_total = steps_total;

    return animation;
}
