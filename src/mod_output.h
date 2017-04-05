#ifndef OUTPUTH

#include <ncurses.h>
#include <string.h>
#include "defs.h"
#include "languages.h"


/************************************************* GLOBAL VARIABLES*****/
int maxx=80;
int maxy=25;


/***************************************** FUNCTION'S DECLARATIONS *****/
int TC_init_scr();


void TC_check_resolution(int *maxx, int *maxy);
void TC_draw_clock(char bufor[50], int bufor_length, int maxx, int maxy);

void TC_format_string(char bufor[50]);
int TC_check_bufor_length(char bufor[50], int bufor_length);


#ifdef DO_DEBUG
void TC_debug(char *info, int type, int stop);
#endif

#ifndef DO_DEBUG
inline void TC_debug(char *info, int type, int stop);
#endif

/********************************************** EXTERNAL FUNCTIONS *****/
extern void lang_bcd_format_string(char bufor[50], int timer,  int hours, int minutes, int seconds);
extern void lang_digital_format_string(char bufor[50], int timer, int hours, int minutes, int seconds);
extern void lang_binary_format_string(char bufor[50], int timer, int hours, int minutes, int seconds);
extern int TC_set_colors();


extern void insert_bcd(char digit, int posx, int posy);
extern void insert_digit(char digit, int posx, int posy);
extern void insert_binary(char digit, int posx, int posy);

extern void clear_screen();

extern void TC_time_gettime(int *timer, int *hours, int *minutes, int *seconds);

/********************************************** EXTERNAL VARIABLES *****/
extern int curses_active;
extern int use_lang;

extern struct lang_char lang_bcd;
extern struct lang_char lang_digital;
extern struct lang_char lang_binary;

#define OUTPUTH 1
#endif
