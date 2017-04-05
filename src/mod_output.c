#include "mod_output.h"

void TC_check_resolution(int *maxx, int *maxy)
/* This function is invoked every repeat of main loop. It checkes the 
 * whenever the resolution of the screen changes, nad if so, it chenges
 * the values in corespondent variables. It is needed for resizable 
 * xterm windows */
{
	int tmaxx, tmaxy;

	getmaxyx(stdscr, tmaxy, tmaxx);
	if ( tmaxy != *maxy || tmaxx != *maxx )
	{
		*maxy=tmaxy;
		*maxx=tmaxx;
		// if resolution has changed clear the screen to avoid
		// bad looking artifacts on screen.
		clear_screen();
	}
}


void TC_draw_clock(char bufor[50], int bufor_length, int maxx, int maxy)
/* althought a bit confusing (and LONG) this function works quite easy
 * first it checks which language is currelntly in use, after that
 * a block of instructions FOR THAT particular language.
 * at the end refresh() is invoked to refresh screen */
{
	int posx, posy;
	int i=0;
	
	switch (use_lang) 
	{
	    case 0:			// DIGITAL language
		posx=((maxx-bufor_length*lang_digital.dwidth-(bufor_length-1)*lang_digital.x_rng)/2);
		posy=(maxy-lang_digital.dheight)/2;    
		
		while(bufor[i]!='\0') 
		// while not EOL
		{
		    insert_digit(bufor[i],posx+i*(lang_digital.dwidth+lang_digital.x_rng),posy);
		    i++;
		}
	    break;
	    
	    case 1:			// BCD language
		posx=((maxx-bufor_length*lang_bcd.dwidth-(bufor_length-1)*lang_bcd.x_rng)/2);
		posy=(maxy-lang_bcd.dheight*4-3*lang_bcd.y_rng)/2;
		
		while(bufor[i]!='\0') 
		// while not EOL
		{
		    insert_bcd(bufor[i],posx+i*(lang_bcd.dwidth+lang_bcd.x_rng),posy);
		    i++;
		}

	    break;
	    
	    case 2:			// U2 language
		posx=(maxx-lang_binary.width)/2;
		posy=(maxy-(lang_binary.height+lang_binary.y_rng)*3)/2;
		
		while(i<3)
		// only 3 characters are important here
		{
		    insert_binary(bufor[i],posx,posy+i*(lang_binary.y_rng+lang_binary.dheight));
		    i++;
		}
		
	    break;

	    default:			// DEFAULT: should never happen
	    break;
	}
	refresh();
}



void TC_format_string(char bufor[50])
/* This function prepares the time string to display on screen every 
 * repeat of the main loop. It also invokes the gettime() function to 
 * obtain current time */
{
    int timer, hours, minutes, seconds;
    TC_time_gettime(&timer, &hours, &minutes, &seconds);

    switch (use_lang)    
    {
    	case 0: lang_digital_format_string(bufor, timer, hours, minutes, seconds);
	break;
	case 1: lang_bcd_format_string(bufor, timer, hours, minutes, seconds);
	break;
	case 2: lang_binary_format_string(bufor, timer, hours, minutes, seconds);
	default:
	break;
    }
}



int TC_check_bufor_length(char bufor[50], int bufor_length)
/* this function check for length of the output string
 * whenever it changes it cleans the screen (to avoid 
 * ugly artefacts left on tty console ) */
{
	int tmp_length=strlen(bufor);

	if (tmp_length != bufor_length)
	{
		clear_screen();
		bufor_length=tmp_length;
	}
	return bufor_length;
}


/* this is a simple debugging function. If DO_DEBUG is defined (either in 
 * defs.h or as gcc flag it displays 'info' string whenever it's invoked
 * from program, else it just a empty function compiled inline */
#ifdef DO_DEBUG
void TC_debug(char *info, int type, int stop)
#endif
#ifndef DO_DEBUG
inline void TC_debug(char *info, int type, int stop)
#endif
{
#ifdef DO_DEBUG
    switch (type)
    {
        case 0: fprintf(stderr, "TC(II):%s\n\r",info);break;
        case 1: fprintf(stderr, "TC(WW):%s\n\r",info);break;
        case 2: fprintf(stderr, "TC(EE):%s\n\r",info);
    }

    /* if debug needs attention then stop the program */
    if (stop)
        getch();
#endif
}


