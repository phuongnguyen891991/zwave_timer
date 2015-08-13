#define _POSIX_C_SOURCE 199309
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#include "print_timer.h"
#include "currTime.h"

//timer_t *tidp;

void print_siginfo(siginfo_t *si)
{
   timer_t *tidp;
   int or;

   tidp = si->si_value.sival_ptr;

   printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
   printf("    *sival_ptr = 0x%lx\n", (long)tidp);

   or = timer_getoverrun(tidp);
   if (or == -1)
       perror("timer_getoverrun");
   else
       printf("    overrun count = %d\n", or);
}

void handler(int sig, siginfo_t *si, void *uc)
{
    /*Note: calling printf() from a signal handler is not
      strictly correct, since printf() is not async-signal-safe;
      see signal(7) */

   printf("[%s]Caught signal %d\n",currTime("%T"),sig);
   print_siginfo(si);
   signal(SIGRTMIN, SIG_DFL);
}   
