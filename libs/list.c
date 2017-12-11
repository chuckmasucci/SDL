#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../src/sprite.h"
#include "../src/render.h"
#include "../src/dbg.h"

void List_print(struct Node **headRef)
{
    if(headRef == NULL) {
        log_warn("List is empty");
    }

    Node *currentNode = *headRef;
    log_info("List count: %d", List_count(*headRef));
    for(int i = 0; i < List_count(*headRef); i++) {
        Sprite *data = currentNode->data;
        log_info("%s", data->id);
        currentNode = currentNode->next;
    }
}

void List_destroy(struct Node **headRef)
{
    check(headRef != NULL, "Node headRef is null");

    Node *currentNode = *headRef;
    Node *nextNode;
    int listCount = List_count(*headRef);
    for(int i = 0; i < listCount; i++) {
        Sprite *data = currentNode->data;
        nextNode = currentNode->next;
        destroySprite(data);
        free(currentNode);
        if(nextNode) {
            currentNode = nextNode;
        }
    }
    *headRef = NULL;
    return;

error:
    log_warn("List destroy: An error occurred");
    return;
}

void List_push(struct Node **headRef, void *newData)
{
    if(headRef == NULL) {
        log_warn("List is empty");
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *headRef;
    *headRef = newNode;
}

Node *List_remove(struct Node **headRef, Sprite *sprite)
{
    check(headRef != NULL, "Node headRef is null");
    check(sprite != NULL, "Sprite is null");

    Node *current = *headRef;
    Node *nodeToDelete;
    Node *nodeToMove;
    Node *nodeNext;

    int renderAmt = List_count(*headRef);
    for(int i = 0; i < renderAmt; i++) {
        // We are removing the head node
        Sprite *data = current->data;
        Sprite *dataNext = current->next->data;
        if(data->id == sprite->id && i == 0) {
            nodeToDelete = current;
            if(current->next) {
                nodeToMove = current->next;
            }
            *headRef = nodeToMove;
            nodeNext = *headRef;

            // Clean up
            destroySprite(nodeToDelete->data);
            free(nodeToDelete);

            break;
        // We are removing a non-head node
        } else if(dataNext->id == sprite->id) {
            // This is the node we are going to delete
            nodeToDelete = current->next;

            // This is the node we are moving
            nodeToMove = nodeToDelete->next;

            // Repoint the node to move
            current->next = nodeToMove;

            // Set the head
            nodeNext = nodeToMove;

            // Clean up
            destroySprite(nodeToDelete->data);
            free(nodeToDelete);

            break;
        }
        current = current->next;
    }

    return nodeNext;

error:
    log_warn("List remove: An error occurred");
    return NULL;
}

int List_count(Node *headRef)
{
    if(headRef == NULL) {
        return 0;
    }

    return 1 + List_count(headRef->next);
}
