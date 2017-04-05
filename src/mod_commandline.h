#ifndef COMMANDLINEH

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <stdio.h>
#include "defs.h"
#include "languages.h"
//#include "mod_colors.h"


/******************************************* FUNCTION DECLARATIONS *****/
int TC_check_flags(int flags[4], const int flag);
void TC_check_parameters(int argc, char *argv[]);

void TC_found_flag_help(char *name);
void TC_found_flag_stoper(int flags[10]);
void TC_found_flag_timer(int flags[10]);
void TC_found_flag_counter(int flags[10], char *optarg);
void TC_found_flag_run(int flags[10], char *optarg);
void TC_found_flag_notify(int flags[10], char *optarg);
void TC_found_flag_languages(int flags[10],char *optarg);
void TC_found_flag_colors(int flags[10], char *optarg);



/********************************************** EXTERNAL FUNCTIONS *****/
#ifdef DO_DEBUG
	extern void TC_debug(char *info, int type, int stop);
#endif
#ifndef DO_DEBUG
	extern inline void TC_debug(char *info, int type, int stop);
#endif

extern void TC_print_help(char *name);
extern void TC_abnormal_termination(int errorlevel, char *debug);



/********************************************** EXTERNAL CONSTANTS *****/
extern const int timezone_shift;

extern const int TC_SET_LANGUAGE;
extern const int TC_SET_COLOR;
extern const int TC_SET_TIMER;
extern const int TC_SET_COUNTDOWN;
extern const int TC_SET_SYSTEM;
extern const int TC_SET_STOPER;
extern const int TC_SET_NOTIFY;
extern const int TC_CHECK_SYSTEM;
extern const int TC_CHECK_COUNTDOWN;


/********************************************** EXTERNAL VARIABLES *****/
extern int use_lang;
extern int mode;
extern int timer0;
extern char *color_sheme;
extern char *optarg;

struct color_list {
    char *name;
    int r,g,b;
    int std;
};

extern struct color_list colors[];


#define COMMANDLINEH 1
#endif
