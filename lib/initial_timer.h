#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

 
#define CLOCKID CLOCK_REALTIME
   
#ifndef TIMER_START
#define TIMER_START

 int timer_start(timer_t *timerid, struct sigevent sev, struct itimerspec its);


#endif