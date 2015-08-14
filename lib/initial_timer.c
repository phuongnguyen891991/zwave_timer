#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#include "initial_timer.h"
#include "currTime.h"

#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

struct sigevent sev;
struct itimerspec its;
sigset_t mask;
struct sigaction sa;
int i;
siginfo_t *si;
void *uc ;
int sig ;



 int timer_start(timer_t *timerid, int i)
 {
  
  int check_timer_create;
	check_timer_create = timer_create(CLOCKID, &sev, &timerid[i]);

  if(check_timer_create == -1)
        {
       	perror("timer_create");
        }

   	printf("timer ID is 0x%lx (%d) \n", (long)timerid[i],i);

   /* Start the timer */

   	if (timer_settime(timerid[i], 0, &its, NULL) == -1)
        {
        perror("timer_settime");
        }

        return 1;
 }

/*void print_siginfo(siginfo_t *si)
{
   timer_t *tidp;
   int or;

   tidp = si->si_value.sival_ptr;

   printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
   printf("    *sival_ptr = 0x%lx\n", (long)*tidp);

   or = timer_getoverrun(tidp);
   if (or == -1)
       perror("timer_getoverrun");
   else
       printf("    overrun count = %d\n", or);
}

void handler()
{
    *Note: calling printf() from a signal handler is not
      strictly correct, since printf() is not async-signal-safe;
      see signal(7)

   printf("[%s]Caught signal %d\n",currTime("%T"),sig);
   print_siginfo(si);
}  */
 /*void handler(int sig, siginfo_t *si, void *uc)
{
  timer_t * tidptr;
  tidptr=si->si_value.sival_ptr;
  printf("[%s] Got signal %d\n",currTime("%T"),sig);
  printf("*sigval_ptr         =%ld\n",(long)*tidptr);
  printf(" timer_getoverrun() =%d\n",timer_getoverrun(*tidptr));

}*/



int block_and_create_timer(struct sigaction sa, sigset_t mask,void(*handler))
{
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
   return 1;
}

 int setting_timer_count(const char *str, timer_t *timerid,int i) //set counter
{
   char *dupstr;
   
   //timer_t *timerid_ret;
   dupstr = strdup(str);
   //timerid_ret = timerid;
   
   its.it_value.tv_sec = atoi(dupstr);
   its.it_value.tv_nsec = 0;
   its.it_interval.tv_sec = 0;//its.it_value.tv_sec;
   its.it_interval.tv_nsec = 0;

   sev.sigev_value.sival_ptr = &timerid[i];
   //timerid_tmp = &timerid[i];

   free(dupstr);
   return 1;
}

void timer(timer_t *timerid, void(*handler),int argc, char *argv[], int loop)
{
    
    // timer_t *timerid_tmp;
  if (argc < 2 ) 
  {
       fprintf(stderr, "Usage: %s <int-secs> <int-secs>...\n",
               argv[0]);
       exit(EXIT_FAILURE);
    }

   //timerid = calloc(argc-1,sizeof(timer_t));

   if(timerid == NULL)
   {
    errExit("timerid NULL");
   }
  // timerid_tmp = timerid;

   printf("Establishing handler for signal %d\n", SIG);

   if(block_and_create_timer(sa,mask,handler) == -1)
   {
    perror("Error Create \n");
   }

   for(i = 1;i < argc;i++)
   {
    if(setting_timer_count(argv[i],timerid,i) == -1)
      {
        perror("Error setting \n");
      }
    
    if(timer_start(timerid, i) == -1)
    {
      perror("can not Create");
    }

   }
   for(;;)
   {
    pause();
   }
   free(timerid);
   //return 0;
 }