/* render
 * =====================================================================================
 *
 *       Filename:  event.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/17/2018 04:25:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <dbg.h>
#include <list.h>
#include "event.h"
#include "sprite.h"

void destroy_event(Event *event);
Node *event_stack = NULL;

int add_event_listener(char *name, void (*handler)(void *), void *arg)
{
    Event *event;
    event = malloc(sizeof(Event));
    event->name = malloc(sizeof(name));
    strcpy(event->name, name);
    event->handler = handler;
    event->arg = arg;

    List_push(&event_stack, event);

    return 0;
}

int dispatch_event(char *name)
{
    int count = List_count(event_stack);
    Node *node_current = event_stack;
    Event *event = (Event *)event_stack->data;
    for(int i = 0; i < count; i++) {
        if(strcmp(name, event->name) == 0) {
            event->handler(event->arg);
            destroy_event(event);
            Node *node_next = node_current->next;
            List_remove(&event_stack, node_current->id);
            break;
        }

        if(node_current->next) {
            event = (Event *)node_current->next->data;
            node_current = node_current->next;
        }
    }

    return 0;
}

void destroy_event(Event *event)
{
    free(event->name);
    free(event);
}
