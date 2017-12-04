#ifndef list_h
#define list_h

#include <stdlib.h>
#include "../src/sprite.h"

typedef struct Node {
    void *data;
    char *name;
    uint flagged;
    struct Node *next;
} Node;

void List_push(struct Node **headRef, void *newData, char *name);
int List_count(Node *headRef);
void List_remove(struct Node **headRef, Sprite *sprite);
#endif
