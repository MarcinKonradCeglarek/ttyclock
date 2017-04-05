#include "mod_colors.h"

int TC_set_colors()
/* This function is invoked from main.c and if possible for current 
 * sets the colors for drawing */
{
    int i=0;
    
    TC_debug("TC_set_colors()",0,0);
    
    if(has_colors())
    /* if colors are available then initiate colors, else return with 
     * exitstauts */
    {
      TC_debug("TC_set_colors() -> has_colors()",0,0);
      start_color();
      TC_debug("TC_set_colors() -> start_color()",0,0);
    } else {
      return 1;
    }

    /* a global variable 'color_sheme' contains user selected color for 
     * display use. Otherwise the color_sheme contains default color */
    /* This loop checks whenever user invoked program with reasonable 
       color like blue, red etc.*/
    while(strcmp(colors[i].name, color_sheme) )
        i++;
     
    if (can_change_color())
    {
	/* If terminal supports custom colors then try to set this 
	 * instead of standard color */
	TC_debug("TC_set_colors() -> can_change_color()",0,0);

	init_pair(1,1,1);
	init_pair(2,2,2);
	    
	init_color(2,colors[i].r,colors[i].g,colors[i].b);
	
	if (default_bg=="black")
	    init_color(1,colors[i].r/10,colors[i].g/10,colors[i].b/10);
	else
	{ 
	    init_color(1,(colors[i].r+800)%1000,(colors[i].g+800)%1000,(colors[i].b+800)%1000);
	    init_color(0,999,999,999);
	}
    } else {
	/* else use standard colors from structure 'colors' */
        init_pair(1,0,0);
	init_pair(2,colors[i].std,colors[i].std);
    } 
    
    // function ends here
    TC_debug("TC_set_colors() -> return 0",0,0);
    return 0;
}

