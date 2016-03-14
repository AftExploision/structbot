#include <stdio.h>

#include "structbot.h"
#include "structbot/interface.h"
#include "structbot/error.h"
#include "priorityqueue.h"

//List of priority queues. This is static length, equal to the number of event types there are
structbot_priorityqueue *queues;

//Prototypes for static functions
static void init_queues();

int main(void) {
	init_queues();
	return 0;
}

int register_event_as_hook(structbot_event* e, bool external) {
	//If the event was external we should ensure the priority is not 0
	if (external && e->priority == 0) {
		e->priority = 1;
	}
	//Add the hook to the right queue
	switch(e->event) {
		case STR_ETT_PROGRAMSTART:
			if (e->priority != 0) {
				return STRUCTBOT_ERR_REASPERMERROR;
			} else {
				return priorityqueue_add(&(queues[0]), e);
			}
		case STR_ETT_SERVERCONNECTION:
			if (e->priority != 0) {
				return STRUCTBOT_ERR_REASPERMERROR;
			} else {
				return priorityqueue_add(&(queues[1]), e);
			}
		case STR_ETT_CHANNELCONNECTION:
			return priorityqueue_add(&(queues[2]), e);
		case STR_ETT_USERJOIN:
			return priorityqueue_add(&(queues[3]), e);
		case STR_ETT_USERLEAVE:
			return priorityqueue_add(&(queues[4]), e);
		case STR_ETT_CHANNELMESG:
			return priorityqueue_add(&(queues[5]), e);
		case STR_ETT_PRIVMSG:
			return priorityqueue_add(&(queues[6]), e);
		case STR_ETT_PING:
			return priorityqueue_add(&(queues[7]), e);
		case STR_ETT_END:
		case STR_ETT_NUM:
		default:
			return STRUCTBOT_ERR_REASUNKTYP;
	}
	
	return STRUCTBOT_ERR_NONE;
}

//Set up the list of queues to be just as long as every event type we need
static void init_queues() {
	queues = malloc(sizeof(structbot_priorityqueue) * STR_ETT_NUM);
}
