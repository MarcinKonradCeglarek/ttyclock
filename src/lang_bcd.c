#include "lang_bcd.h"


void lang_bcd_format_string(char bufor[50], int timer, int hours, int minutes, int seconds)
/* This function formats the BCD string to further output. It don't need any special
 * "tweaks", but other (far more sophisticated) functions will so i put specialized 
 * function in every lang module */
{
    if (timer < 0)
    	sprintf(bufor,"-%2d%2d%2d",hours,minutes,seconds);
    else
	sprintf(bufor,"%2d%2d%2d",hours,minutes,seconds);
}



void insert_bcd(char digit, int posx, int posy)
/* This function gets the char, and coordinates and displays given char , where the
 * given coordinates are the upper left corner of displayed char. 
 * Then it calls a subroutine that displays a set of four bits (0 - 15) 
 * on the screen */
{
	// if input digit isn't ':' then draw a dark frame
	if (digit!='-')
	{
	    set_color_pair(1);
	    insert_bcd_elements( 15 , posx, posy);
	}
	
	// switching to color_pair 2 (default RED)
	set_color_pair(2);
	
	// if 'digit' is a common digit then just draw it on the screen
	if ( ( digit >= '0') && ( digit <= '9') )
	    insert_bcd_elements( digit-'0', posx, posy);
	else
	// else check for possible chars and print correspondent bits sets
	// for example '-' equals 15 (0000 1111)B
	    switch(digit) {
		case '-':
		    insert_bcd_elements( 4 , posx, posy);
		break;
	    }
}


void insert_bcd_elements(int part, int posx, int posy)
/* This function is able to display a pack of four bits on the screen. 
 * it just rewrite the last 4 bits of variable 'part' onto screen */
{
    int i;
    char draw_char=' ';

    if ((part & 1)!=0)			// 0001
        // now we draw a block. It's parameters are given in lang_bcd
	for(i=0;i<lang_bcd.dheight;i++)
	    draw_hline_inpos(posx,posy+(lang_bcd.dheight+lang_bcd.y_rng)*3+i,draw_char,lang_bcd.dwidth);

    if ((part & 2)!=0)    		// 0010
	for(i=0;i<lang_bcd.dheight;i++)
	    draw_hline_inpos(posx,posy+(lang_bcd.dheight+lang_bcd.y_rng)*2+i,draw_char,lang_bcd.dwidth);

    if ((part & 4)!=0)			// 0100
	for(i=0;i<lang_bcd.dheight;i++)
	    draw_hline_inpos(posx,posy+(lang_bcd.dheight+lang_bcd.y_rng)*1+i,draw_char,lang_bcd.dwidth);

    if ((part & 8)!=0)			// 1000
	for(i=0;i<lang_bcd.dheight;i++)
	    draw_hline_inpos(posx,posy+(lang_bcd.dheight+lang_bcd.y_rng)*0+i,draw_char,lang_bcd.dwidth);
}
