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

Node *event_stack = NULL;

int add_event_listener(char *name, void (*handler)(void))
{
    Event *event;
    event = malloc(sizeof(Event));
    event->name = malloc(sizeof(name));
    strcpy(event->name, name);
    event->handler = handler;

    List_push(&event_stack, event);

    return 0;
}

int dispatch_event(char *name)
{
    int count = List_count(event_stack);
    Event *event = (Event *)event_stack->data;
    for(int i = 0; i < count; i++) {
        if(strcmp(name, event->name) == 0) {
            event->handler();
            if(event_stack->next) {
                event = (Event *)event_stack->next->data;
            }
        }
    }

    return 0;
}
