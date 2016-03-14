#ifndef _PRIORITYQUEUE_H_STRUCTBOT
#define _PRIORITYQUEUE_H_STRUCTBOT

#include <stdlib.h> //size_t
#include "structbot/interface.h"

//A priority queue for structbot_event's
typedef struct {
	structbot_event* data;
	size_t mySize;
	size_t capacity;
} structbot_priorityqueue;

//Returns a pointer to an structevent on success, NULL on failure
//The queue is restructured after a remove (lowest child gets to move up, cascaded down)
//The remove is always the top node
structbot_event* priorityqueue_remove(structbot_priorityqueue* pq);

//Adds an event to the priority queue
//This is a min-heap sorted by structbot_event->priority
//returns 0 on success and an error code on failure
int priorityqueue_add(structbot_priorityqueue* pq, structbot_event* e);


#endif //_PRIORITYQUEUE_H_STRUCTBOT
