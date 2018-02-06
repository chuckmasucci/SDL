#ifndef animate_h
#define animate_h

#define BEZIER_STEPS 100
#define STEPS 100
#define SPRITE_FRAME_DELAY 100

#include <bezier.h>

enum AnimationType {
    TO_FROM = 1,
    CONTINUOUS = 2,
    FRAMES = 3,
    BEZIER = 4,
    NORMAL = 5
};

typedef enum AnimationAttribute {
    ATTR_X,
    ATTR_Y,
    ATTR_ALPHA
} AnimationAttribute;

typedef struct Animation2 {
    int delay;
    int from;
    int to;
    int time;
    int type;
    int current_step;
    int steps_total;
    int *steps;
} Animation2;

typedef struct Animation {
    char *id;
    int current_step;
    int current_step_xy;
    int delay;
    int is_animating;
    int from_alpha;
    int from_x;
    int from_y;
    int to_alpha;
    int to_x;
    int to_y;
    int *steps_x;
    int *steps_y;
    int time;
    int steps_alpha[STEPS];
    enum AnimationType type;
} Animation;

typedef struct AnimationContinuous {
    Animation anim;
    int speed;
} AnimationContinuous;

typedef struct AnimationBezier {
    Animation anim;
    int current_point;
    Vector2 points[STEPS];
} AnimationBezier;

#endif
