#ifndef _SETTINGS_H_STRUCTBOT
#define _SETTINGS_H_STRUCTBOT

#include <argp.h>
#include <stdbool.h>

//This struct contains all possible settings that we can have
typedef struct {
	bool debug;
	bool verbose;
	char *pluginRelPath;
} structbot_settings;

//This function parses the cli input for argp
error_t parse_options(int key, char *arg, struct argp_state *state);

//Start parsing cli options with argp
void start_parsing(int argc, char **argv, structbot_settings *settings);

#endif //_SETTINGS_H_STRUCTBOT
