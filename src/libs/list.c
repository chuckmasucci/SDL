#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../dbg.h"

void List_push(struct Node **headRef, void *newData, char *name)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *headRef;
    newNode->name = name;
    *headRef = newNode;
}

void List_remove(struct Node **headRef, void *data)
{

}

int List_count(Node *headRef)
{
    if(headRef == NULL) {
        return 0;
    }

    return 1 + List_count(headRef->next);
}
