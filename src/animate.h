#ifndef animate_h
#define animate_h
#define BEZIER_STEPS 100

#include <bezier.h>

enum AnimationType {
    TO_FROM = 1,
    CONTINUOUS = 2,
    FRAMES = 3,
    BEZIER = 4
};

typedef struct Animation {
    enum AnimationType type;
    int is_animating;
    int delay;
} Animation;

typedef struct AnimationToFrom {
    Animation anim;
    int fromX;
    int fromY;
    int toX;
    int to_y;
    int currentX;
    int currentY;
} AnimationToFrom;

typedef struct AnimationContinuous {
    Animation anim;
    int speed;
} AnimationContinuous;

typedef struct AnimationBezier {
    Animation anim;
    int current_point;
    Vector2 points[BEZIER_STEPS];
} AnimationBezier;

#endif
