#ifndef animate_h
#define animate_h
#define BEZIER_STEPS 100
#define STEPS 100

#include <bezier.h>

enum AnimationType {
    TO_FROM = 1,
    CONTINUOUS = 2,
    FRAMES = 3,
    BEZIER = 4,
    NORMAL = 5
};

typedef struct Animation {
    char *id;
    int current_step;
    int delay;
    int is_animating;
    int from_alpha;
    int from_x;
    int from_y;
    int to_alpha;
    int to_x;
    int to_y;
    int steps_alpha[STEPS];
    int steps_x[STEPS];
    int steps_y[STEPS];
    enum AnimationType type;
} Animation;

typedef struct AnimationToFrom {
    Animation anim;
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    int current_x;
    int current_y;
} AnimationToFrom;

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
