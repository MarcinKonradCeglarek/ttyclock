#ifndef OUTPUTH

#include <string.h>
#include <ncurses.h>
#include "defs.h"


/************************************************* GLOBAL VARIABLES*****/
char *color_sheme="cyan";
char *default_bg="black";

struct color_list {
    char *name;
    int r, g, b;
    int std;
};
    
struct color_list colors[] = {
/* Here is an array with some default colors included 
 * The synopsis is: human_name, red, green, blue, standard ncurses color
 * the every color is within range 0 - 999 */
    {"black"  ,  0,  0,  0, 0},
    {"red"    ,999,  0,  0, 1},
    {"blue"   ,  0,  0,999, 4},
    {"yellow" ,999,999,  0, 3},
    {"magenta",999,  0,999, 5},
    {"orange" ,999,500,  0, 3},
    {"green"  ,  0,999,  0, 2},
    {"cyan"   ,  0,999,999, 6},
    {"white"  ,999,999,999, 7},
    {"gray"   ,500,500,500, 7},
    {"user"   ,500,500,500, 7},
    // closing record (needed for proper exiting from loops
    {"end",0,0,0}
};

/***************************************** FUNCTION'S DECLARATIONS *****/
int TC_set_colors();

#ifdef DO_DEBUG
void TC_debug(char *info, int type, int stop);
#endif

#ifndef DO_DEBUG
inline void TC_debug(char *info, int type, int stop);
#endif

/********************************************** EXTERNAL FUNCTIONS *****/


/********************************************** EXTERNAL VARIABLES *****/
extern int curses_active;
extern int use_lang;

#define OUTPUTH 1
#endif
//#include "mod_colors.h"

