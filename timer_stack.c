#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN
#define BUF_SIZE 1000

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                       } while (0)

char *
 currTime(const char *format)
 {
     static char buf[BUF_SIZE];  /* Nonreentrant */
     time_t t;
     size_t s;
     struct tm *tm;
 
     t = time(NULL);
     tm = localtime(&t);
     if (tm == NULL)
         return NULL;
 
     s = strftime(buf, BUF_SIZE, (format != NULL) ? format : "%c", tm);
 
     return (s == 0) ? NULL : buf;
 }

static void
print_siginfo(siginfo_t *si)
{
   timer_t *tidp;
   int or;

   tidp = si->si_value.sival_ptr;

   printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
   printf("    *sival_ptr = 0x%lx\n", (long) *tidp);

   or = timer_getoverrun(*tidp);
   if (or == -1)
       perror("timer_getoverrun");
   else
       printf("    overrun count = %d\n", or);
}

static void
handler(int sig, siginfo_t *si, void *uc)
{
   /* Note: calling printf() from a signal handler is not
      strictly correct, since printf() is not async-signal-safe;
      see signal(7) */

   printf("[%s]Caught signal %d\n",currTime("%T"), sig);
   print_siginfo(si);
  // signal(SIG, SIG_DFL);
}

int
main(int argc, char *argv[])
{
   timer_t *timerid;
   struct sigevent sev;
   struct itimerspec its;
   //long long freq_nanosecs;
   sigset_t mask;
   struct sigaction sa;
   int i;
   if (argc < 2 ) {
       fprintf(stderr, "Usage: %s <int-secs> <int-secs>...\n",
               argv[0]);
       exit(EXIT_FAILURE);
   }
   timerid = calloc(argc-1,sizeof(timer_t));
   if(timerid == NULL)
   {
		errExit("timerid NULL");
   }
   /* Establish handler for timer signal */

   printf("Establishing handler for signal %d\n", SIG);
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
  // sev.sigev_value.sival_ptr = &timerid;
   for(i=1;i<argc;i++)
   {

     //freq_nanosecs = atoi(argv[i]);
   its.it_value.tv_sec = atoi(argv[i]);
   its.it_value.tv_nsec = 0;
   its.it_interval.tv_sec = 0;//its.it_value.tv_sec;
   its.it_interval.tv_nsec = 0;

   sev.sigev_value.sival_ptr=&timerid[i];
        
   	if (timer_create(CLOCKID, &sev, &timerid[i]) == -1)
        {
       errExit("timer_create");
        }

   printf("timer ID is 0x%lx\n", (long) timerid[i]);

   /* Start the timer */

   if (timer_settime(timerid[i], 0, &its, NULL) == -1)
        {
        errExit("timer_settime");
        }

   }

   while(1)
   {
    pause();
   } 
   exit(EXIT_SUCCESS);
   return 0;
   //exit(EXIT_SUCCESS);
   
}