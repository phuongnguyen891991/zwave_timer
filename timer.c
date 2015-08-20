#define TT_SIGUSR1 (SIGUSR1)
#define TT_SIGUSR2 (SIGUSR2)
#define TIME_INTERVAL_1 1
#define TIME_INTERVAL_2 2

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

timer_t create_timer(int signo) {
    timer_t timerid;
    struct sigevent se;
    se.sigev_notify=SIGEV_SIGNAL;
    se.sigev_signo = signo;
    if (timer_create(CLOCK_REALTIME, &se, &timerid) == -1) {
        perror("Failed to create timer");
        exit(-1);
    }
    return timerid;
}

void set_timer(timer_t timerid, int seconds) {
    struct itimerspec timervals;
    timervals.it_value.tv_sec = seconds;
    timervals.it_value.tv_nsec = 0;
    timervals.it_interval.tv_sec = seconds;
    timervals.it_interval.tv_nsec = 0;

    if (timer_settime(timerid, 0, &timervals, NULL) == -1) {
        perror("Failed to start timer");
        exit(-1);
    }
    return;
}

void install_sighandler(int signo, void(*handler)(int)) {
    sigset_t set;
    struct sigaction act;

    /* Setup the handler */
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;
    sigaction(signo, &act, 0);

    /* Unblock the signal */
    sigemptyset(&set);
    sigaddset(&set, signo);
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    return;
}


void signal_handler(int signo) {
    printf("receiving sig %d\n", signo);
}

int main()
{
    printf("test\n");
    timer_t timer1 = create_timer(TT_SIGUSR1);
    timer_t timer2 = create_timer(TT_SIGUSR2);

    install_sighandler(TT_SIGUSR1, signal_handler);
    install_sighandler(TT_SIGUSR2, signal_handler);

    set_timer(timer1, TIME_INTERVAL_1);
    set_timer(timer2, TIME_INTERVAL_2);

    while (1) sleep(1);
    return 0;
}
