#include "mod_curses.h"

void clear_screen()
{
	clear();
}


void draw_hline_inpos(int start_x, int start_y, char draw_char, int length)
{
	mvhline(start_y, start_x, draw_char, length);
}


void draw_vline_inpos(int start_x, int start_y, char draw_char, int height)
{
	mvvline(start_y, start_x, draw_char, height);
}



void draw_char_inpos(int start_x, int start_y, char draw_char)
{
	mvaddch(start_y, start_x, draw_char);
}


void set_color_pair(int color_pair)
{
	attron(COLOR_PAIR(color_pair));
}


void init_curses()
/* Initiating ncurses screen in program. It also displays some debug
   information if necessary, hides the cursor and disable the echo */
{
    initscr();
    curses_active=1;
    keypad(stdscr,TRUE);
    noecho();
    curs_set(0);
}


void end_curses()
{
	endwin();
}
