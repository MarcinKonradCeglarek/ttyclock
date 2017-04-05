#include "languages.h"

void TC_initiate_languages()
/* this function initiates the basic languages table */
{
	TC_debug("initiating digital language",0,0);
	
	lang_digital.name="digital";
	lang_digital.lp=0;
	lang_digital.is_hor=1;
	lang_digital.segments=1;

	lang_digital.width=5;
	lang_digital.height=5;
	lang_digital.x_rng=1;
	lang_digital.y_rng=0;
	lang_digital.dwidth=lang_digital.width;
	lang_digital.dheight=lang_digital.height;
	


	TC_debug("initiating BCD language",0,0);
	
	lang_bcd.name="bcd";
	lang_bcd.lp=1;
	lang_bcd.is_hor=1;
	lang_bcd.segments=4;

	lang_bcd.x_rng=3;
	lang_bcd.y_rng=2;
	lang_bcd.dwidth=6;
	lang_bcd.dheight=4;
	lang_bcd.width=lang_bcd.dwidth;
	lang_bcd.height=lang_bcd.segments * (lang_bcd.dheight + lang_bcd.y_rng) - lang_bcd.y_rng;


	
	TC_debug("initiating binary language",0,0);
	
	lang_binary.name="binary";
	lang_binary.lp=2;
	lang_binary.is_hor=0;
	lang_binary.segments=8;

	lang_binary.dwidth=5;
	lang_binary.dheight=2;
	lang_binary.x_rng=3;
	lang_binary.y_rng=2;

	lang_binary.width=(lang_binary.dwidth+lang_binary.x_rng) *lang_binary.segments - lang_binary.x_rng;
	lang_binary.height=lang_binary.dheight;
	
}
