#ifndef _INTERFACE_H_STRUCTBOT
#define _INTERFACE_H_STRUCTBOT

//Different types of events
typedef enum {
	USERJOIN,
	USERLEAVE,
	CHANNELMESG,
	PRIVMSG,
	PING,
	EVENTTYPEEND
} structbot_eventtype;

//This is an event struct. It determines the priority of the event, the location, the function callbacks, and the type
typedef struct {
	
} structbot_event;

#endif //_INTERFACE_H_STRUCTBOT
