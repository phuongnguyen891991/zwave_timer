#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN
#define BUF_SIZE 1000

#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include "lib/currTime.h"
#include "lib/initial_timer.h"
#include "lib/print_timer.h"

   timer_t *timerid, *timerid_tmp;
   struct sigevent sev;
   struct itimerspec its;
   //long long freq_nanosecs;
   sigset_t mask;
   struct sigaction sa;
   int i;

int main(int argc, char *argv[])
{
	

	if (argc < 2 ) 
	{
       fprintf(stderr, "Usage: %s <int-secs> <int-secs>...\n",
               argv[0]);
       exit(EXIT_FAILURE);
    }

   timerid = calloc(argc-1,sizeof(timer_t));

   if(timerid == NULL)
   {
		errExit("timerid NULL");
   }

   printf("Establishing handler for signal %d\n", SIG);
   sa.sa_flags = SA_SIGINFO;
   sa.sa_sigaction = handler;
   sigemptyset(&sa.sa_mask);

   if (sigaction(SIGRTMAX, &sa, NULL) == -1)
       errExit("sigaction");

   /* Block timer signal temporarily */

   printf("Blocking signal %d\n", SIG);
   sigemptyset(&mask);
   sigaddset(&mask, SIG);
   if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
       errExit("sigprocmask");

   /* Create the timer */

   sev.sigev_notify = SIGEV_SIGNAL;
   sev.sigev_signo = SIGRTMAX;

   for(i=1;i<argc;i++)
   {
   	//printf("argc %d \n",argc);
   its.it_value.tv_sec = atoi(argv[i]);
   its.it_value.tv_nsec = 0;
   its.it_interval.tv_sec = 0;//its.it_value.tv_sec;
   its.it_interval.tv_nsec = 0;

   	sev.sigev_value.sival_ptr = &timerid[i];
   	timerid_tmp = &timerid[i];

   	if(timer_start(timerid_tmp,sev,its) == -1)
   	{
   		perror("can not Create");
   	}

   }
   while(1)
   {
   	//pause();
   }
   return 0;
}

