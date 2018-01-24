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

#define SECOND_ELAPSED "second_elapsed"

typedef struct Event {
    char *name;
    void (*handler)();
} Event;

int add_event_listener(char *name, void (*handler)());
int dispatch_event(char *name);
