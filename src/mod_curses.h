/* This file delivers an interface between program and ncurses library
 * I CAN use ncurses directives directly from program, but if I would like
 * to move for example to other platorm it's an easiest way */
#include <ncurses.h>


/******************************************* FUNCTION DECLARATIONS *****/
void draw_hline_inpos(int start_y, int start_x, char draw_char, int length);
void draw_vline_inpos(int start_y, int start_x, char draw_char, int height);
void draw_char_inpos(int start_y, int start_x, char draw_char);

void clear_screen();

void set_color_pair(int color_pair);

void init_curses();
void end_curses();



/********************************************** EXTERNAL VARIABLES *****/
extern int curses_active;
