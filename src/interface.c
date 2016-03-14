//This is responsible for the functions defined in structbot/interface.h

#include <stdbool.h> //true/false

#include "structbot/interface.h"
#include "structbot.h"

int hook_event(structbot_event* e) {
	//Call the internal function to register this event into the priority queue
	//This is an external call, they can't be priority 0
	return register_event_as_hook(e, true);
}
