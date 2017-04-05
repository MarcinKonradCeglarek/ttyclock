#include "mod_time.h"

void TC_time_gettime(int *timer, int *hours, int *minutes, int *seconds)
/* this function gets current unix-time (seconds from 1970) substracts 
 * possible shift (for --timer and --stoper flag) and extracts number of 
 * elpased seconds in current day. Than it calculates the current time
 * (OR a time which has to be shown on clock).
 * It's worth notifying that timer CAN be a negative integer. It happens when 
 * program is in countdown mode (it also displays '-' at the beggining of string
 */
{
    //*timer=( time(0)+timezone_shift)%86400 - timer0 ;
    
    switch (mode)
    {
	case NORMAL_MODE: *timer= (time(0)+timezone_shift)%86400;
	break;
	
	default: *timer = time(0) - timer0;
	break;
    }
    
    *seconds=abs(*timer%60);
    *minutes=abs((*timer/60)%60);
    *hours=abs(*timer/3600);
	return;
}

void TC_interval()
// the only reason it's separate function is to keep all time-related functions
// in one place
{
    usleep(interval);
}
