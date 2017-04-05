#ifndef TIMEFUNCTH

/* time.h is requered for time();
 * unistd.h for usleep();
 * and stdlib.h for abs() functions */

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "defs.h"

/************************************************ LOCAL  CONSTANTS *****/
int const interval=100000;	// the time (in microseconds) between each loop


/************************************************ LOCAL  FUNCTIONS *****/
void TC_time_gettime(int *timer, int *hours, int *minutes, int *seconds);
void TC_interval();


/********************************************** EXTERNAL VARIABLES *****/
extern int timer0;
extern int mode;

extern const int timezone_shift;

#define TIMEFUNCTH 1
#endif
