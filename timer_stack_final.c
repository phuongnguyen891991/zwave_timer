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

//struct linked_list * head_start = NULL;

//struct linked_list *lst ;
 static timer_t timerid;
 static timer_t timerid1;
//static timer_t  timerid2;
//static timer_t  timerid3;

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

void * handler_func1(timer_t timerid)
{
  printf("handler 1 signal is called \n");
  return (0);
}
void * handler_func2(timer_t timerid)
{
  printf("handler 2 signal is called \n");
  if(flag2 < 1)
  {
  printf("[0x%lx] \n",(long)timerid);
  timer_cancel(timerid);
  flag2++;
  }
  return (0);
}

void * handler_func3(timer_t * timerid)
{
  printf("handler 3 signal is called \n");
  if(flag3 < 1)
  {
 // timer_cancel(timerid1);
  flag3++;
  }
  return (0);
}
void * handler_func4()
{
  printf("handler 4 signal is called \n");
  if(flag4 < 1)
  {
  //timer_cancel(timerid2);
  flag4++;
  }
  print_list();
  return (0);
}

int main(int argc, char *argv[])
{

timerid  = calloc(1,sizeof(timer_t));
timerid1 = calloc(1,sizeof(timer_t));
//timerid2 = calloc(1,sizeof(timer_t));
//timerid3 = calloc(1,sizeof(timer_t));
 
int loop_times = 3 ; 
//int loop_times1 = 3;
//int loop_times2 = 2;

int timming = 1;
int timming1 = 3;
//int timming2 = 4;
//int timming3 = 2;

init_timer();
printf("timer in main: [0x%lx] \n",(long)timerid);
timer(timerid  ,handler_func1,timming ,loop_times);
timer(timerid1 ,handler_func2,timming1 ,loop_times);
//timer(timerid2 ,handler_func3,timming2 ,loop_times1);
//timer(timerid3 ,handler_func4,timming3 ,loop_times2);
print_list();
//timer_cancel(timerid);
//print_list();
//count_node();
while(1)
{
	pause();
}
//return 0;
}
