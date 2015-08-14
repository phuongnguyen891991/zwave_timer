
#include <time.h>

 
#define CLOCKID CLOCK_REALTIME
   
#ifndef TIMER_START
#define TIMER_START

 int timer_start(timer_t *timerid,int i);
 int setting_timer_count(const char *str,  timer_t *timerid,int i);
 int block_and_create_timer(struct sigaction sa, sigset_t mask,void(*handler));
 void print_siginfo(siginfo_t *si);
 //void handler(int sig, siginfo_t *si, void *uc)
 void timer(timer_t *timerid,void (*handler), int argc, char *argv[],int loop);


#endif