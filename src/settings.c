#include <stdbool.h>
#include <string.h>

#include <argp.h>

#include "settings.h"
#include "version.h"


const char* argp_program_version = MAJORVERSION"."MINORVERSION;
const char* argp_program_bug_address = "gameraftexploision@gmail.com";

const struct argp_option options[] = {\
                                     {"plugindir", 'p', "dir", 0, "Specify the directory where structbot plugins are located", 0},\
                                     {  "verbose", 'v',     0, 0,                   "Have structbot print messages verbosely", 0},\
                                     {    "debug", 'd',     0, 0,                 "Have structbot print basically everything", 0},\
                                     {          0,   0,     0, 0,                                                           0, 0}\
                                    };

const struct argp argp = {\
                           &(options[0]),\
                           parse_options,\
                           "structbot [OPTIONS]",\
                           "A modular IRC bot.",\
                           NULL,\
                           NULL,\
                           NULL\
                          };

void start_parsing(int argc, char **argv, structbot_settings *settings) {
	argp_parse(&argp, argc, argv, 0, NULL, (void *)settings);
}

error_t parse_options(int key, char *arg, struct argp_state *state) {
	structbot_settings *settings = state->input;
	
	switch (key) {
		case 'v':
			settings->verbose = true;
			break;
		case 'd':
			settings->debug = true;
			break;
		case 'p':
			settings->pluginRelPath = malloc((strlen(arg) + 1) * sizeof(char));
			strcpy(settings->pluginRelPath, arg);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
} 
