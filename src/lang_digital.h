#ifndef LANGDIGH

#include <stdio.h>
#include "languages.h"


/************************************************ GLOBAL VARIABLES *****/
struct lang_char lang_digital;


/************************************************ LOCAL  FUNCTIONS *****/
void lang_digital_format_string(char bufor[50], int timer, int hours, int minutes, int seconds);
void insert_digit(char digit, int posx, int posy);
void insert_digit_part(int part, int posx, int posy);

/********************************************** EXTERNAL FUNCTIONS *****/
extern void draw_hline_inpos(int start_y, int start_x, char draw_char, int length);
extern void draw_vline_inpos(int start_y, int start_x, char draw_char, int height);
extern void draw_char_inpos(int start_y, int start_x, char draw_char);

extern void set_color_pair(int color_pair);

#define LANGDIGH 1
#endif
