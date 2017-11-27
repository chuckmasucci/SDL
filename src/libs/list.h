#include <stdlib.h>

typedef struct Node {
    void *data;
    char *name;
    struct Node *next;
} Node;

void List_push(struct Node **headRef, void *newData, char *name);
int List_count(Node *headRef);
