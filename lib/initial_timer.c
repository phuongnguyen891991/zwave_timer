#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>


#include "initial_timer.h"
//#include "print_timer.h"
//#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

//struct sigevent sev;
//struct itimerspec its;


 int timer_start(timer_t *timerid, struct sigevent sev,struct itimerspec its)
 {
  int check_timer_create;
	check_timer_create = timer_create(CLOCK_REALTIME, &sev, &timerid);
  if(check_timer_create == -1)
        {
       	perror("timer_create");
        }

   	printf("timer ID is 0x%lx\n", (long) timerid);

   /* Start the timer */

   	if (timer_settime(timerid, 0, &its, NULL) == -1)
        {
        perror("timer_settime");
        }
        return 0;
 }
