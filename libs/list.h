#ifndef list_h
#define list_h

#include <stdlib.h>
#include "../src/sprite.h"

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

void List_push(struct Node **headRef, void *newData);
int List_count(Node *headRef);
Node *List_remove(struct Node **headRef, Sprite *sprite);
void List_destroy(struct Node **headRef);
#endif
