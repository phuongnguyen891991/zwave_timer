
#include <time.h>

 
#define CLOCKID CLOCK_REALTIME
   
#ifndef TIMER_START
#define TIMER_START

 timer_t timer_start(timer_t timerid, struct sigevent sev, struct itimerspec its,int i);
 timer_t setting_timer_count(const char *str,  timer_t *timerid);
 int block_and_create_timer(struct sigaction sa, sigset_t mask);
 void print_siginfo(siginfo_t *si);
 void handler(int sig, siginfo_t *si, void *uc);


#endif