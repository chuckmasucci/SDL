#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

void List_push(struct Node **headRef, void *newData);
int List_count(Node *headRef);
