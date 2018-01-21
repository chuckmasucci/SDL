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

Node *eventStack = NULL;

int addEventListener(char *name, void (*handler)(void))
{
    Event *event;
    event = malloc(sizeof(Event));
    event->name = malloc(sizeof(name));
    strcpy(event->name, name);
    event->handler = handler;

    List_push(&eventStack, event);

    return 0;
}

int dispatchEvent(char *name)
{
    int count = List_count(eventStack);
    Event *event = (Event *)eventStack->data;
    for(int i = 0; i < count; i++) {
        if(strcmp(name, event->name) == 0) {
            event->handler();
            if(eventStack->next) {
                event = (Event *)eventStack->next->data;
            }
        }
    }

    return 0;
}
