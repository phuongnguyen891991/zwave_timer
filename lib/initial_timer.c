#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include "initial_timer.h"
#include "currTime.h"
#include "linked_list.h"

#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

sigset_t mask;

struct sigevent  sev;
struct linked_list * head_find = NULL;
struct linked_list *lst;

void * timerHandler(int sig, siginfo_t *si, void *uc)
{
    timer_t * tidp; 
    tidp = si->si_value.sival_ptr;

    printf("[%s] tidp [%p]\n",currTime("%T"),(long)*tidp);
    find_list_call_handler(*tidp);
    printf("\n");
}
int block_and_create_timer(int timming, struct linked_list * lst,int loop_times)//struct sigaction sa, sigset_t mask,void (*handler))
{

  struct itimerspec its;
  struct sigaction sa ;
  
  if((timer_create(CLOCK_REALTIME, &sev, &lst->timerid)) == -1)
        {
        perror("timer_create");
        }

    printf("timer ID is 0x%lx \n", (long)lst->timerid);

   its.it_value.tv_sec = timming;
   its.it_value.tv_nsec = 0;
   its.it_interval.tv_sec = loop_times;//its.it_value.tv_sec;
   its.it_interval.tv_nsec = 0;

   if (timer_settime(lst->timerid, 0, &its, NULL) == -1)
        {
        perror("timer_settime");
        }

   return 1;
}

void * ptimer_stop()
{
  char char_stop;
  //while(1)
  //{
  scanf("%s",&char_stop);
  if(char_stop == 'q')
  {
    exit(EXIT_SUCCESS);
  }
  return (0);
}
void init_timer(void)
{
  struct sigaction sa ;
  /*set up handler*/
    sa.sa_flags =  SA_SIGINFO;//SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
   
   sigemptyset(&sa.sa_mask);
   if (sigaction(SIGRTMAX, &sa, NULL) == -1)
       errExit("sigaction");
   /* Block timer signal temporarily */
   printf("Blocking signal %d\n", SIG);
   sigemptyset(&mask);
   sigaddset(&mask, SIG);
}

void timer(timer_t * timerid_input, void(*handler), int timming, int loop_times)
{
    //struct linked_list * lst;   
    lst = add_to_list(&timerid_input, handler,true);
   if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
       errExit("sigprocmask"); 

  sev.sigev_notify=SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMAX;
   printf("Establishing handler for signal %d\n", SIG);
   sev.sigev_value.sival_ptr = &lst->timerid;
   if(block_and_create_timer(timming,lst,loop_times) == -1)
   {
    perror("Error Create \n");
   }
 }

 void timer_cancel(timer_t *timerid_cancel)
 {
  init_timer();
  int ret_linked_list;
  char quit;

  scanf("%s",&quit);
//  if(quit == 'q')
//  {
  /*  printf(" signal cancel is %s  n",quit );
    sev.sigev_value.sival_ptr = &lst->timerid;
    if(block_and_create_timer(0,&lst,0) == -1)
    {
      perror("Error creae timer cancel \n");
    }
    else
    {*/
    while(lst!=NULL)
      {
       ret_linked_list = delete_from_list(&timerid_cancel) ;
            if(ret_linked_list != 0)
            {
                printf("\n delete  failed, no such element found\n");
            }
            else
            {
                printf("\n delete  [%p] passed \n",timerid_cancel);
            }
            lst = lst->next;
      }
//    }
 // }
}