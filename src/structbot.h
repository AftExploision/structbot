#ifndef _STRUCTBOT_H_STRUCTBOT
#define _STRUCTBOT_H_STRUCTBOT

//This is main prototype file for main.c

#include <stdbool.h> //true, false, bool
#include "structbot/interface.h" //structbot_event

//Register an event onto the priority queue. If the event is external, the
//minimum priority is 1
//Returns 0 on success and an error code on error
//Error codes are in structbot/error.h
int register_event_as_hook(structbot_event *e, bool external);

#endif //_STRUCTBOT_H_STRUCTBOT
