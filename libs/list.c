#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../src/sprite.h"
#include "../src/render.h"
#include "../src/dbg.h"

void List_print(struct Node **headRef) {
    Node *currentNode = *headRef;
    for(int i = 0; i < List_count(*headRef); i++) {
        currentNode = currentNode->next;
    }
}

void List_push(struct Node **headRef, void *newData, char *name)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *headRef;
    newNode->name = name;
    newNode->flagged = 0;
    *headRef = newNode;
}

void List_remove(struct Node **headRef, Sprite *sprite)
{
    Node *current = *headRef;
    Node *tempNode;

    int renderAmt = List_count(*headRef);
    for(int i = 0; i < renderAmt; i++) {
        if(current->name == sprite->id && i == 0) {
            tempNode = current->next;
            *headRef = tempNode;
            destroySprite(sprite);
            List_print(headRef);
            break;
        } else if(current->next->name == sprite->id && i >= 0) {
            tempNode = current->next;
            if(tempNode->name == sprite->id) {
                current->next = tempNode->next;
            }
            destroySprite(sprite);
            List_print(headRef);
            break;
        }
        current = current->next;
    }
}

int List_count(Node *headRef)
{
    if(headRef == NULL) {
        return 0;
    }

    return 1 + List_count(headRef->next);
}
