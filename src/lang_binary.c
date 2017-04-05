#include "lang_binary.h"


void lang_binary_format_string(char bufor[50], int timer, int hours, int minutes, int seconds)
/* This function formats the binary string to further output. It don't need any special
 * "tweaks", but other (far more sophisticated) functions will so i put specialized 
 * function in every lang module */
{
    /* if timer is less then 0 that mean that we are in countdown mode. 
     * then we should convert our binary clock to proper U2 code for 
     * negative numbers ;) */
    if (timer<0)
	sprintf(bufor,"%c%c%c",-hours,-minutes,-seconds);
    else
    	sprintf(bufor,"%c%c%c",hours,minutes,seconds);
}



void insert_binary(char digit, int posx, int posy)
/* This function gets the char, and coordinates and displays given char , where the
 * given coordinates are the upper left corner of displayed char. That particular 
 * function displays a pack of four blocks which represents the BCD code for a digit */
{
	int j;
		
	char i=1;
	
	// sets the dark 'matrix' 8x3 on which we will write later
        set_color_pair(1);
        for (j=0;j<lang_binary.segments;j++)
    	    insert_binary_pt(posx+(lang_binary.x_rng+lang_binary.dwidth)*j, posy);
	
	// switching to color_pair 2 (default BLUE)
	set_color_pair(2);
	
	for (j=0; j<lang_binary.segments; j++)
	{
	    // if bit no. j (i = 2^j) is set 
		//then show the 'bit' in that place
	    if (( digit & i ) != 0 )
		insert_binary_pt(posx+lang_binary.width-lang_binary.dwidth - j*(lang_binary.dwidth+lang_binary.x_rng),posy);	

	    // i goes thru every (...) like 1, 2, 4, 8, 16, ...
	    i=i*2;		
	}
}


void insert_binary_pt(int posx, int posy)
/* displays a binary 'bit' in a given place of the screen */
{
    int i;
    char draw_char=' ';
    
    for (i=0; i<=lang_binary.dheight; i++)
	draw_hline_inpos(posx, posy+i, draw_char, lang_binary.dwidth);
}
