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
#include <dbg.h>
#include <list.h>
#include <stdlib.h>
#include "animate.h"
#include "easing.h"
#include "gfx.h"

Animation2 *add_animation_attrs(int type, int delay, int *steps, int duration, int loop)
{
    Animation2 *animation;
    animation = malloc(sizeof(Animation2));
    animation->delay = delay;
    animation->time = duration;
    animation->type = type;
    animation->time_start = 0;
    animation->time_end = 0;
    animation->current_step = 0;

    int steps_total = FPS * (duration / 1000);
    animation->steps = malloc(steps_total * sizeof(int));
    animation->steps = steps;
    animation->steps_total = steps_total;

    return animation;
}

int *get_linear_points(unsigned int from, unsigned int to, unsigned int duration, AHFloat (ease_func)(AHFloat))
{
    int delta = from - to;
    int steps_total = FPS * (duration / 1000);
    int *steps = malloc(sizeof(int) * steps_total);

    int reverse_ease = (from < to) ? 0 : 1;

    for(int i = 0; i <= steps_total; i++) {
        float ratio = (float)i / steps_total;
        AHFloat ease = ease_func(ratio);
        int step = ((int)floor(delta) * (reverse_ease - ease)) + to;
        steps[i] = step;
    }

    return steps;
}

int *get_bezier_points(CubicBezierPoints points, unsigned int duration, AHFloat (ease_func)(AHFloat), int type)
{
    int steps_total = FPS * (duration / 1000);
    int *steps = malloc(sizeof(int) * steps_total);

    for(int i = 0; i < steps_total; i++) {
        float t = (float)i / (float)steps_total;
        AHFloat p = CubicEaseInOut(t);
        Vector2 point = getCubicBezierPoint(p, points.p0, points.p1, points.p2, points.p3);
        if(type == ATTR_X) {
            steps[i] = (int)point.x;
        } else if(type == ATTR_Y) {
            steps[i] = (int)point.y;
        }
    }

    return steps;
}
