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


  //timer_t *timerid, *timerid_tmp;
   //struct sigevent sev;
   //struct itimerspec its;
void handler_func(int sig, siginfo_t *si, void *uc)
{
  timer_t * tidptr;
  tidptr=si->si_value.sival_ptr;
  printf("[%s] Caught signal %d\n",currTime("%T"),sig);
  printf("*sigval_ptr         =0x%lxd\n",(long)*tidptr);
  printf(" timer_getoverrun() =%d\n",timer_getoverrun(*tidptr));

}

int main(int argc, char *argv[])
{

timer_t *timerid ;
//int time_count ;
int loop =1;
timerid = calloc(argc-1,sizeof(timer_t));
void (*handler_tmp) = handler_func;

timer(timerid,handler_tmp,argc,argv,loop);


return 0;
}
