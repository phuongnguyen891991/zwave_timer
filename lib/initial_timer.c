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

int i;

struct linked_list *lst;

void * timerHandler()
{
 // printf("call handler function \n");
 // int sig;
    siginfo_t *si;
    timer_t  * tidp;
    void (*handler_call);
    struct linked_list * lst_find ;

    tidp = si->si_value.sival_ptr;
    //printf("[%s] timer  [%p] \n",currTime("%T"),&tidp);
     
    lst_find = search_in_list(tidp,NULL);
    //print_list();
    printf("[%s] timer ID is 0x%lx \n",currTime("%T"),(long)&lst_find->timerid);
    //lst_find->handler();
    //print_list();
    //lst_find->handler();
   
    //lst_find->handler;

    //lst_find = lst_find->next;
   // }
   /* while(lst != NULL)
    {
      printf("lst->timerid \n");
    if ( tidp == lst->timerid )
      //lst->handler;
      printf("EXIT_SUCCESS \n");
      lst = lst->next;
    } */
      //return (0);
}
int block_and_create_timer(int timming, struct linked_list * lst,int i,int loop_times)//struct sigaction sa, sigset_t mask,void (*handler))
{
  struct sigaction sa ;
  struct itimerspec its;
  struct sigevent sev;
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
   if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
       errExit("sigprocmask"); 

  sev.sigev_notify=SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMAX;
  sev.sigev_value.sival_ptr = &lst->timerid;

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

   return (0);
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

void timer(timer_t * timerid, void(*handler), int timming, int loop_times)
{
   
    lst = add_to_list(&timerid, handler,true);
  
   printf("Establishing handler for signal %d\n", SIG);
   //printf("%lx \n",si->si_timerid);
   if(block_and_create_timer(timming,lst,i,loop_times) == -1)
   {
    perror("Error Create \n");
   }
 }