#ifndef LANGBINH

#include <stdio.h>
#include "languages.h"


/************************************************ GLOBAL VARIABLES *****/
struct lang_char lang_binary;



/************************************************ LOCAL  FUNCTIONS *****/
void lang_binary_format_string(char bufor[50], int timer, int hours, int minutes, int seconds);
void insert_binary(char digit, int posx, int posy);
void insert_binary_pt(int posy, int posx);


/********************************************** EXTERNAL FUNCTIONS *****/
extern void draw_hline_inpos(int start_y, int start_x, char draw_char, int length);
extern void draw_vline_inpos(int start_y, int start_x, char draw_char, int height);
extern void set_color_pair(int color_pair);


#define LANGBINH 1
#endif

