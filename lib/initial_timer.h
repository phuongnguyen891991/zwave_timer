
#include <time.h>
//#include "linked_list.h"
//include "linked_list.h"

#define CLOCKID CLOCK_REALTIME
   
#ifndef TIMER_START
#define TIMER_START

 ///timer_t * timer_start(int i);
 //int setting_timer_count(int timming,  timer_t * timerid,int i,int loop);
 //void * timerHandler( int sig, siginfo_t *si, void (*uc) ,struct linked_list * lst);
 //int block_and_create_timer(int timming, struct linked_list * lst,int i,int loop_times);
 //void print_siginfo(siginfo_t *si);
 void init_timer(void);
 void timer(timer_t * timerid,void (*handler), int *timming,int *loop_times);
 void timer_cancel(timer_t *timerid_cancel);


#endif