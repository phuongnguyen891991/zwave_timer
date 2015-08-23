#define TT_SIGUSR1 (SIGRTMAX)
#define TT_SIGUSR2 (SIGRTMAX-1)
#include <signal.h>
#include <time.h>

#include <stdio.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sched.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN
#define BUF_SIZE 1000

#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include "lib/currTime.h"
#include "lib/initial_timer.h"
#include "lib/linked_list.h"

struct linked_list * head_start = NULL;

struct linked_list *lst ;
timer_t * timerid;
timer_t * timerid1;
timer_t * timerid2;
timer_t * timerid3;

 void * handler_func1()
{
  printf("handler 1 signal is called \n");
  /*timer_t tidptr1;
  //tidptr1=si->si_value.sival_ptr;
  printf("[%s] Caught signal %d\n",currTime("%T"),sig);
  //printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
  printf("     *sigval_ptr = 0x%lx\n",(long)tidptr1);
 // printf(" overrun count = %d\n",timer_getoverrun(tidptr1)); */
  return (0);
}
 void * handler_func2()
{
  printf("handler 2 signal is called \n");
  return (0);
}
void * handler_func3()
{
  printf("handler 3 signal is called \n");
  return (0);
}


int main(int argc, char *argv[])
{

int loop_times = 0 ; 
int loop_times1 = 3;
int loop_times2 = 2;

int timming = 1;
int timming1 = 3;
int timming2 = 4;
int timming3 = 5;

init_timer();
timer(timerid  ,handler_func1,timming ,loop_times);
//timer(timerid1 ,handler_func2,timming1 ,loop_times);
//timer(timerid2 ,handler_func3,timming2 ,loop_times2);
//timer(timerid3 ,handler_func2,timming3 ,loop_times);
print_list();
timer_cancel(timerid);
print_list();
while(1)
{
	pause();
}//sleep(1);
return 0;
}
