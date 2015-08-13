#include <stdlib.h>
#include <string.h>
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
//#include "lib/print_timer.h"

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

   if(block_and_create_timer(sa,mask) == -1)
   {
    perror("Error Create \n");
   }

   for(i = 1;i < argc;i++)
   {
   //	printf("argv[%d]: %s \n",i,argv[i]);

    timerid_tmp = setting_timer_count(argv[i],timerid[i]);

   	//sev.sigev_value.sival_ptr = &timerid[i];
   //	printf("timer_id: %p\n",&timerid_tmp);
   	
   	if(timer_start(timerid_tmp,sev,its,i) == -1)
   	{
   		perror("can not Create");
   	}

   }
   while(1)
   {
   	pause();
   }
   //exit(EXIT_SUCCESS);
   return 0;
}

