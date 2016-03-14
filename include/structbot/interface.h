#ifndef _INTERFACE_H_STRUCTBOT
#define _INTERFACE_H_STRUCTBOT

#include <stdlib.h> //size_t

//Different types of events
typedef enum {
	STR_ETT_NUM = 8,
	STR_ETT_PROGRAMSTART,
	STR_ETT_SERVERCONNECTION,
	STR_ETT_CHANNELCONNECTION,
	STR_ETT_USERJOIN,
	STR_ETT_USERLEAVE,
	STR_ETT_CHANNELMESG,
	STR_ETT_PRIVMSG,
	STR_ETT_PING,
	STR_ETT_END,
} structbot_eventtype;

//This is an event struct. It determines the priority of the event, the location, the function callbacks, and the type
typedef struct _structbot_event_ {
	//Priority for deciding in which order to call the event hooks
	size_t priority;
	//Type of the event
	structbot_eventtype event;
	//Function to call when event is being handled
	int (* event_handler)(struct _structbot_event_* e);
	//message that comes with the event, in the event of a message it will be the irc line, ect, ect
	//The special event types (programstart, serverconnection) will only be allowed with priority 0.
	char* message;
	//Path to the plugin containing the event hook. This is incase the callback fails. In that case, we'd need to call the error decoding function
	char* soPath;
} structbot_event;

//Register an event hook
//Returns 0 on success
//Erros can be found in structbot/error.h
int hook_event(structbot_event* e);

#endif //_INTERFACE_H_STRUCTBOT
