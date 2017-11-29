#ifndef animate_h
#define animate_h
typedef struct Animation {
    int fromX;
    int fromY;
    int toX;
    int toY;
    int currentX;
    int currentY;
    int isAnimating;
} Animation;
#endif
