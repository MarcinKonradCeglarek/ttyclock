/***************************************************************\
* Author:   Marcin Ceglarek                                     *
* Program:  Ncurses Watch                                       *
* Version:  0.3.0                                               *
* Synopsis: This program has been written to provide some kind  *
*           nice looking digital/binary watch for linux console *
*           It's quite simple without any sophisticated options *
*           (so far). If you need some nice shiny console clock *
*           with some additional parameters it's just for you   *
* Date:     21.10.2004                                          *
\***************************************************************/

#include "main.h"
#include <stdio.h>

int main(int argc, char *argv[])
/* It's main program function. I believe that every sub-function
 * has a self-explaining TC, but nevertheless i will provide
 * a brief info about what it does. More info can be found in 
 * function's definition */
{
    int close_loop=1;
    char bufor[50];
    int bufor_length=0;

    
    // getopt() based function to parese command-line parameters
    TC_debug("main()",0,0);
    TC_check_parameters(argc, argv);
    
    // initiating ncurses screen and setting default colors
    TC_debug("initscr()",0,0);
    init_curses();

    TC_set_colors();

    // this function initiates the languages for later use
    TC_initiate_languages();

    // main program loop
    while(close_loop)
    {
		// we have to check xterm resolution every time 
		// user can resize the window after all ;)
		TC_check_resolution(&maxx, &maxy);

		// this function formats the clock string 
		// later that string will be used to draw a clock
		TC_format_string(bufor);

		// if string's length has changed then clear screen
		bufor_length=TC_check_bufor_length(bufor, bufor_length);

		// draw a clock using given formatted string
		TC_draw_clock(bufor, bufor_length, maxx, maxy);

		// wait 500.000microseconds (0.5s) for next redraw
		// 1s is a bit too long, since program doesn't finish
		// main loop in no-time. Sometimes it skipped one seccond
		TC_interval();
    }
    
    // after exiting from main loop clear the scren (althought it is
    // cleared while closing screen by ncurses)
    TC_debug("Clearing screen",0,0);
    clear_screen();
    
    // closing display and returning no-error exitcode to mother-process.
    end_curses();
    return 0;
}



void TC_print_help(char *name)
/* It's just a simple help.. nothing intresting here :P 
 * It takes one argument: the name with wchich the program was called */
{
    fprintf(stdout, "%s usage:\n\n", name);
    fprintf(stdout, "  -h, --help          brief help about flags which can be used with %s\n", name);
    fprintf(stdout, "  -s, --stoper        %s will count seconds since start\n", name);
    fprintf(stdout, "  -t, --timer         countdowns to specific moment in the future.\n");
    fprintf(stdout, "                      at the moment it will countdown to every full hour\n");
    fprintf(stdout, "  -u, --count, --countdown [HHh][MMm][SSs]\n");
    fprintf(stdout, "                      sets counter for specific time. Acceptable (and required)\n");
    fprintf(stdout, "                      aguments are for example:\n");
    fprintf(stdout, "                          33m10s - counts for 33minutes and 10seconds\n");
    fprintf(stdout, "                          5h33m - counts for 5hours and 33minutes\n");
    fprintf(stdout, "                          1h2m59s - counts for 1 hour, 2minutes and 59seconds\n");
    fprintf(stdout, "  -r, --run [file]\n");
    fprintf(stdout, "                      'file' can be a common ELF binary or a shell script. It will\n");    
    fprintf(stdout, "                      be invoked when counter reaches \'00:00:00\'.\n");
    fprintf(stdout, "  -c, --color [color]\n");
    fprintf(stdout, "                      'color' can be one of common colors like: black, blue, red\n");    
    fprintf(stdout, "                      yellow, green, cyan, violet, orange, white, gray or\n");
    fprintf(stdout, "                      a hex \"weblike\" color (ie.: 4455dd).\n");
    fprintf(stdout, "  -l, --lang, --language [digital|binary|bcd]\n");
    fprintf(stdout, "                      currently available languages are:\n");
    fprintf(stdout, "                          * digital - normal digital clock\n");
    fprintf(stdout, "                          * bcd - displays current time in BCD\n");
    fprintf(stdout, "                          * binary - a true 1337 (U2) binary clock ;)\n");
    fprintf(stdout, "  -n, --notify [file]\n");
    fprintf(stdout, "                      'file' should be a path to a sound file which will be palyed\n");
    fprintf(stdout, "                      every full hour. The file is simpy passed to /bin/play command\n");

    return;
}



void TC_abnormal_termination(int errorlevel, char *debug)
/* This function handles some unexpected errors which might occur during 
 * working. Those exitcodes are defined in defs.h */
{
	// this function does nothing for non-error exitcode. It is invoked after
	// every flag-checking, but displays errors (end halt's program) only on error
    if (errorlevel)
    {
        switch(errorlevel)
	{
	    case TC_DOUBLED_OPTION:
		fprintf(stderr, "You can't double the %s flags!\n", debug);
	    break;
	    case TC_INVALID_OPTIONS:
		fprintf(stderr, "Flag --normal isn't compatible with %s flag\n", debug);
	    break;
	    case TC_FLAG_T_NOT_SET:
	    	fprintf(stderr, "You can't use %s flag without the --timer flag\n", debug);
	    break;
	    case TC_UNKNOWN_COLOR_SHEME:
	    	fprintf(stderr, "The color sheme name '%s' is not valid\n", debug);
	    break;
	    case TC_OPTION_REQUIRE_ARG:
	    	fprintf(stderr, "Option %s require an argument!\n", debug);
	    break;
	    case TC_ARGUMENT_IS_INVALID:
	    	fprintf(stderr, "Argument %s is invalid\n", debug);
	    break;
	    case TC_ARGUMENT_HAS_WRONG_FORMAT:
	    	fprintf(stderr, "Argument '%s' has wrong format\n", debug);
	    break;
	    case TC_UNKNOWN_LANGUAGE:
		fprintf(stderr, "Given language '%s' is unknown\n", debug);
	    break;
	    default:
		TC_debug("abnormal_termination::unknown error!!!",0,0);
	    break;
	}
	// after displaying possible tips, exit with error exitcode
	exit(errorlevel);
    } else 
	return;
}

