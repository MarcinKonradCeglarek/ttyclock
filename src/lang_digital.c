#include "lang_digital.h"

void lang_digital_format_string(char bufor[50], int timer, int hours, int minutes, int seconds)
/* It's just simple formating here, nevertheless this function (the 
 * function that formats the output string) is unique for every language
 * If timer is less then 0, that means that we are in countdown mode, 
 * so we should put '-' at the beginning */
{
    if (timer<0)
	sprintf(bufor,"-%2d:%2d:%2d",hours,minutes,seconds);    
    else
	sprintf(bufor,"%2d:%2d:%2d",hours,minutes,seconds);
}


void insert_digit(char digit, int posx, int posy)
/* Inserts a part of digit. Depend on variable part it can put:

  +---4-+
  |     |
  |1    |32
  +---8-+
  |     |
  |2    |64
  +--16-+	
 * in invocations of insert_digit_part I use mask of above. It's well 
 * explained in the insert_digit_part body, so I won't explaint that 
 * mechanism here							*/
{
	if (digit!=':')
	{
	    // switching to 'dark' (or black if term don't support 
	    // colors) color sheme
	    set_color_pair(1);
	    insert_digit_part(127,posx,posy);
	}

	set_color_pair(2);

	switch(digit) {
	    case '0':
		// for example 0 almost every element shown (except 
		// middle slash (8))
		insert_digit_part(127-8,posx,posy);
	    break;
	    case '1':
		// '1' is made of two lines (32 and 64)
	        insert_digit_part(32+64,posx,posy);
	    break;	
	    case '2':
		insert_digit_part(127-64-1,posx,posy);
	    break;
	    case '3':
		insert_digit_part(127-3,posx,posy);
	    break;
	    case '4':
		insert_digit_part(1+32+64+8,posx,posy);
	    break;
	    case '5':
		insert_digit_part(127-32-2,posx,posy);
	    break;
	    case '6':
		insert_digit_part(127-32,posx,posy);
	    break;
	    case '7':
		insert_digit_part(64+32+4,posx,posy);
	    break;
	    case '8':
		insert_digit_part(127,posx,posy);
	    break;
	    case '9':
		insert_digit_part(127-2,posx,posy);
	    break;
	    case ':':
        	draw_char_inpos(posx+lang_digital.dwidth/2,posy+lang_digital.dheight/3,' ');
		draw_char_inpos(posx+lang_digital.dwidth/2,posy+lang_digital.dheight-1-lang_digital.dheight/3,' ');
	    break;
	    case '-':
		draw_hline_inpos(posx+1,posy+lang_digital.dheight/2,' ',lang_digital.dwidth-2);
	    break;
	    default:
		insert_digit_part(127-8,posx,posy);
	    break;	    
	}
}

void insert_digit_part(int part, int posx, int posy)
/* Inserts a part of digit. Depend on variable part it can put:

  +---4-+
  |     |
  |1    |32
  +---8-+
  |     |
  |2    |64
  +--16-+	
  
 * You are encouraged to use masks here. For example if you want to put 
 * for example digit '5' you should consider passing 92 as a part 
 * variable. It's because the digit 5 is made of elements: 4, 1, 8, 64 
 * and 16. 4+1+8+64+16 equals 92. Also you can substract missing 
 * elements (2, 32) from 127 (all elements shown).*/

{
    int draw_char=' ';
    
    // here we check whenever the i bit is set in the 'part' variable:
    // part & 00000001
    if ((part & 1)!=0)				// 00000001
    	draw_vline_inpos(posx, posy, draw_char, lang_digital.dheight/2);
	
    if ((part & 2)!=0)				// 00000010
	draw_vline_inpos(posx, posy+lang_digital.dheight/2, draw_char, lang_digital.dheight/2+1);
	
    if ((part & 4)!=0)				// 00000100
	draw_hline_inpos(posx, posy, draw_char, lang_digital.dwidth);

    if ((part & 8)!=0)				// 00001000
	draw_hline_inpos(posx,posy+lang_digital.dheight/2,draw_char,lang_digital.dwidth);
	
    if ((part & 16)!=0)				// 00010000
	draw_hline_inpos(posx,posy+lang_digital.dheight-1,draw_char,lang_digital.dwidth);

    if ((part & 32)!=0)				// 00100000
	draw_vline_inpos(posx+lang_digital.dwidth-1, posy, draw_char, lang_digital.dheight/2);

    if ((part & 64)!=0)				// 01000000
	draw_vline_inpos(posx+lang_digital.dwidth-1, posy+lang_digital.dheight/2, draw_char, lang_digital.dheight/2+1);
}
