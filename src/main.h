/***************************************************************\
* Author:   Marcin Ceglarek                                     *
* Program:  Ncurses Watch                                       *
* Version:  0.3.0                                               *
* Synopsis: This program has been written to provide some kind  *
*           nice looking digital/binary watch for linux console *
*           It's quite simple without any sophisticated options *
*           (so far). If you need some nice shiny console clock *
*           with some additional parameters it's just for you   *
* Date:     21.10.2004                                          *
\***************************************************************/

#ifndef MAINH

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"
#include "languages.h"


/************************************************ GLOBAL CONSTANTS *****/
// global constants: timezone information

const int timezone_shift=3600;

const int TC_SET_LANGUAGE=0;
const int TC_SET_COLOR=1;
const int TC_SET_TIMER=2;
const int TC_SET_COUNTDOWN=3;
const int TC_SET_SYSTEM=4;
const int TC_SET_STOPER=5;
const int TC_SET_NOTIFY=6;
const int TC_CHECK_COUNTDOWN=252;
const int TC_CHECK_SYSTEM=251;


/************************************************ GLOBAL VARIABLES *****/
/* global variables: most of them are used in varius diffrent places 
 * and i don't want to add them to definition of every function in program
 */
int curses_active=0;
int use_lang=0;
int mode=NORMAL_MODE;
int timer0=0;


/********************************************* EXTERNAL VARIABLES *****/
/* default screen size. check also for getmaxyx() function which 
 * provides current values for xterm virtual screens */
extern int maxx;
extern int maxy;


/****************************************** FUNCTION DEKLARATIONS *****/
#ifdef DO_DEBUG
extern void TC_debug(char *info, int type, int stop);
#endif
#ifndef DO_DEBUG
extern inline void TC_debug(char *info, int type, int stop);
#endif

void TC_print_help(char *name);
void TC_abnormal_termination(int errorlevel, char *debug);
int main(int argc, char *argv[]);



/********************************************* EXTERNAL FUNCTIONS *****/

//			 from mod_curses.c:
extern void clear_screen();
extern void init_curses();
extern void end_curses();


//			 from mod_output.c:
extern void TC_check_resolution(int *maxx, int *maxy);
extern void TC_draw_clock(char bufor[50], int bufor_length, int maxx, int maxy);
extern void TC_format_string(char bufor[50]);
extern int TC_check_bufor_length(char bufor[50], int bufor_length);

//                       from mod_colors.c
extern int TC_set_colors();

//			 from langs:
extern void TC_initiate_languages();

//			 from mod_command_line.c:
extern void TC_check_parameters(int argc, char *argv[]);
extern int TC_check_flags(int flags[4], const int flag);

// 			 from mod_time.c:
extern void TC_time_gettime(int *timer, int *hours, int *minutes, int *seconds);
extern void TC_interval();

extern void insert_binary_pt(int, int);
#define MAINH 1
#endif
