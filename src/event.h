/* 

 * =====================================================================================
 *
 *       Filename:  event.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/17/2018 06:12:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "sprite.h"

typedef struct Event {
    char *name;
    void (*handler)();
    void *arg;
} Event;

int add_event_listener(char *name, void (*handler)(void *), void *arg);
int dispatch_event(char *name);
